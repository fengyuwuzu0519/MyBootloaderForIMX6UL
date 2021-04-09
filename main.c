#include "led.h"
#include "uart.h"
#include "my_printf.h"

void delay(volatile unsigned int d)
{
	while(d--);
}


int  main()
{
	led_init();
	uart_init();

	while(1)
	{
		led_ctl(1);
		delay(1000000);
		led_ctl(0);
		delay(1000000);
		my_printf_test();
	}

	return 0;
}
