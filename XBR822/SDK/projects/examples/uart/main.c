#include "xbr820.h"
#include "xbr820_uart.h"
#include "xbr820_interrupts.h"

int main()
{
	str_uart_init_t uart1_cfg;
	uint8_t rev_byte0 = 0x00;
	
	uart1_cfg.BAND_RATE = 115200UL;
	
	uart_init(BRX820_UART, &uart1_cfg);
	
	while(1)
	{
		if (1)
		{
			uart_sent_byte(BRX820_UART, 0x55);
			uart_sent_byte(BRX820_UART, 0xAA);
		}
		
		while(uart_get_fifo_cnt(BRX820_UART))
		{
			uart_rev_byte(BRX820_UART, &rev_byte0);
			uart_sent_byte(BRX820_UART, rev_byte0);
		}
	}
	
    return 0;
}

