/*
 * (C) Copyright 2007-2011
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * Tom Cubie <tangliang@allwinnertech.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _XINJIE_CLOCK_H
#define _XINJIE_CLOCK_H

#include <linux/types.h>

#define CLK_GATE_OPEN			0x1
#define CLK_GATE_CLOSE			0x0


#ifndef __ASSEMBLY__
int clock_init(void);
int clock_twi_onoff(int port, int state);
void clock_set_de_mod_clock(u32 *clk_cfg, unsigned int hz);
void clock_init_safe(void);
void clock_init_uart(void);
#endif

#endif /* _XINJIE_CLOCK_H */
