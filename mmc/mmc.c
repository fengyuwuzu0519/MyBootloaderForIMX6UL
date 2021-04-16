#include "io.h"
#include "crm_regs.h"
#include "imx-regs.h"
#include "my_printf.h"
#include "clk.h"
#include "config.h"
#include "list.h"
#include "fsl_esdhc.h"
#include "iomux-v3.h"
#include "mx6ull_pins.h"
#include "common.h"
#include "fsl_esdhc.h"

int cur_dev_num = -1;
struct list_head mmc_devices;

#define USDHC_PAD_CTRL (PAD_CTL_PKE | PAD_CTL_PUE |     \
		PAD_CTL_PUS_100K_UP | PAD_CTL_SPEED_MED |       \
		PAD_CTL_DSE_40ohm   | PAD_CTL_SRE_FAST  | PAD_CTL_HYS)


iomux_v3_cfg_t usdhc1_pads[] = {
	MX6_PAD_SD1_CLK__USDHC1_CLK | MUX_PAD_CTRL(USDHC_PAD_CTRL),
	MX6_PAD_SD1_CMD__USDHC1_CMD | MUX_PAD_CTRL(USDHC_PAD_CTRL),
};

iomux_v3_cfg_t usdhc2_emmc_pads[] = {
	MX6_PAD_NAND_RE_B__USDHC2_CLK | MUX_PAD_CTRL(USDHC_PAD_CTRL),
	MX6_PAD_NAND_WE_B__USDHC2_CMD | MUX_PAD_CTRL(USDHC_PAD_CTRL),
};

struct fsl_esdhc_cfg usdhc_cfg[] = {
	{USDHC1_BASE_ADDR, 0, 4},
	{USDHC2_BASE_ADDR, 0, 8},
};

int board_mmc_init(void)
{
	int i;

	for (i = 0; i < CONFIG_SYS_FSL_USDHC_NUM; i++) {
		//设置GPIO功能选择
		switch (i) {
		case 0:
			imx_iomux_v3_setup_multiple_pads(usdhc1_pads, ARRAY_SIZE(usdhc1_pads));
			usdhc_cfg[0].sdhc_clk = mxc_get_clock(MXC_ESDHC_CLK);
		case 1:
			imx_iomux_v3_setup_multiple_pads(usdhc2_emmc_pads, ARRAY_SIZE(usdhc2_emmc_pads));
			usdhc_cfg[1].sdhc_clk = mxc_get_clock(MXC_ESDHC2_CLK);
		}
		fsl_esdhc_initialize(&usdhc_cfg[i]);
	}

	return 0;
}

int mmc_probe(void)
{
	board_mmc_init();
	return 0;
}

int mmc_initialize(void)
{
	INIT_LIST_HEAD(&mmc_devices);
	cur_dev_num = 0;

	mmc_probe();

	return 0;
}
