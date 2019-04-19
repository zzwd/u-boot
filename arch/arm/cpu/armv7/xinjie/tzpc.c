// SPDX-License-Identifier: GPL-2.0+
/*
 * (C) Copyright 2015 Chen-Yu Tsai <wens@csie.org>
 */

#include <asm/io.h>
#include <asm/arch/cpu.h>
#include <asm/arch/tzpc.h>

/* Configure Trust Zone Protection Controller */
void tzpc_init(void)
{
	struct sunxi_tzpc *tzpc = (struct sunxi_tzpc *)SUNXI_TZPC_BASE;

	/* Enable non-secure access to all peripherals */
	writel(SUN8I_H3_TZPC_DECPORT0_ALL, &tzpc->decport0_set);
	writel(SUN8I_H3_TZPC_DECPORT1_ALL, &tzpc->decport1_set);
	writel(SUN8I_H3_TZPC_DECPORT2_ALL, &tzpc->decport2_set);
}
