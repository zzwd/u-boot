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
#include <mmc.h>
#include <i2c.h>
#include <serial.h>
#ifdef CONFIG_SPL_BUILD
#include <spl.h>
#endif
#include <asm/gpio.h>
#include <asm/io.h>
#include <asm/arch/gpio.h>
#include <asm/arch/spl.h>

#include <linux/compiler.h>


void s_init(void)
{

}

#ifdef CONFIG_SPL_BUILD
void board_init_f(ulong dummy)
{
	
}

#endif

void reset_cpu(ulong addr)
{


}



