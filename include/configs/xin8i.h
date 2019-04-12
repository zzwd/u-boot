/*
 * (C) Copyright 2014 Chen-Yu Tsai <wens@csie.org>
 *
 * Configuration settings for the Allwinner A23 (sun8i) CPU
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _XIN8I_CONFIG_H
#define _XIN8I_CONFIG_H

#include <asm/arch/cpu.h>
#include <linux/stringify.h>

#ifdef CONFIG_OLD_SUNXI_KERNEL_COMPAT
/*
 * The U-Boot workarounds bugs in the outdated buggy sunxi-3.4 kernels at the
 * expense of restricting some features, so the regular machine id values can
 * be used.
 */
# define CONFIG_MACH_TYPE_COMPAT_REV	0
#else
/*
 * A compatibility guard to prevent loading outdated buggy sunxi-3.4 kernels.
 * Only sunxi-3.4 kernels with appropriate fixes applied are able to pass
 * beyond the machine id check.
 */
# define CONFIG_MACH_TYPE_COMPAT_REV	1
#endif

#define CONFIG_ARMV7_PSCI		1
#define CONFIG_ARMV7_PSCI_NR_CPUS	4

/*
 * High Level Configuration Options
 */
#define CONFIG_XINJIE		/* xinjie family */
#ifdef CONFIG_SPL_BUILD
#define CONFIG_SYS_THUMB_BUILD	/* Thumbs mode to save space in SPL */
#endif


#define SDRAM_OFFSET(x) 0x4##x
#define CONFIG_SYS_SDRAM_BASE		0x40000000
#define CONFIG_SYS_LOAD_ADDR		0x42000000 /* default load address */
#define CONFIG_SYS_TEXT_BASE		0x4a000000
/* V3s do not have enough memory to place code at 0x4a000000 */
/* Note SPL_STACK_R_ADDR is set through Kconfig, we include it here 
 * since it needs to fit in with the other values. By also #defining it
 * we get warnings if the Kconfig value mismatches. */
#define CONFIG_SPL_STACK_R_ADDR		0x4fe00000
#define CONFIG_SPL_BSS_START_ADDR	0x4ff80000

#define CONFIG_SYS_INIT_RAM_ADDR	0x0
#define CONFIG_SYS_INIT_RAM_SIZE	0x8000	/* 32 KiB */

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM_0			CONFIG_SYS_SDRAM_BASE
#define PHYS_SDRAM_0_SIZE		0x80000000 /* 2 GiB */

#define CONFIG_SYS_NO_FLASH

#define CONFIG_ENV_SIZE 	0x20000

/* mmc config */
#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_SYS_MMC_ENV_DEV		0	/* first detected MMC controller */

/*
 * Miscellaneous configurable options
 */
#define CONFIG_SYS_CBSIZE	1024	/* Console I/O Buffer Size */

#define CONFIG_SYS_GENERIC_BOARD

/* baudrate */
#define CONFIG_BAUDRATE			115200
 
 /* 2MB of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + (2 << 20))

#define CONFIG_SYS_MAXARGS	16	/* max number of command args */

/* mmc config */
#define CONFIG_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_CMD_MMC
#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_SYS_MMC_ENV_DEV		0	/* first detected MMC controller */


#define CONFIG_SPL_LDSCRIPT "arch/arm/cpu/armv7/xinjie/u-boot-spl.lds"

#ifndef CONFIG_SPL_BUILD
#include <config_distro_defaults.h>

#include <config_distro_bootcmd.h>

#else /* ifndef CONFIG_SPL_BUILD */

#endif


#endif /* _XIN8I_CONFIG_H */
