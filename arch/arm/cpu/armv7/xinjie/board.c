/*
 * (C) Copyright 2012 Henrik Nordstrom <henrik@henriknordstrom.net>
 *
 * (C) Copyright 2007-2011
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * Tom Cubie <tangliang@allwinnertech.com>
 *
 * Some init for sunxi platform.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#include <common.h>
#ifdef CONFIG_SPL_BUILD
#include <spl.h>
#endif

#include <asm/arch/clock.h>
#include <asm/arch/tzpc.h>

#include <linux/compiler.h>


void s_init(void)
{
	/* Enable SMP mode for CPU0, by setting bit 6 of Auxiliary Ctl reg */
	asm volatile(
		"mrc p15, 0, r0, c1, c0, 1\n"
		"orr r0, r0, #1 << 6\n"
		"mcr p15, 0, r0, c1, c0, 1\n");

	/* Enable non-secure access to some peripherals */
	tzpc_init(); 	/*启用对所有外围设备的非安全访问*/
	clock_init(); 	/*PLL时钟初始化*/
	/*
	timer_init();
	gpio_init();
	i2c_init_board();
	*/
}

#ifdef CONFIG_SPL_BUILD
u32 spl_boot_device(void)
{
	return -1;		/* Never reached */
}

void board_init_f(ulong dummy)
{
	
}
#endif

void reset_cpu(ulong addr)
{


}



