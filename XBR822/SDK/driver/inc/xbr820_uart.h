#ifndef __XBR_UART_H__
#define __XBR_UART_H__

#include "pho_common.h"

typedef struct str_uart_init
{
    uint32_t   BAND_RATE;

} str_uart_init_t;

em_result_t uart_init(brx820_uart_regdef *uartx, const str_uart_init_t *uart_init_cfg);
em_result_t uart_sent_byte(brx820_uart_regdef *uartx, uint8_t data);
em_result_t uart_rev_byte(brx820_uart_regdef *uartx, uint8_t *data);
uint8_t uart_get_fifo_cnt(brx820_uart_regdef *uartx);

#endif
