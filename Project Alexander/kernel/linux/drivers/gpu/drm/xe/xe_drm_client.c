// SPDX-License-Identifier: MIT
/*
 * Copyright © 2023 Intel Corporation
 */
#include "xe_drm_client.h"

#include <drm/drm_print.h>
#include <drm/xe_drm.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/types.h>

#include "xe_bo.h"
#include "xe_bo_types.h"
#include "xe_device_types.h"
#include "xe_exec_queue.h"
#include "xe_force_wake.h"
#include "xe_gt.h"
#include "xe_hw_engine.h"
#include "xe_pm.h"
#include "xe_trace.h"

/**
 * DOC: DRM Client usage stats
 *
 * The drm/xe driver implements the DRM client usage stats specification as
 * documented in :ref:`drm-client-usage-stats`.
 *
 * Example of the output showing the implemented key value pairs and entirety of
 * the currently possible format options:
 *
 * ::
 *
 * 	pos:    0
 * 	flags:  0100002
 * 	mnt_id: 26
 * 	ino:    685
 * 	drm-driver:     xe
 * 	drm-client-id:  3
 * 	drm-pdev:       0000:03:00.0
 * 	drm-total-system:       0
 * 	drm-shared-system:      0
 * 	drm-active-system:      0
 * 	drm-resident-system:    0
 * 	drm-purgeable-system:   0
 * 	drm-total-gtt:  192 KiB
 * 	drm-shared-gtt: 0
 * 	drm-active-gtt: 0
 * 	drm-resident-gtt:       192 KiB
 * 	drm-total-vram0:        23992 KiB
 * 	drm-shared-vram0:       16 MiB
 * 	drm-active-vram0:       0
 * 	drm-resident-vram0:     23992 KiB
 * 	drm-total-stolen:       0
 * 	drm-shared-stolen:      0
 * 	drm-active-stolen:      0
 * 	drm-resident-stolen:    0
 * 	drm-cycles-rcs: 28257900
 * 	drm-total-cycles-rcs:   7655183225
 * 	drm-cycles-bcs: 0
 * 	drm-total-cycles-bcs:   7655183225
 * 	drm-cycles-vcs: 0
 * 	drm-total-cycles-vcs:   7655183225
 * 	drm-engine-capacity-vcs:        2
 * 	drm-cycles-vecs:        0
 * 	drm-total-cycles-vecs:  7655183225
 * 	drm-engine-capacity-vecs:       2
 * 	drm-cycles-ccs: 0
 * 	drm-total-cycles-ccs:   7655183225
 * 	drm-engine-capacity-ccs:        4
 *
 * Possible `drm-cycles-` key names are: `rcs`, `ccs`, `bcs`, `vcs`, `vecs` and
 * "other".
 */

/**
 * xe_drm_client_alloc() - Allocate drm client
 * @void: No arg
 *
 * Allocate drm client struct to track client memory against
 * same till client life. Call this API whenever new client
 * has opened xe device.
 *
 * Return: pointer to client struct or NULL if can't allocate
 */
struct xe_drm_client *xe_drm_client_alloc(void)
{
	struct xe_drm_client *client;

	client = kzalloc(sizeof(*client), GFP_KERNEL);
	if (!client)
		return NULL;

	kref_init(&client->kref);

#ifdef CONFIG_PROC_FS
	spin_lock_init(&client->bos_lock);
	INIT_LIST_HEAD(&client->bos_list);
#endif
	return client;
}

/**
 * __xe_drm_client_free() - Free client struct
 * @kref: The reference
 *
 * This frees client struct. Call this API when xe device is closed
 * by drm client.
 *
 * Return: void
 */
void __xe_drm_client_free(struct kref *kref)
{
	struct xe_drm_client *client =
		container_of(kref, typeof(*client), kref);

	kfree(client);
}

#ifdef CONFIG_PROC_FS
/**
 * xe_drm_client_add_bo() - Add BO for tracking client mem usage
 * @client: The drm client ptr
 * @bo: The xe BO ptr
 *
 * Add all BO created by individual drm client by calling this function.
 * This helps in tracking client memory usage.
 *
 * Return: void
 */
void xe_drm_client_add_bo(struct xe_drm_client *client,
			  struct xe_bo *bo)
{
	XE_WARN_ON(bo->client);
	XE_WARN_ON(!list_empty(&bo->client_link));

	spin_lock(&client->bos_lock);
	bo->client = xe_drm_client_get(client);
	list_add_tail(&bo->client_link, &client->bos_list);
	spin_unlock(&client->bos_lock);
}

/**
 * xe_drm_client_remove_bo() - Remove BO for tracking client mem usage
 * @bo: The xe BO ptr
 *
 * Remove all BO removed by individual drm client by calling this function.
 * This helps in tracking client memory usage.
 *
 * Return: void
 */
void xe_drm_client_remove_bo(struct xe_bo *bo)
{
	struct xe_drm_client *client = bo->client;

	spin_lock(&client->bos_lock);
	list_del(&bo->client_link);
	spin_unlock(&client->bos_lock);

	xe_drm_client_put(client);
}

static void bo_meminfo(struct xe_bo *bo,
		       struct drm_memory_stats stats[TTM_NUM_MEM_TYPES])
{
	u64 sz = bo->size;
	u32 mem_type;

	if (bo->placement.placement)
		mem_type = bo->placement.placement->mem_type;
	else
		mem_type = XE_PL_TT;

	if (drm_gem_object_is_shared_for_memory_stats(&bo->ttm.base))
		stats[mem_type].shared += sz;
	else
		stats[mem_type].private += sz;

	if (xe_bo_has_pages(bo)) {
		stats[mem_type].resident += sz;

		if (!dma_resv_test_signaled(bo->ttm.base.resv,
					    DMA_RESV_USAGE_BOOKKEEP))
			stats[mem_type].active += sz;
		else if (mem_type == XE_PL_SYSTEM)
			stats[mem_type].purgeable += sz;
	}
}

static void show_meminfo(struct drm_printer *p, struct drm_file *file)
{
	struct drm_memory_stats stats[TTM_NUM_MEM_TYPES] = {};
	struct xe_file *xef = file->driver_priv;
	struct ttm_device *bdev = &xef->xe->ttm;
	struct ttm_resource_manager *man;
	struct xe_drm_client *client;
	struct drm_gem_object *obj;
	struct xe_bo *bo;
	unsigned int id;
	u32 mem_type;

	client = xef->client;

	/* Public objects. */
	spin_lock(&file->table_lock);
	idr_for_each_entry(&file->object_idr, obj, id) {
		struct xe_bo *bo = gem_to_xe_bo(obj);

		bo_meminfo(bo, stats);
	}
	spin_unlock(&file->table_lock);

	/* Internal objects. */
	spin_lock(&client->bos_lock);
	list_for_each_entry(bo, &client->bos_list, client_link) {
		if (!kref_get_unless_zero(&bo->ttm.base.refcount))
			continue;
		bo_meminfo(bo, stats);
		xe_bo_put(bo);
	}
	spin_unlock(&client->bos_lock);

	for (mem_type = XE_PL_SYSTEM; mem_type < TTM_NUM_MEM_TYPES; ++mem_type) {
		if (!xe_mem_type_to_name[mem_type])
			continue;

		man = ttm_manager_type(bdev, mem_type);

		if (man) {
			drm_print_memory_stats(p,
					       &stats[mem_type],
					       DRM_GEM_OBJECT_RESIDENT |
					       (mem_type != XE_PL_SYSTEM ? 0 :
					       DRM_GEM_OBJECT_PURGEABLE),
					       xe_mem_type_to_name[mem_type]);
		}
	}
}

static void show_run_ticks(struct drm_printer *p, struct drm_file *file)
{
	unsigned long class, i, gt_id, capacity[XE_ENGINE_CLASS_MAX] = { };
	struct xe_file *xef = file->driver_priv;
	struct xe_device *xe = xef->xe;
	struct xe_gt *gt;
	struct xe_hw_engine *hwe;
	struct xe_exec_queue *q;
	u64 gpu_timestamp;

	xe_pm_runtime_get(xe);

	/* Accumulate all the exec queues from this client */
	mutex_lock(&xef->exec_queue.lock);
	xa_for_each(&xef->exec_queue.xa, i, q) {
		xe_exec_queue_update_run_ticks(q);
		xef->run_ticks[q->class] += q->run_ticks - q->old_run_ticks;
		q->old_run_ticks = q->run_ticks;
	}
	mutex_unlock(&xef->exec_queue.lock);

	/* Get the total GPU cycles */
	for_each_gt(gt, xe, gt_id) {
		enum xe_force_wake_domains fw;

		hwe = xe_gt_any_hw_engine(gt);
		if (!hwe)
			continue;

		fw = xe_hw_engine_to_fw_domain(hwe);
		if (xe_force_wake_get(gt_to_fw(gt), fw)) {
			hwe = NULL;
			break;
		}

		gpu_timestamp = xe_hw_engine_read_timestamp(hwe);
		XE_WARN_ON(xe_force_wake_put(gt_to_fw(gt), fw));
		break;
	}

	xe_pm_runtime_put(xe);

	if (unlikely(!hwe))
		return;

	for (class = 0; class < XE_ENGINE_CLASS_MAX; class++) {
		const char *class_name;

		for_each_gt(gt, xe, gt_id)
			capacity[class] += gt->user_engines.instances_per_class[class];

		/*
		 * Engines may be fused off or not exposed to userspace. Don't
		 * return anything if this entire class is not available
		 */
		if (!capacity[class])
			continue;

		class_name = xe_hw_engine_class_to_str(class);
		drm_printf(p, "drm-cycles-%s:\t%llu\n",
			   class_name, xef->run_ticks[class]);
		drm_printf(p, "drm-total-cycles-%s:\t%llu\n",
			   class_name, gpu_timestamp);

		if (capacity[class] > 1)
			drm_printf(p, "drm-engine-capacity-%s:\t%lu\n",
				   class_name, capacity[class]);
	}
}

/**
 * xe_drm_client_fdinfo() - Callback for fdinfo interface
 * @p: The drm_printer ptr
 * @file: The drm_file ptr
 *
 * This is callabck for drm fdinfo interface. Register this callback
 * in drm driver ops for show_fdinfo.
 *
 * Return: void
 */
void xe_drm_client_fdinfo(struct drm_printer *p, struct drm_file *file)
{
	show_meminfo(p, file);
	show_run_ticks(p, file);
}
#endif
