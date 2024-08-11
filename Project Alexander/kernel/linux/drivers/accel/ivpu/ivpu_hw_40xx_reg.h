/* SPDX-License-Identifier: GPL-2.0-only */
/*
 * Copyright (C) 2020-2023 Intel Corporation
 */

#ifndef __IVPU_HW_40XX_REG_H__
#define __IVPU_HW_40XX_REG_H__

#include <linux/bits.h>

#define VPU_40XX_HOST_SS_CPR_CLK_EN					0x00000080u
#define VPU_40XX_HOST_SS_CPR_CLK_EN_TOP_NOC_MASK			BIT_MASK(1)
#define VPU_40XX_HOST_SS_CPR_CLK_EN_DSS_MAS_MASK			BIT_MASK(10)
#define VPU_40XX_HOST_SS_CPR_CLK_EN_CSS_MAS_MASK			BIT_MASK(11)

#define VPU_40XX_HOST_SS_CPR_CLK_SET					0x00000084u
#define VPU_40XX_HOST_SS_CPR_CLK_SET_TOP_NOC_MASK			BIT_MASK(1)
#define VPU_40XX_HOST_SS_CPR_CLK_SET_DSS_MAS_MASK			BIT_MASK(10)
#define VPU_40XX_HOST_SS_CPR_CLK_SET_MSS_MAS_MASK			BIT_MASK(11)

#define VPU_40XX_HOST_SS_CPR_RST_EN					0x00000090u
#define VPU_40XX_HOST_SS_CPR_RST_EN_TOP_NOC_MASK			BIT_MASK(1)
#define VPU_40XX_HOST_SS_CPR_RST_EN_DSS_MAS_MASK			BIT_MASK(10)
#define VPU_40XX_HOST_SS_CPR_RST_EN_CSS_MAS_MASK			BIT_MASK(11)

#define VPU_40XX_HOST_SS_CPR_RST_SET					0x00000094u
#define VPU_40XX_HOST_SS_CPR_RST_SET_TOP_NOC_MASK			BIT_MASK(1)
#define VPU_40XX_HOST_SS_CPR_RST_SET_DSS_MAS_MASK			BIT_MASK(10)
#define VPU_40XX_HOST_SS_CPR_RST_SET_MSS_MAS_MASK			BIT_MASK(11)

#define VPU_40XX_HOST_SS_CPR_RST_CLR					0x00000098u
#define VPU_40XX_HOST_SS_CPR_RST_CLR_TOP_NOC_MASK			BIT_MASK(1)
#define VPU_40XX_HOST_SS_CPR_RST_CLR_DSS_MAS_MASK			BIT_MASK(10)
#define VPU_40XX_HOST_SS_CPR_RST_CLR_MSS_MAS_MASK			BIT_MASK(11)

#define VPU_40XX_HOST_SS_HW_VERSION					0x00000108u
#define VPU_40XX_HOST_SS_HW_VERSION_SOC_REVISION_MASK			GENMASK(7, 0)
#define VPU_40XX_HOST_SS_HW_VERSION_SOC_NUMBER_MASK			GENMASK(15, 8)
#define VPU_40XX_HOST_SS_HW_VERSION_VPU_GENERATION_MASK			GENMASK(23, 16)

#define VPU_40XX_HOST_SS_SW_VERSION					0x0000010cu

#define VPU_40XX_HOST_SS_GEN_CTRL					0x00000118u
#define VPU_40XX_HOST_SS_GEN_CTRL_PS_MASK				GENMASK(31, 29)

#define VPU_40XX_HOST_SS_NOC_QREQN					0x00000154u
#define VPU_40XX_HOST_SS_NOC_QREQN_TOP_SOCMMIO_MASK			BIT_MASK(0)

#define VPU_40XX_HOST_SS_NOC_QACCEPTN					0x00000158u
#define VPU_40XX_HOST_SS_NOC_QACCEPTN_TOP_SOCMMIO_MASK			BIT_MASK(0)

#define VPU_40XX_HOST_SS_NOC_QDENY					0x0000015cu
#define VPU_40XX_HOST_SS_NOC_QDENY_TOP_SOCMMIO_MASK			BIT_MASK(0)

#define VPU_40XX_TOP_NOC_QREQN						0x00000160u
#define VPU_40XX_TOP_NOC_QREQN_CPU_CTRL_MASK				BIT_MASK(0)
#define VPU_40XX_TOP_NOC_QREQN_HOSTIF_L2CACHE_MASK			BIT_MASK(2)

#define VPU_40XX_TOP_NOC_QACCEPTN					0x00000164u
#define VPU_40XX_TOP_NOC_QACCEPTN_CPU_CTRL_MASK				BIT_MASK(0)
#define VPU_40XX_TOP_NOC_QACCEPTN_HOSTIF_L2CACHE_MASK			BIT_MASK(2)

#define VPU_40XX_TOP_NOC_QDENY						0x00000168u
#define VPU_40XX_TOP_NOC_QDENY_CPU_CTRL_MASK				BIT_MASK(0)
#define VPU_40XX_TOP_NOC_QDENY_HOSTIF_L2CACHE_MASK			BIT_MASK(2)

#define VPU_40XX_HOST_SS_FW_SOC_IRQ_EN					0x00000170u
#define VPU_40XX_HOST_SS_FW_SOC_IRQ_EN_CSS_ROM_CMX_MASK			BIT_MASK(0)
#define VPU_40XX_HOST_SS_FW_SOC_IRQ_EN_CSS_DBG_MASK			BIT_MASK(1)
#define VPU_40XX_HOST_SS_FW_SOC_IRQ_EN_CSS_CTRL_MASK			BIT_MASK(2)
#define VPU_40XX_HOST_SS_FW_SOC_IRQ_EN_DEC400_MASK			BIT_MASK(3)
#define VPU_40XX_HOST_SS_FW_SOC_IRQ_EN_MSS_NCE_MASK			BIT_MASK(4)
#define VPU_40XX_HOST_SS_FW_SOC_IRQ_EN_MSS_MBI_MASK			BIT_MASK(5)
#define VPU_40XX_HOST_SS_FW_SOC_IRQ_EN_MSS_MBI_CMX_MASK			BIT_MASK(6)

#define VPU_40XX_HOST_SS_ICB_STATUS_0					0x00010210u
#define VPU_40XX_HOST_SS_ICB_STATUS_0_TIMER_0_INT_MASK			BIT_MASK(0)
#define VPU_40XX_HOST_SS_ICB_STATUS_0_TIMER_1_INT_MASK			BIT_MASK(1)
#define VPU_40XX_HOST_SS_ICB_STATUS_0_TIMER_2_INT_MASK			BIT_MASK(2)
#define VPU_40XX_HOST_SS_ICB_STATUS_0_TIMER_3_INT_MASK			BIT_MASK(3)
#define VPU_40XX_HOST_SS_ICB_STATUS_0_HOST_IPC_FIFO_INT_MASK		BIT_MASK(4)
#define VPU_40XX_HOST_SS_ICB_STATUS_0_MMU_IRQ_0_INT_MASK		BIT_MASK(5)
#define VPU_40XX_HOST_SS_ICB_STATUS_0_MMU_IRQ_1_INT_MASK		BIT_MASK(6)
#define VPU_40XX_HOST_SS_ICB_STATUS_0_MMU_IRQ_2_INT_MASK		BIT_MASK(7)
#define VPU_40XX_HOST_SS_ICB_STATUS_0_NOC_FIREWALL_INT_MASK		BIT_MASK(8)
#define VPU_40XX_HOST_SS_ICB_STATUS_0_CPU_INT_REDIRECT_0_INT_MASK	BIT_MASK(30)
#define VPU_40XX_HOST_SS_ICB_STATUS_0_CPU_INT_REDIRECT_1_INT_MASK	BIT_MASK(31)

#define VPU_40XX_HOST_SS_ICB_STATUS_1					0x00010214u
#define VPU_40XX_HOST_SS_ICB_STATUS_1_CPU_INT_REDIRECT_2_INT_MASK	BIT_MASK(0)
#define VPU_40XX_HOST_SS_ICB_STATUS_1_CPU_INT_REDIRECT_3_INT_MASK	BIT_MASK(1)
#define VPU_40XX_HOST_SS_ICB_STATUS_1_CPU_INT_REDIRECT_4_INT_MASK	BIT_MASK(2)

#define VPU_40XX_HOST_SS_ICB_CLEAR_0					0x00010220u
#define VPU_40XX_HOST_SS_ICB_CLEAR_1					0x00010224u
#define VPU_40XX_HOST_SS_ICB_ENABLE_0					0x00010240u
#define VPU_40XX_HOST_SS_ICB_ENABLE_1					0x00010244u

#define VPU_40XX_HOST_SS_TIM_IPC_FIFO_ATM				0x000200f4u

#define VPU_40XX_HOST_SS_TIM_IPC_FIFO_STAT				0x000200fcu
#define VPU_40XX_HOST_SS_TIM_IPC_FIFO_STAT_FILL_LEVEL_MASK		GENMASK(23, 16)

#define VPU_40XX_HOST_SS_AON_PWR_ISO_EN0				0x00030020u
#define VPU_40XX_HOST_SS_AON_PWR_ISO_EN0_CSS_CPU_MASK			BIT_MASK(3)

#define VPU_40XX_HOST_SS_AON_PWR_ISLAND_EN0				0x00030024u
#define VPU_40XX_HOST_SS_AON_PWR_ISLAND_EN0_CSS_CPU_MASK		BIT_MASK(3)

#define VPU_40XX_HOST_SS_AON_PWR_ISLAND_TRICKLE_EN0			0x00030028u
#define VPU_40XX_HOST_SS_AON_PWR_ISLAND_TRICKLE_EN0_CSS_CPU_MASK	BIT_MASK(3)

#define VPU_40XX_HOST_SS_AON_PWR_ISLAND_STATUS0				0x0003002cu
#define VPU_40XX_HOST_SS_AON_PWR_ISLAND_STATUS0_CSS_CPU_MASK		BIT_MASK(3)

#define VPU_50XX_HOST_SS_AON_PWR_ISLAND_EN_POST_DLY			0x00030068u
#define VPU_50XX_HOST_SS_AON_PWR_ISLAND_EN_POST_DLY_POST_DLY_MASK	GENMASK(7, 0)

#define VPU_50XX_HOST_SS_AON_PWR_ISLAND_STATUS_DLY			0x0003006cu
#define VPU_50XX_HOST_SS_AON_PWR_ISLAND_STATUS_DLY_STATUS_DLY_MASK	GENMASK(7, 0)

#define VPU_40XX_HOST_SS_AON_IDLE_GEN					0x00030200u
#define VPU_40XX_HOST_SS_AON_IDLE_GEN_EN_MASK				BIT_MASK(0)
#define VPU_40XX_HOST_SS_AON_IDLE_GEN_HW_PG_EN_MASK			BIT_MASK(1)

#define VPU_40XX_HOST_SS_AON_DPU_ACTIVE					0x00030204u
#define VPU_40XX_HOST_SS_AON_DPU_ACTIVE_DPU_ACTIVE_MASK			BIT_MASK(0)

#define VPU_50XX_HOST_SS_AON_FABRIC_REQ_OVERRIDE			0x00030210u
#define VPU_50XX_HOST_SS_AON_FABRIC_REQ_OVERRIDE_REQ_OVERRIDE_MASK      BIT_MASK(0)

#define VPU_40XX_HOST_SS_VERIFICATION_ADDRESS_LO			0x00040040u
#define VPU_40XX_HOST_SS_VERIFICATION_ADDRESS_LO_DONE_MASK		BIT_MASK(0)
#define VPU_40XX_HOST_SS_VERIFICATION_ADDRESS_LO_IOSF_RS_ID_MASK	GENMASK(2, 1)
#define VPU_40XX_HOST_SS_VERIFICATION_ADDRESS_LO_IMAGE_LOCATION_MASK	GENMASK(31, 3)

#define VPU_40XX_HOST_SS_WORKPOINT_CONFIG_MIRROR			0x00082020u
#define VPU_40XX_HOST_SS_WORKPOINT_CONFIG_MIRROR_FINAL_PLL_FREQ_MASK	GENMASK(15, 0)
#define VPU_40XX_HOST_SS_WORKPOINT_CONFIG_MIRROR_CONFIG_ID_MASK		GENMASK(31, 16)

#define VPU_40XX_HOST_IF_TCU_PTW_OVERRIDES				0x00360000u
#define VPU_40XX_HOST_IF_TCU_PTW_OVERRIDES_CACHE_OVERRIDE_EN_MASK	BIT_MASK(0)
#define VPU_40XX_HOST_IF_TCU_PTW_OVERRIDES_AWCACHE_OVERRIDE_MASK	BIT_MASK(1)
#define VPU_40XX_HOST_IF_TCU_PTW_OVERRIDES_ARCACHE_OVERRIDE_MASK	BIT_MASK(2)
#define VPU_40XX_HOST_IF_TCU_PTW_OVERRIDES_SNOOP_OVERRIDE_EN_MASK	BIT_MASK(3)
#define VPU_40XX_HOST_IF_TCU_PTW_OVERRIDES_AW_SNOOP_OVERRIDE_MASK	BIT_MASK(4)
#define VPU_40XX_HOST_IF_TCU_PTW_OVERRIDES_AR_SNOOP_OVERRIDE_MASK	BIT_MASK(5)
#define VPU_40XX_HOST_IF_TCU_PTW_OVERRIDES_PTW_AW_CONTEXT_FLAG_MASK	GENMASK(10, 6)
#define VPU_40XX_HOST_IF_TCU_PTW_OVERRIDES_PTW_AR_CONTEXT_FLAG_MASK	GENMASK(15, 11)

#define VPU_40XX_HOST_IF_TBU_MMUSSIDV					0x00360004u
#define VPU_40XX_HOST_IF_TBU_MMUSSIDV_TBU0_AWMMUSSIDV_MASK		BIT_MASK(0)
#define VPU_40XX_HOST_IF_TBU_MMUSSIDV_TBU0_ARMMUSSIDV_MASK		BIT_MASK(1)
#define VPU_40XX_HOST_IF_TBU_MMUSSIDV_TBU1_AWMMUSSIDV_MASK		BIT_MASK(2)
#define VPU_40XX_HOST_IF_TBU_MMUSSIDV_TBU1_ARMMUSSIDV_MASK		BIT_MASK(3)
#define VPU_40XX_HOST_IF_TBU_MMUSSIDV_TBU2_AWMMUSSIDV_MASK		BIT_MASK(4)
#define VPU_40XX_HOST_IF_TBU_MMUSSIDV_TBU2_ARMMUSSIDV_MASK		BIT_MASK(5)
#define VPU_40XX_HOST_IF_TBU_MMUSSIDV_TBU3_AWMMUSSIDV_MASK		BIT_MASK(6)
#define VPU_40XX_HOST_IF_TBU_MMUSSIDV_TBU3_ARMMUSSIDV_MASK		BIT_MASK(7)
#define VPU_40XX_HOST_IF_TBU_MMUSSIDV_TBU4_AWMMUSSIDV_MASK		BIT_MASK(8)
#define VPU_40XX_HOST_IF_TBU_MMUSSIDV_TBU4_ARMMUSSIDV_MASK		BIT_MASK(9)

#define VPU_40XX_CPU_SS_DSU_LEON_RT_BASE				0x04000000u
#define VPU_40XX_CPU_SS_DSU_LEON_RT_DSU_CTRL				0x04000000u
#define VPU_40XX_CPU_SS_DSU_LEON_RT_PC_REG				0x04400010u
#define VPU_40XX_CPU_SS_DSU_LEON_RT_NPC_REG				0x04400014u
#define VPU_40XX_CPU_SS_DSU_LEON_RT_DSU_TRAP_REG			0x04400020u

#define VPU_40XX_CPU_SS_TIM_WATCHDOG					0x0102009cu
#define VPU_40XX_CPU_SS_TIM_WDOG_EN					0x010200a4u
#define VPU_40XX_CPU_SS_TIM_SAFE					0x010200a8u

#define VPU_40XX_CPU_SS_TIM_GEN_CONFIG					0x01021008u
#define VPU_40XX_CPU_SS_TIM_GEN_CONFIG_WDOG_TO_INT_CLR_MASK		BIT_MASK(9)

#define VPU_40XX_CPU_SS_CPR_NOC_QREQN					0x01010030u
#define VPU_40XX_CPU_SS_CPR_NOC_QREQN_TOP_MMIO_MASK			BIT_MASK(0)

#define VPU_40XX_CPU_SS_CPR_NOC_QACCEPTN				0x01010034u
#define VPU_40XX_CPU_SS_CPR_NOC_QACCEPTN_TOP_MMIO_MASK			BIT_MASK(0)

#define VPU_40XX_CPU_SS_CPR_NOC_QDENY					0x01010038u
#define VPU_40XX_CPU_SS_CPR_NOC_QDENY_TOP_MMIO_MASK			BIT_MASK(0)

#define VPU_40XX_CPU_SS_TIM_IPC_FIFO					0x010200f0u
#define VPU_40XX_CPU_SS_TIM_PERF_EXT_FREE_CNT				0x01029008u

#define VPU_40XX_CPU_SS_DOORBELL_0					0x01300000u
#define VPU_40XX_CPU_SS_DOORBELL_0_SET_MASK				BIT_MASK(0)

#define VPU_40XX_CPU_SS_DOORBELL_1					0x01301000u

#endif /* __IVPU_HW_40XX_REG_H__ */
