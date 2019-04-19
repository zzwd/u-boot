/*
 * (C) Copyright 2007-2011
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * Tom Cubie <tangliang@allwinnertech.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CPU_XIN8I_H
#define __CPU_XIN8I_H

#define SUNXI_SRAM_A1_BASE		0x00000000
#define SUNXI_SRAM_A1_SIZE		(64 * 1024)	/* 64 kiB */

#define SUNXI_SRAM_A2_BASE		0x00044000
#define SUNXI_SRAM_A2_SIZE		(32 * 1024)	/* 64 kiB */

#define SUNXI_SRAM_C_BASE		0x00010000	
#define SUNXI_SRAM_C_SIZE		(44 * 1024)	/* 44 kiB */

#define SUNXI_SYS_CTRL			0x01c00000
#define SUNXI_DMA_BASE			0x01c02000
#define SUNXI_NFC_BASE			0x01c03000
#define SUNXI_TS_BASE			0x01c06000

#define SUNXI_CCM_BASE			0x01c20000
#define SUNXI_TZPC_BASE			0x01c23400
#define SUNXI_PRCM_BASE			0x01f01400

#ifndef __ASSEMBLY__
void xinjie_board_init(void);
void xinjie_reset(void);
int xinjie_get_ss_bonding_id(void);
int xinjie_get_sid(unsigned int *sid);
#endif /* __ASSEMBLY__ */

#endif /* __CPU_XIN8I_H */
