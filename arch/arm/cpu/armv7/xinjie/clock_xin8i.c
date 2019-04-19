/*
 * sun6i specific clock code
 *
 * (C) Copyright 2007-2012
 * Allwinner Technology Co., Ltd. <www.allwinnertech.com>
 * Tom Cubie <tangliang@allwinnertech.com>
 *
 * (C) Copyright 2013 Luke Kenneth Casson Leighton <lkcl@lkcl.net>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <asm/io.h>
#include <asm/arch/clock.h>
#include <asm/arch/prcm.h>
#include <asm/arch/sys_proto.h>

#ifdef CONFIG_SPL_BUILD
void clock_init_safe(void)
{
	struct sunxi_ccm_reg * const ccm =
		(struct sunxi_ccm_reg *)SUNXI_CCM_BASE;

	clock_set_pll1(408000000); /*设置锁相环PLL_CPUX, 初始化CPU时钟*/

	writel(PLL6_CFG_DEFAULT, &ccm->pll6_cfg); 	/*设置锁相环PERIPHPLL，初始化PERIPH0时钟*/
	while (!(readl(&ccm->pll6_cfg) & CCM_PLL6_CTRL_LOCK)) /*等待时钟稳定*/
		;

	writel(AHB1_ABP1_DIV_DEFAULT, &ccm->ahb1_apb1_div); /* 初始化AHB1/APB1时钟, AHB1=PLL6/3,APB1=AHB1/2 */

	writel(MBUS_CLK_DEFAULT, &ccm->mbus0_clk_cfg); 	/*初始化MBUS时钟， PLL6/4 */
}
#endif

void clock_init_uart(void)
{
#if CONFIG_CONS_INDEX < 5
	struct sunxi_ccm_reg *const ccm =
		(struct sunxi_ccm_reg *)SUNXI_CCM_BASE;

	/* uart clock source is apb2 ，APB2初始化为24M, 串口的时钟源是APB2*/
	writel(APB2_CLK_SRC_OSC24M|
	       APB2_CLK_RATE_N_1|
	       APB2_CLK_RATE_M(1),
	       &ccm->apb2_div);

	/* open the clock for uart 打开串口时钟*/
	setbits_le32(&ccm->apb2_gate,
		     CLK_GATE_OPEN << (APB2_GATE_UART_SHIFT +
				       CONFIG_CONS_INDEX - 1));

	/* deassert uart reset 复位串口*/
	setbits_le32(&ccm->apb2_reset_cfg,
		     1 << (APB2_RESET_UART_SHIFT +
			   CONFIG_CONS_INDEX - 1));
#else
	/* enable R_PIO and R_UART clocks, and de-assert resets */
	prcm_apb0_enable(PRCM_APB0_GATE_PIO | PRCM_APB0_GATE_UART);
#endif
}


#ifdef CONFIG_SPL_BUILD
void clock_set_pll1(unsigned int clk)
{
	struct sunxi_ccm_reg * const ccm =
		(struct sunxi_ccm_reg *)SUNXI_CCM_BASE;
	const int p = 0;
	int k = 1;
	int m = 1;

	if (clk > 1152000000) {
		k = 2;
	} else if (clk > 768000000) {
		k = 3;
		m = 2;
	}

	/* Switch to 24MHz clock while changing PLL1 */
	/* 配置PLL1改变CPU时钟之前,通过CPUX_AXI_CFG_REG寄存器先将CPU配置成使用24M的外部晶振*/
	writel(AXI_DIV_3 << AXI_DIV_SHIFT |
	       ATB_DIV_2 << ATB_DIV_SHIFT |
	       CPU_CLK_SRC_OSC24M << CPU_CLK_SRC_SHIFT,
	       &ccm->cpu_axi_cfg);

	/*
	 * sun6i: PLL1 rate = ((24000000 * n * k) >> 0) / m   (p is ignored)
	 * sun8i: PLL1 rate = ((24000000 * n * k) >> p) / m
	 * 通过PLL_CPUX_CTRL_REG寄存器配置PLL1
	 */
	writel(CCM_PLL1_CTRL_EN | CCM_PLL1_CTRL_P(p) |
	       CCM_PLL1_CTRL_N(clk / (24000000 * k / m)) |
	       CCM_PLL1_CTRL_K(k) | CCM_PLL1_CTRL_M(m), &ccm->pll1_cfg);
	sdelay(200);

	/* Switch CPU to PLL1 ,通过CPUX_AXI_CFG_REG寄存器将使用外部24M时钟的CPU切换到使用PLL1提供的时钟*/
	writel(AXI_DIV_3 << AXI_DIV_SHIFT |
	       ATB_DIV_2 << ATB_DIV_SHIFT |
	       CPU_CLK_SRC_PLL1 << CPU_CLK_SRC_SHIFT,
	       &ccm->cpu_axi_cfg);
}
#endif

