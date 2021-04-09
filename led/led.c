
#include "led.h"
//gpio3-4
static volatile unsigned int *CCM_CCGR2                              ;
static volatile unsigned int *IOMUXC_SW_MUX_CTL_PAD_LCD_RESET;
static volatile unsigned int *GPIO3_GDIR                             ;
static volatile unsigned int *GPIO3_DR                               ;

/**********************************************************************
 * 函数名称： led_init
 * 功能描述： 初始化LED引脚，就是把它设置为输出引脚
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2020/02/07	     V1.0	  韦东山	      创建
 ***********************************************************************/
void led_init(void)
{
	unsigned int val;

	CCM_CCGR2                               = (volatile unsigned int *)(0x20C406C);
	IOMUXC_SW_MUX_CTL_PAD_LCD_RESET			= (volatile unsigned int *)(0x20e0114);
	GPIO3_GDIR                              = (volatile unsigned int *)(0x020A4000 + 0x4);
	GPIO3_DR                                = (volatile unsigned int *)(0x020A4000);

	/* GPIO3_IO04 */
	/* a. 使能GPIO3
	 * set CCM to enable GPIO3
	 * bit[27:26] = 0b11
	 */
	*CCM_CCGR2 |= (3<<26);

	/* b. 设置GPIO3_IO04用于GPIO
	 * set IOMUXC_SW_MUX_CTL_PAD_LCD_RESET
	 *      to configure GPIO3_IO04 as GPIO
	 * bit[3:0] = 0b0101 alt5
	 */
	val = *IOMUXC_SW_MUX_CTL_PAD_LCD_RESET;
	val &= ~(0xf);
	val |= (5);
	*IOMUXC_SW_MUX_CTL_PAD_LCD_RESET = val;


	/* c. 设置GPIO3_IO04作为output引脚
	 * set GPIO3_GDIR to configure GPIO3_IO04 as output
	 * GPIO3_GDIR  0x020AC000 + 0x4
	 * bit[4] = 0b1
	 */
	*GPIO3_GDIR |= (1<<4);

}

/**********************************************************************
 * 函数名称： led_ctl
 * 功能描述： 设置LED状态
 * 输入参数：
 *     on : 1-LED点亮, 0-LED熄灭
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2020/02/07	     V1.0	  韦东山	      创建
 ***********************************************************************/
void led_ctl(int on)
{
	if (on) /* on: output 0*/
	{
		/* d. 设置GPIO3_DR输出低电平
		 * set GPIO3_DR to configure GPIO3_IO04 output 0
		 * bit[4] = 0b0
		 */
		*GPIO3_DR &= ~(1<<4);
	}
	else  /* off: output 1*/
	{
		/* e. 设置GPIO5_IO3输出高电平
		 * set GPIO3_DR to configure GPIO3_IO04 output 1
		 * bit[4] = 0b1
		 */
		*GPIO3_DR |= (1<<4);
	}
}
