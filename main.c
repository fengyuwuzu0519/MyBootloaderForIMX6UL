#include "led.h"
#include "uart.h"
#include "my_printf.h"
#include "clk.h"
#include "io.h"

void delay(volatile unsigned int d)
{
	while(d--);
}

int  main()
{
	u32 cnt=0;
	led_init();
	uart_init();

	while(1)
	{
		cnt++;
		led_ctl(1);
		delay(1000000);
		led_ctl(0);
		delay(1000000);
		printf("cnt=%d clk=%d\r\n", cnt, mxc_get_clock(MXC_ARM_CLK));
	}

	return 0;
}
