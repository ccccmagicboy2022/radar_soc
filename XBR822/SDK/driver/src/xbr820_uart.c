#include "xbr820_uart.h"

em_result_t uart_init(brx820_uart_regdef *uartx, const str_uart_init_t *uart_init_cfg)
{
    uartx->BR_f.BAUD_RATE = 16000000 / uart_init_cfg->BAND_RATE;

    uartx->CTL_f.TX_INT_CLEAR = 1;
    uartx->CTL_f.TX_ENABLE = 1;
    uartx->CTL_f.RX_ENABLE = 1;

    return OK;
}
em_result_t uart_send_data_polling(brx820_uart_regdef *uartx, uint8_t data)
{
    while (!uartx->ST_f.TX_STATE)
    uartx->TD_f.TX_DATA = data;
    while (!uartx->ST_f.TI) {}
    return OK;
}
em_result_t uart_rec_data(brx820_uart_regdef *uartx, uint8_t *data)
{
    if (uartx->ST_f.RDATA_CNT != 0) {
        uartx->CTL_f.FIFO_RD = 1;
        *data = uartx->RD_f.RX_DATA;
        return OK;
    } else {
        return ERROR;
    }
}