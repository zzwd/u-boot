// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2007-2011
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * Tom Cubie <tangliang@allwinnertech.com>
 */

/*
 * This function is derived from PowerPC code (timebase clock frequency).
 * On ARM it returns the number of timer ticks per second.
 */
#include <common.h>

DECLARE_GLOBAL_DATA_PTR;

/* init timer register */
int timer_init(void)
{

	return 0;
}


ulong get_tbclk(void)
{
	return CONFIG_SYS_HZ;
}