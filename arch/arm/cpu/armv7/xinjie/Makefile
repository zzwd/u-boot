# SPDX-License-Identifier: GPL-2.0+
#
# (C) Copyright 2012 Henrik Nordstrom <henrik@henriknordstrom.net>
#
# Based on some other Makefile
# (C) Copyright 2000-2003
# Wolfgang Denk, DENX Software Engineering, wd@denx.de.
obj-y	+= timer.o
obj-y	+= board.o

ifndef CONFIG_SPL_BUILD
ifdef CONFIG_ARMV7_PSCI
obj-y	+= psci.o
endif
endif

