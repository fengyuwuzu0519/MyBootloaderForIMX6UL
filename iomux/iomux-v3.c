#include "io.h"
#include "iomux-v3.h"
#include "imx-regs.h"

static void *base = (void *)IOMUXC_BASE_ADDR;


void imx_iomux_v3_setup_pad(iomux_v3_cfg_t pad)
{
	u32 mux_ctrl_ofs = (pad & MUX_CTRL_OFS_MASK) >> MUX_CTRL_OFS_SHIFT;
	u32 mux_mode = (pad & MUX_MODE_MASK) >> MUX_MODE_SHIFT;
	u32 sel_input_ofs = (pad & MUX_SEL_INPUT_OFS_MASK) >> MUX_SEL_INPUT_OFS_SHIFT;
	u32 sel_input = (pad & MUX_SEL_INPUT_MASK) >> MUX_SEL_INPUT_SHIFT;
	u32 pad_ctrl_ofs = (pad & MUX_PAD_CTRL_OFS_MASK) >> MUX_PAD_CTRL_OFS_SHIFT;
	u32 pad_ctrl = (pad & MUX_PAD_CTRL_MASK) >> MUX_PAD_CTRL_SHIFT;

	u32 lpsr = (pad & MUX_MODE_LPSR) >> MUX_MODE_SHIFT;
	if (lpsr == IOMUX_CONFIG_LPSR) {
		base = (void *)IOMUXC_SNVS_BASE_ADDR;
		mux_mode &= ~IOMUX_CONFIG_LPSR;
	}

	writel(mux_mode, base + mux_ctrl_ofs);

	if (sel_input_ofs)
		writel(sel_input, base + sel_input_ofs);

	if (!(pad_ctrl & NO_PAD_CTRL) && pad_ctrl_ofs)
		writel(pad_ctrl, base + pad_ctrl_ofs);
	if (lpsr == IOMUX_CONFIG_LPSR)
		base = (void *)IOMUXC_BASE_ADDR;
}

void imx_iomux_v3_setup_multiple_pads(iomux_v3_cfg_t const *pad_list, unsigned count)
{
	iomux_v3_cfg_t const *p = pad_list;
	int stride;
	int i;

	stride = 1;

	for (i = 0; i < count; i++) {
		imx_iomux_v3_setup_pad(*p);
		p += stride;
	}
}
