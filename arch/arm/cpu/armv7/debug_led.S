/*
 * A debug_led function that debug ASM programme
 *only use Allinner H3 Soc
 * (C) Copyright 2010
 *
 * Author :zzw
 *	Aneesh V	<aneesh@ti.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */


#include <linux/linkage.h>

#define PACFG1		0x01C20804
#define PADAT		0x01C20810

ENTRY(debug_led)

led_on :
	ldr r0, = 0x17777777   	/* 这里ldr 为伪指令 */
    ldr r1, = PACFG1
    str r0, [r1]          	/* 寄存器间接寻址 将r0的值给r1所指地址的内存中,配置GPIO PA15为输出模式  */

    ldr r0, = (1<<15) 	  	/* PA15, 在数据寄存器的第15位输出高电平 */
    ldr r1, = PADAT
    str r0, [r1]          	/* 点亮 */
    mov pc, lr 				/* 返回*/

ENDPROC(debug_led)
