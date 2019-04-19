/*
 * (C) Copyright 2014
 * Chen-Yu Tsai <wens@csie.org>
 *
 * Watchdog register definitions
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _XINJIE_WATCHDOG_H_
#define _XINJIE_WATCHDOG_H_

#define WDT_CTRL_RESTART	(0x1 << 0)
#define WDT_CTRL_KEY		(0x0a57 << 1)

#define WDT_CFG_RESET		(0x1)
#define WDT_MODE_EN		(0x1)

struct sunxi_wdog {
	u32 irq_en;		/* 0x00 */
	u32 irq_sta;		/* 0x04 */
	u32 res1[2];
	u32 ctl;		/* 0x10 */
	u32 cfg;		/* 0x14 */
	u32 mode;		/* 0x18 */
	u32 res2;
};

#endif /* _XINJIE_WATCHDOG_H_ */
