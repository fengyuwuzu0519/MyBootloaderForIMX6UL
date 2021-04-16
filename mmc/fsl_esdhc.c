#include "fsl_esdhc.h"
#include "io.h"

struct fsl_esdhc {
	uint    dsaddr;		/* SDMA system address register */
	uint    blkattr;	/* Block attributes register */
	uint    cmdarg;		/* Command argument register */
	uint    xfertyp;	/* Transfer type register */
	uint    cmdrsp0;	/* Command response 0 register */
	uint    cmdrsp1;	/* Command response 1 register */
	uint    cmdrsp2;	/* Command response 2 register */
	uint    cmdrsp3;	/* Command response 3 register */
	uint    datport;	/* Buffer data port register */
	uint    prsstat;	/* Present state register */
	uint    proctl;		/* Protocol control register */
	uint    sysctl;		/* System Control Register */
	uint    irqstat;	/* Interrupt status register */
	uint    irqstaten;	/* Interrupt status enable register */
	uint    irqsigen;	/* Interrupt signal enable register */
	uint    autoc12err;	/* Auto CMD error status register */
	uint    hostcapblt;	/* Host controller capabilities register */
	uint    wml;		/* Watermark level register */
	uint    mixctrl;	/* For USDHC */
	char    reserved1[4];	/* reserved */
	uint    fevt;		/* Force event register */
	uint    admaes;		/* ADMA error status register */
	uint    adsaddr;	/* ADMA system address register */
	char    reserved2[4];
	uint    dllctrl;
	uint    dllstat;
	uint    clktunectrlstatus;
	char    reserved3[84];
	uint    vendorspec;
	uint    mmcboot;
	uint    vendorspec2;
	char	reserved4[48];
	uint    hostver;	/* Host controller version register */
};

int fsl_esdhc_initialize(struct fsl_esdhc_cfg *cfg)
{
	struct fsl_esdhc *regs;
	struct mmc *mmc;
	u32 caps, voltage_caps;

	if (!cfg)
		return -1;
	regs = (struct fsl_esdhc *)cfg->esdhc_base;

	return 0;
}
