#include "uart.h"
#include "io.h"
#include "iomux-v3.h"
#include "mx6ull_pins.h"
#include "common.h"

#define UART_PAD_CTRL  (PAD_CTL_PKE | PAD_CTL_PUE |		\
	PAD_CTL_PUS_100K_UP | PAD_CTL_SPEED_MED |		\
	PAD_CTL_DSE_40ohm   | PAD_CTL_SRE_FAST  | PAD_CTL_HYS)

#if 0
static volatile unsigned int *IOMUXC_SW_MUX_CTL_PAD_ENET2_RX_EN ;
static volatile unsigned int *IOMUXC_SW_MUX_CTL_PAD_ENET2_TX_DATA0;
static volatile unsigned int *IOMUXC_UART7_RX_DATA_SELECT_INPUT;
#else
static iomux_v3_cfg_t const uart7_pads[] = {
	MX6_PAD_ENET2_RX_EN__UART7_DCE_TX | MUX_PAD_CTRL(UART_PAD_CTRL),
	MX6_PAD_ENET2_TX_DATA0__UART7_DCE_RX | MUX_PAD_CTRL(UART_PAD_CTRL),
};
static iomux_v3_cfg_t const uart1_pads[] = {
	MX6_PAD_UART1_TX_DATA__UART1_DCE_TX | MUX_PAD_CTRL(UART_PAD_CTRL),
	MX6_PAD_UART1_RX_DATA__UART1_DCE_RX | MUX_PAD_CTRL(UART_PAD_CTRL),
};
#endif

/**********************************************************************
 * 函数名称： Uart_Init
 * 功能描述： 初始化UART，就是规定传输格式，设置波特率为115200，配置UART占用的GPIO管脚
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2020/02/16	     V1.0	  zh(angenao)	      创建
 ***********************************************************************/

void uart_init(void)
{
#if 0
	IOMUXC_SW_MUX_CTL_PAD_ENET2_RX_EN		= (volatile unsigned int *)(0x20E00EC);
	IOMUXC_SW_MUX_CTL_PAD_ENET2_TX_DATA0	= (volatile unsigned int *)(0x20E00F0);
	IOMUXC_UART7_RX_DATA_SELECT_INPUT		= (volatile unsigned int *)(0x20E0654);

	*IOMUXC_UART7_RX_DATA_SELECT_INPUT = 0;
	*IOMUXC_SW_MUX_CTL_PAD_ENET2_TX_DATA0 = 1;
	*IOMUXC_SW_MUX_CTL_PAD_ENET2_RX_EN = 1;
#else
	imx_iomux_v3_setup_multiple_pads(uart1_pads, ARRAY_SIZE(uart7_pads));
#endif
	UART1->UCR1 |= (1 << 0) ;		/*关闭当前串口*/

	/*
	 *  设置UART传输格式：
	 *  UART1中的UCR2寄存器关键bit如下
	 *  [14]:	1：忽略RTS引脚
	 *  [8] :	0: 关闭奇偶校验 默认为0，无需设置
	 *  [6] :	0: 停止位1位	    默认为0，无需设置
	 *  [5] :	1: 数据长度8位
	 *  [2] :	1: 发送数据使能
	 *  [1] :	1: 接收数据使能
	 */

	UART1->UCR2 |= (1<<14) |(1<<5) |(1<<2)|(1<<1);

	/*
	 *  UART1中的UCR3寄存器关键bit如下
	 *  [2]:  1:根据官方文档表示，IM6ULL的UART用了这个MUXED模型，提示要设置
	 */

	UART1->UCR3 |= (1<<2);

	/*
	 * 设置波特率
	 * 根据芯片手册得知波特率计算公式:
	 * Baud Rate = Ref Freq / (16 * (UBMR + 1)/(UBIR+1))
	 * 当我们需要设置 115200的波特率
	 * UART7_UFCR [9:7]=101，表示不分频，得到当前UART参考频率Ref Freq ：80M ，
	 * 带入公式：115200 = 80000000 /(16*(UBMR + 1)/(UBIR+1))
	 *
	 * 选取一组满足上式的参数：UBMR、UBIR即可
	 *
	 * UART7_UBIR    = 71
	 * UART7_UBMR = 3124
	 */

    UART1->UFCR = 5 << 7;       /* Uart的时钟clk：80MHz */
    UART1->UBIR = 71;
    UART1->UBMR = 3124;

	UART1->UCR1 |= (1 << 0);		/*使能当前串口*/
}
/**********************************************************************
* 函数名称： PutChar
* 功能描述： 从串口输出单个字符到上位机
* 输入参数：单个字符
* 输出参数： 无
* 返 回 值： 无
* 修改日期		  版本号 	修改人		 修改内容
* -----------------------------------------------
* 2020/02/16		V1.0	 zh(angenao)		 创建
***********************************************************************/

void PutChar(int c)
{
	while (!((UART1->USR2) & (1<<3))); /*等待上个字节发送完毕*/
	UART1->UTXD = (unsigned char)c;
}
/**********************************************************************
 * 函数名称： GetChar
 * 功能描述： 通过串口，从上位机获取单个字符
 * 输入参数： 无
 * 输出参数： 无
 * 返 回 值： 返回接收到的字符
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2020/02/16	     V1.0	  zh(angenao)	      创建
 ***********************************************************************/

unsigned char GetChar(void)
{
	while (!(UART1->USR2 & (1<<0)));  /*等待接收数据*/
	return (unsigned char)UART1->URXD;
}
/**********************************************************************
 * 函数名称： PutStr
 * 功能描述： 输出字符串，就是连续发送单个字符
 * 输入参数： 字符串
 * 输出参数： 无
 * 返 回 值： 无
 * 修改日期        版本号     修改人	      修改内容
 * -----------------------------------------------
 * 2020/02/16	     V1.0	  zh(angenao)	      创建
 ***********************************************************************/

void PutStr(const char *s)
{
	while (*s)
	{
		PutChar(*s);
		s++;
	}
}
int raise(int signum)/* raise函数，防止编译报错 */
{
    return 0;
}
