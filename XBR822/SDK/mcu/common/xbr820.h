#ifndef __XBR820_H__
#define __XBR820_H__

#include "csi_core.h"

typedef enum irq_number
{
    INT_SOFT                 = 3,
    INT_SYS_TIMER            = 7,
    INT_EXTERNAL            = 11,
    INT_000                 = 16,
    INT_001                 = 17,
    INT_002                 = 18,
    INT_003                 = 19,
    INT_004                 = 20,
    INT_005                 = 21,
    INT_006                 = 22,
    INT_007                 = 23,
}irq_number_e;


typedef struct
{
    __IO uint32_t TX_ENABLE                 : 1;
    __IO uint32_t TX_INT_CLEAR              : 1;
    __IO uint32_t RX_ENABLE                 : 1;
    __IO uint32_t RX_INT_CLEAR              : 1;
    __IO uint32_t FIFO_RD                   : 1;
    __IO uint32_t FIFO_CLR                  : 1;
    uint32_t                                : 26;
} str_usart_ctl_field_t;

typedef struct
{
    __IO uint32_t BAUD_RATE                 : 16;
    uint32_t                                : 16;
} str_usart_br_field_t;

typedef struct
{
    __IO uint32_t TX_DATA                   : 8;
    uint32_t                                : 24;
} str_usart_td_field_t;

typedef struct
{
    __IO uint32_t RX_DATA                   : 8;
    uint32_t                                : 24;
} str_usart_rd_field_t;

typedef struct
{
    __IO uint32_t TI                        : 1;
    __IO uint32_t TX_STATE                  : 3;
    __IO uint32_t RI                        : 1;
    __IO uint32_t RX_STATE                  : 3;
    __IO uint32_t RX_ERROR                  : 2;
    __IO uint32_t RDATA_CNT                 : 4;
    uint32_t                                : 18;
} str_usart_st_field_t;

typedef struct
{
    __IO uint32_t VALUE                      : 8;
    __IO uint32_t INOUT                      : 8;
    //__IO uint32_t INEN                       : 8;
    uint32_t                                 : 8;
    uint32_t                                 : 8;
} str_gpio_ctl_field_t;

typedef struct
{
    __IO uint32_t PX_0                       : 4;
    __IO uint32_t PX_1                       : 4;
    __IO uint32_t PX_2                       : 4;
    __IO uint32_t PX_3                       : 4;
    __IO uint32_t PX_4                       : 4;
    __IO uint32_t PX_5                       : 4;
    __IO uint32_t PX_6                       : 4;
    __IO uint32_t PX_7                       : 4;
} str_gpio_ps_field_t;

typedef struct
{
    __IO uint32_t ADC_DIV                    : 12;
    __IO uint32_t TRI_MODE                   : 1;
    __IO uint32_t TRI_SRC                    : 1;
    uint32_t                                 : 18;
} str_adc_ctl_field_t;

typedef struct
{
    __IO uint32_t ADC_DELAY                  : 12;
    uint32_t                                 : 20;
} str_adc_delay_field_t;

typedef struct
{
    __IO uint32_t ADC_BEGIN                  : 11;
    uint32_t                                 : 5;
    __IO uint32_t ADC_END                    : 11;
    uint32_t                                 : 5;
} str_adc_range_field_t;


typedef struct
{
    union
    {
        __IO uint32_t CTL;
        str_usart_ctl_field_t CTL_f;
    };
    union
    {
        __IO uint32_t BR;
        str_usart_br_field_t BR_f;
    };
    union
    {
        __IO uint32_t TD;
        str_usart_td_field_t TD_f;
    };
    union
    {
        __IO uint32_t RD;
        str_usart_rd_field_t RD_f;
    };
    union
    {
        __IO uint32_t ST;
        str_usart_st_field_t ST_f;
    };
} brx820_uart_regdef;

typedef struct
{
    union
    {
        __IO uint32_t CTL;
        str_gpio_ctl_field_t CTL_f;
    };
    union
    {
        __IO uint32_t PS;
        str_gpio_ps_field_t PS_f;
    };
} brx820_gpio_regdef;

typedef struct
{
    union
    {
        __IO uint32_t CTL;
        str_adc_ctl_field_t CTL_f;
    };
    union
    {
        __IO uint32_t DELAY;
        str_adc_delay_field_t DELAY_f;
    };
    union
    {
        __IO uint32_t RANGE;
        str_adc_range_field_t RANGE_f;
    };    
} brx820_adc_regdef;


#define BRX820_UART     ((brx820_uart_regdef *)(0x1f040000UL))
#define BRX820_GPIO_PA  ((brx820_gpio_regdef *)(0x1f000100UL))
#define BRX820_GPIO_PB  ((brx820_gpio_regdef *)(0x1f000120UL))
#define BRX820_DSP_ADC  ((brx820_adc_regdef *)(0x1f010000UL))

#define SYSTEM_CLOCK 40000000

#endif
