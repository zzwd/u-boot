/*
 * (C) Copyright 2014 Chen-Yu Tsai <wens@csie.org>
 *
 * Configuration settings for the Allwinner A23 (sun8i) CPU
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __XIN8I_CONFIG_H
#define __XIN8I_CONFIG_H

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

#ifdef CONFIG_XINJIE
#define CONFIG_DEBUG_LED
#endif

#ifdef CONFIG_SPL_BUILD
#define CONFIG_SYS_THUMB_BUILD	/* Thumbs mode to save space in SPL */
#endif


#define SDRAM_OFFSET(x) 0x4##x
#define CONFIG_SYS_SDRAM_BASE		0x40000000
#define CONFIG_SYS_LOAD_ADDR		0x42000000 /* default load address */
#define CONFIG_SYS_TEXT_BASE		0x4a000000
#define CONFIG_PRE_CON_BUF_ADDR 	0x4f000000
/* V3s do not have enough memory to place code at 0x4a000000 */
/* Note SPL_STACK_R_ADDR is set through Kconfig, we include it here 
 * since it needs to fit in with the other values. By also #defining it
 * we get warnings if the Kconfig value mismatches. */
#define CONFIG_SPL_STACK_R_ADDR		0x4fe00000
#define CONFIG_SPL_BSS_START_ADDR	0x4ff80000
#define CONFIG_SPL_BSS_MAX_SIZE		0x00080000 /* 512 KiB */

#define CONFIG_SPL_FRAMEWORK
#define CONFIG_SPL_LIBCOMMON_SUPPORT
#define CONFIG_SPL_LIBGENERIC_SUPPORT

/*
 *参考sunxi官网链接http://linux-sunxi.org/BROM，可以看到U-Boot SPL limitations部分
 *Allwinner H3
 *1、SPL size limit on MMC is 32 KiB，也就是CONFIG_SPL_MAX_SIZE参数不能大于32，这里设置成24KiB
 *2、SPL load address is 0x00000,也就是CONFIG_SPL_TEXT_BASE应该设置成0x00000，这里设置成0x60，最新版Uboot设置成0x20，
 *估计是考虑到SPL的校验头，我看了编译成功后的spl/u-boot-spl.map感觉没有必要，直接设置成0x00000即可
 *3、CONFIG_SPL_STACK参数设置成32KiB的位置，我们看Allwinner H3的数据手册可以SRAM A1的大小为64KiB，设置32KiB没有问题，
 *同时和SPL代码结束位置大约有8K（CONFIG_SPL_STACK-CONFIG_SPL_MAX_SIZE）作为堆栈容量
 */
#define CONFIG_SPL_TEXT_BASE		0x60		/* sram start+header */
#define CONFIG_SPL_MAX_SIZE			0x5fa0		/* 24KB on sun4i/sun7i */
#define LOW_LEVEL_SRAM_STACK		0x00008000	/* End of sram */

#define CONFIG_SPL_STACK		LOW_LEVEL_SRAM_STACK

#define CONFIG_SPL_PAD_TO		32768		/* decimal for 'dd' */

#define CONFIG_SYS_INIT_RAM_ADDR	0x0
#define CONFIG_SYS_INIT_RAM_SIZE	0x8000	/* 32 KiB */

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

#define CONFIG_SYS_NO_FLASH

#define CONFIG_ENV_SIZE 	0x20000


#define CONFIG_NR_DRAM_BANKS		1

 /* 2MB of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(CONFIG_ENV_SIZE + (2 << 20))

#define CONFIG_SYS_MAXARGS	16	/* max number of command args */

#define CONFIG_ENV_IS_NOWHERE
#define CONFIG_SYS_CBSIZE	1024	/* Console I/O Buffer Size */

#define CONFIG_SYS_GENERIC_BOARD

/* baudrate */
#define CONFIG_BAUDRATE			115200

#define CONFIG_SPL_LDSCRIPT "arch/arm/cpu/armv7/xinjie/u-boot-spl.lds"




#ifndef CONFIG_SPL_BUILD
#include <config_distro_defaults.h>

/* Enable pre-console buffer to get complete log on the VGA console */
#define CONFIG_PRE_CONSOLE_BUFFER
#define CONFIG_PRE_CON_BUF_SZ		4096 /* Aprox 2 80*25 screens */

/*
 * 160M RAM (256M minimum minus 64MB heap + 32MB for u-boot, stack, fb, etc.
 * 32M uncompressed kernel, 16M compressed kernel, 1M fdt,
 * 1M script, 1M pxe and the ramdisk at the end.
 */
#define MEM_LAYOUT_ENV_SETTINGS \
	"bootm_size=0xa000000\0" \
	"kernel_addr_r=" __stringify(SDRAM_OFFSET(2000000)) "\0" \
	"fdt_addr_r=" __stringify(SDRAM_OFFSET(3000000)) "\0" \
	"scriptaddr=" __stringify(SDRAM_OFFSET(3100000)) "\0" \
	"pxefile_addr_r=" __stringify(SDRAM_OFFSET(3200000)) "\0" \
	"ramdisk_addr_r=" __stringify(SDRAM_OFFSET(3300000)) "\0"

#ifdef CONFIG_MMC
#define BOOT_TARGET_DEVICES_MMC(func) func(MMC, mmc, 0)
#else
#define BOOT_TARGET_DEVICES_MMC(func)
#endif

#ifdef CONFIG_AHCI
#define BOOT_TARGET_DEVICES_SCSI(func) func(SCSI, scsi, 0)
#else
#define BOOT_TARGET_DEVICES_SCSI(func)
#endif

#ifdef CONFIG_USB_STORAGE
#define BOOT_TARGET_DEVICES_USB(func) func(USB, usb, 0)
#else
#define BOOT_TARGET_DEVICES_USB(func)
#endif

/* FEL boot support, auto-execute boot.scr if a script address was provided */
#define BOOTENV_DEV_FEL(devtypeu, devtypel, instance) \
	"bootcmd_fel=" \
		"if test -n ${fel_booted} && test -n ${fel_scriptaddr}; then " \
			"echo '(FEL boot)'; " \
			"source ${fel_scriptaddr}; " \
		"fi\0"
#define BOOTENV_DEV_NAME_FEL(devtypeu, devtypel, instance) \
	"fel "
/* FEL boot support, auto-execute boot.scr if a script address was provided */
#define BOOTENV_DEV_FEL(devtypeu, devtypel, instance) \
	"bootcmd_fel=" \
		"if test -n ${fel_booted} && test -n ${fel_scriptaddr}; then " \
			"echo '(FEL boot)'; " \
			"source ${fel_scriptaddr}; " \
		"fi\0"
#define BOOTENV_DEV_NAME_FEL(devtypeu, devtypel, instance) \
	"fel "

#define BOOT_TARGET_DEVICES(func) \
	func(FEL, fel, na) \
	BOOT_TARGET_DEVICES_MMC(func) \
	BOOT_TARGET_DEVICES_SCSI(func) \
	BOOT_TARGET_DEVICES_USB(func) \
	func(PXE, pxe, na) \
	func(DHCP, dhcp, na)

#include <config_distro_bootcmd.h>

#ifdef CONFIG_USB_KEYBOARD
#define CONSOLE_STDIN_SETTINGS \
	"preboot=usb start\0" \
	"stdin=serial,usbkbd\0"
#else
#define CONSOLE_STDIN_SETTINGS \
	"stdin=serial\0"
#endif

#ifdef CONFIG_VIDEO
#define CONSOLE_STDOUT_SETTINGS \
	"stdout=serial,vga\0" \
	"stderr=serial,vga\0"
#else
#define CONSOLE_STDOUT_SETTINGS \
	"stdout=serial\0" \
	"stderr=serial\0"
#endif	
#define CONSOLE_ENV_SETTINGS \
	CONSOLE_STDIN_SETTINGS \
	CONSOLE_STDOUT_SETTINGS

#define CONFIG_EXTRA_ENV_SETTINGS \
	CONSOLE_ENV_SETTINGS \
	MEM_LAYOUT_ENV_SETTINGS \
	"fdtfile=" CONFIG_DEFAULT_DEVICE_TREE ".dtb\0" \
	"console=ttyS0,115200\0" \
	BOOTENV

#else /* ifndef CONFIG_SPL_BUILD */
#define CONFIG_EXTRA_ENV_SETTINGS
#endif

#endif /* __XIN8I_CONFIG_H */
