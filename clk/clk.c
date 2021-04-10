#include "io.h"
#include "crm_regs.h"
#include "imx-regs.h"
#include "my_printf.h"
#include "clk.h"

struct mxc_ccm_reg *imx_ccm = (struct mxc_ccm_reg *)CCM_BASE_ADDR;

enum pll_clocks {
	PLL_SYS,	/* System PLL */
	PLL_BUS,	/* System Bus PLL*/
	PLL_USBOTG,	/* OTG USB PLL */
	PLL_ENET,	/* ENET PLL */
	PLL_AUDIO,	/* AUDIO PLL */
	PLL_VIDEO,	/* AUDIO PLL */
};

static u32 decode_pll(enum pll_clocks pll, u32 infreq)
{
	u32 div;

	switch (pll) {
	case PLL_SYS:
		div = readl(&imx_ccm->analog_pll_sys);
		div &= BM_ANADIG_PLL_SYS_DIV_SELECT;

		return (infreq * div) >> 1;
	default:
		return 0;
	}
}

static u32 get_mcu_main_clk(void)
{
	u32 reg, freq;

	reg = readl(&imx_ccm->cacrr);
	reg &= MXC_CCM_CACRR_ARM_PODF_MASK;
	reg >>= MXC_CCM_CACRR_ARM_PODF_OFFSET;
	freq = decode_pll(PLL_SYS, MXC_HCLK);

	return freq / (reg + 1);
}

unsigned int mxc_get_clock(enum mxc_clock clk)
{
	switch (clk) {
	case MXC_ARM_CLK:
		return get_mcu_main_clk();
	default:
		printf("Unsupported MXC CLK: %d\n", clk);
		break;
	}
	return 0;
}
