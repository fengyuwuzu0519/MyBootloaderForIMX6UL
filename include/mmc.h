/*
 * Copyright 2008,2010 Freescale Semiconductor, Inc
 * Andy Fleming
 *
 * Based (loosely) on the Linux code
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _MMC_H_
#define _MMC_H_

#include "io.h"
#include "list.h"

struct mmc_config {
	const char *name;
	const struct mmc_ops *ops;
	uint host_caps;
	uint voltages;
	uint f_min;
	uint f_max;
	uint b_max;
	unsigned char part_type;
};

struct mmc {
	struct list_head link;
	const struct mmc_config *cfg;	/* provided configuration */
	uint version;
	void *priv;
	uint has_init;
	int high_capacity;
	uint bus_width;
	uint clock;
	uint card_caps;
	uint ocr;
	uint dsr;
	uint dsr_imp;
	uint scr[2];
	uint csd[4];
	uint cid[4];
	ushort rca;
	u8 part_support;
	u8 part_attr;
	u8 wr_rel_set;
	char part_config;
	uint tran_speed;
	uint read_bl_len;
	uint write_bl_len;
	uint erase_grp_size;	/* in 512-byte sectors */
	uint hc_wp_grp_size;	/* in 512-byte sectors */
	u64 capacity;
	u64 capacity_user;
	u64 capacity_boot;
	u64 capacity_rpmb;
	u64 capacity_gp[4];
	u64 enh_user_start;
	u64 enh_user_size;
//	block_dev_desc_t block_dev;
	char op_cond_pending;	/* 1 if we are waiting on an op_cond command */
	char init_in_progress;	/* 1 if we have done mmc_start_init() */
	char preinit;		/* start init as early as possible */
	int ddr_mode;
};


#endif /* _MMC_H_ */
