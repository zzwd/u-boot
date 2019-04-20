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

#include <asm/arch/gpio.h>
#include <asm/arch/clock.h>
#include <asm/arch/tzpc.h>

#include <linux/compiler.h>

static int gpio_init(void)
{
	/*配置UART0*/
#if CONFIG_CONS_INDEX == 1 && defined(CONFIG_MACH_XINJIE_H3)
	sunxi_gpio_set_cfgpin(SUNXI_GPA(4), SUN8I_H3_GPA_UART0);
	sunxi_gpio_set_cfgpin(SUNXI_GPA(5), SUN8I_H3_GPA_UART0);
	sunxi_gpio_set_pull(SUNXI_GPA(5), SUNXI_GPIO_PULL_UP);
#else
#error Unsupported console port number. Please fix pin mux settings in board.c
#endif

	return 0;
}

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
	timer_init();	/*定时器初始化*/
					/*看门狗默认是关闭的，可查看allwinner H3数据手册4.6 Timer/4.6.4小节中*/
	gpio_init(); 	/*GPIO 初始化*/
	/*
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
	preloader_console_init(); /*console初始化*/

#ifdef CONFIG_SPL_I2C_SUPPORT
	/* Needed early by sunxi_board_init if PMU is enabled */
	//i2c_init(CONFIG_SYS_I2C_SPEED, CONFIG_SYS_I2C_SLAVE);
#endif
	//sunxi_board_init();
}
#endif

void reset_cpu(ulong addr)
{


}



