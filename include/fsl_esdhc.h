/*
 * FSL SD/MMC Defines
 *-------------------------------------------------------------------
 *
 * Copyright 2007-2008, 2010-2016 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef  __FSL_ESDHC_H__
#define	__FSL_ESDHC_H__

#include "io.h"
#include "mmc.h"


struct fsl_esdhc_cfg {
	u32	esdhc_base;
	u32	sdhc_clk;
	u8	max_bus_width;
	u8	wp_enable;
	struct mmc_config cfg;
};

int fsl_esdhc_initialize(struct fsl_esdhc_cfg *cfg);

#endif  /* __FSL_ESDHC_H__ */
