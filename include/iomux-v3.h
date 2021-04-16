/*
 * Based on Linux i.MX iomux-v3.h file:
 * Copyright (C) 2009 by Jan Weitzel Phytec Messtechnik GmbH,
 *			<armlinux@phytec.de>
 *
 * Copyright (C) 2011, 2016 Freescale Semiconductor, Inc.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __MACH_IOMUX_V3_H__
#define __MACH_IOMUX_V3_H__

typedef u64 iomux_v3_cfg_t;

#define MUX_CTRL_OFS_SHIFT	0
#define MUX_CTRL_OFS_MASK	((iomux_v3_cfg_t)0xfff << MUX_CTRL_OFS_SHIFT)
#define MUX_PAD_CTRL_OFS_SHIFT	12
#define MUX_PAD_CTRL_OFS_MASK	((iomux_v3_cfg_t)0xfff << \
	MUX_PAD_CTRL_OFS_SHIFT)
#define MUX_SEL_INPUT_OFS_SHIFT	24
#define MUX_SEL_INPUT_OFS_MASK	((iomux_v3_cfg_t)0xfff << \
	MUX_SEL_INPUT_OFS_SHIFT)

#define MUX_MODE_SHIFT		36
#define MUX_MODE_MASK		((iomux_v3_cfg_t)0x3f << MUX_MODE_SHIFT)
#define MUX_PAD_CTRL_SHIFT	42
#define MUX_PAD_CTRL_MASK	((iomux_v3_cfg_t)0x3ffff << MUX_PAD_CTRL_SHIFT)
#define MUX_SEL_INPUT_SHIFT	60
#define MUX_SEL_INPUT_MASK	((iomux_v3_cfg_t)0xf << MUX_SEL_INPUT_SHIFT)

#define MUX_MODE_SION		((iomux_v3_cfg_t)IOMUX_CONFIG_SION << \
	MUX_MODE_SHIFT)
#define MUX_PAD_CTRL(x)		((iomux_v3_cfg_t)(x) << MUX_PAD_CTRL_SHIFT)

#define IOMUX_PAD(pad_ctrl_ofs, mux_ctrl_ofs, mux_mode, sel_input_ofs,	\
		sel_input, pad_ctrl)					\
	(((iomux_v3_cfg_t)(mux_ctrl_ofs) << MUX_CTRL_OFS_SHIFT)     |	\
	((iomux_v3_cfg_t)(mux_mode)      << MUX_MODE_SHIFT)         |	\
	((iomux_v3_cfg_t)(pad_ctrl_ofs)  << MUX_PAD_CTRL_OFS_SHIFT) |	\
	((iomux_v3_cfg_t)(pad_ctrl)      << MUX_PAD_CTRL_SHIFT)     |	\
	((iomux_v3_cfg_t)(sel_input_ofs) << MUX_SEL_INPUT_OFS_SHIFT)|	\
	((iomux_v3_cfg_t)(sel_input)     << MUX_SEL_INPUT_SHIFT))

#define NEW_PAD_CTRL(cfg, pad)	(((cfg) & ~MUX_PAD_CTRL_MASK) | \
					MUX_PAD_CTRL(pad))

#define __NA_			0x000
#define NO_MUX_I		0
#define NO_PAD_I		0

#define NO_PAD_CTRL		(1 << 17)

#define IOMUX_CONFIG_LPSR       0x20
#define MUX_MODE_LPSR           ((iomux_v3_cfg_t)IOMUX_CONFIG_LPSR << \
				MUX_MODE_SHIFT)

#define PAD_CTL_HYS		(1 << 16)

#define PAD_CTL_PUS_100K_DOWN	(0 << 14 | PAD_CTL_PUE)
#define PAD_CTL_PUS_47K_UP	(1 << 14 | PAD_CTL_PUE)
#define PAD_CTL_PUS_100K_UP	(2 << 14 | PAD_CTL_PUE)
#define PAD_CTL_PUS_22K_UP	(3 << 14 | PAD_CTL_PUE)
#define PAD_CTL_PUE		(1 << 13 | PAD_CTL_PKE)
#define PAD_CTL_PKE		(1 << 12)

#define PAD_CTL_ODE		(1 << 11)

#define PAD_CTL_SPEED_LOW	(0 << 6)
#define PAD_CTL_SPEED_MED	(2 << 6)
#define PAD_CTL_SPEED_HIGH	(3 << 6)

#define PAD_CTL_DSE_DISABLE	(0 << 3)
#define PAD_CTL_DSE_240ohm	(1 << 3)
#define PAD_CTL_DSE_120ohm	(2 << 3)
#define PAD_CTL_DSE_80ohm	(3 << 3)
#define PAD_CTL_DSE_60ohm	(4 << 3)
#define PAD_CTL_DSE_48ohm	(5 << 3)
#define PAD_CTL_DSE_40ohm	(6 << 3)
#define PAD_CTL_DSE_34ohm	(7 << 3)


#define PAD_CTL_SRE_SLOW	(0 << 0)
#define PAD_CTL_SRE_FAST	(1 << 0)

#define IOMUX_CONFIG_SION	0x10

#define GPIO_PIN_MASK		0x1f
#define GPIO_PORT_SHIFT		5
#define GPIO_PORT_MASK		(0x7 << GPIO_PORT_SHIFT)
#define GPIO_PORTA		(0 << GPIO_PORT_SHIFT)
#define GPIO_PORTB		(1 << GPIO_PORT_SHIFT)
#define GPIO_PORTC		(2 << GPIO_PORT_SHIFT)
#define GPIO_PORTD		(3 << GPIO_PORT_SHIFT)
#define GPIO_PORTE		(4 << GPIO_PORT_SHIFT)
#define GPIO_PORTF		(5 << GPIO_PORT_SHIFT)

void imx_iomux_v3_setup_pad(iomux_v3_cfg_t pad);
void imx_iomux_v3_setup_multiple_pads(iomux_v3_cfg_t const *pad_list,
				     unsigned count);

#endif	/* __MACH_IOMUX_V3_H__*/
