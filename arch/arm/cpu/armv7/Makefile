#
# (C) Copyright 2000-2003
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
#
# SPDX-License-Identifier:	GPL-2.0+
#

extra-y	:= start.o

obj-y	+= cache_v7.o

obj-y	+= cpu.o cp15.o
obj-y	+= syslib.o

ifneq ($(CONFIG_DEBUG_LED),)
obj-$(CONFIG_ARCH_XINJIE) 	+= debug_led.o
endif

ifneq ($(CONFIG_SUNXI)$(CONFIG_XINJIE),)
ifneq ($(CONFIG_SKIP_LOWLEVEL_INIT),y)
obj-y	+= lowlevel_init.o
endif
endif

ifneq ($(CONFIG_ARMV7_NONSEC),)
obj-y	+= nonsec_virt.o
obj-y	+= virt-v7.o
obj-y	+= virt-dt.o
endif

ifneq ($(CONFIG_ARMV7_PSCI),)
obj-y	+= psci.o
endif

obj-$(CONFIG_IPROC) += iproc-common/
obj-$(CONFIG_KONA) += kona-common/
obj-$(CONFIG_OMAP_COMMON) += omap-common/
obj-$(CONFIG_SYS_ARCH_TIMER) += arch_timer.o

obj-$(CONFIG_ARCH_XINJIE) += xinjie/
obj-$(CONFIG_ARCH_SUNXI) += sunxi/
