#ifndef __XBR820_H__
#define __XBR820_H__

#include "csi_core.h"

typedef enum irq_number
{
    UART_RX_IRQ             = 1,
    UART_TX_IRQ             = 2,
    TIMER1_IRQ              = 3,
    TIMER2_IRQ              = 4,
    TIMER3_IRQ              = 5,
    TIMER4_IRQ              = 6,
    ADC_DONE_IRQ            = 7,
    IR_IRQ                  = 9,
    WDG_IRQ                 = 10,
    GPIO_PA0_IRQ            = 11,
    GPIO_PA1_IRQ            = 12,
    GPIO_PA2_IRQ            = 13,
    GPIO_PA3_IRQ            = 14,
    LIGHT_SENSOR_IRQ        = 17,
    FREQ_DET_IRQ            = 18,
    I2C_MASTER              = 19,
    I2C_SLAVE               = 20,
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

typedef struct {
    __IO uint32_t WDG_RST_EN                                      :1;
    __IO uint32_t WDG_INT_EN                                      :1;
    uint32_t                                                      :30;
} str_wdg_en_filed_t;

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

/**
 * @brief WFG
 *
 */
typedef struct {
    union
    {
        __IO uint32_t WDG_CFG;
        str_wdg_en_filed_t WDG_CFG_f;
    };
    __IO uint32_t STC_WDG_CNT_REG;
} brx820_wdg_regdef;

typedef struct {
    union
    {
        __IO uint32_t TIMER_EN                                        :1;
        __IO uint32_t TIMER_STA                                       :1;
        uint32_t                                                      :30;
    };
    __IO uint32_t TIMER_INIT;
    __IO uint32_t TIMER_CNT;
} brx820_timer_regdef;

typedef struct {
    union
    {
        __IO uint32_t PWM_EN                                          :1;
        uint32_t                                                      :31;
    };
    union
    {
        __IO uint32_t PWM_CTRL                                        :24;
        uint32_t                                                      :8;
    };
    union
    {
        __IO uint32_t PWM_DUTY                                        :24;
        uint32_t                                                      :8;
    };
} brx820_pwm_regdef;


#define BRX820_UART     ((brx820_uart_regdef *)(0x1f040000UL))
#define BRX820_GPIO_PA  ((brx820_gpio_regdef *)(0x1f000100UL))
#define BRX820_GPIO_PB  ((brx820_gpio_regdef *)(0x1f000120UL))
#define BRX820_DSP_ADC  ((brx820_adc_regdef *)(0x1f010000UL))
#define BRX820_WDG      ((brx820_wdg_regdef *)(0x1f020010UL))
#define BRX820_TIMER1   ((brx820_timer_regdef *)(0x1f020020UL))
#define BRX820_TIMER2   ((brx820_timer_regdef *)(0x1f020040UL))
#define BRX820_TIMER3   ((brx820_timer_regdef *)(0x1f020060UL))
#define BRX820_TIMER4   ((brx820_timer_regdef *)(0x1f020080UL))
#define BRX820_PWM1     ((brx820_pwm_regdef *)(0x1f020100UL))
#define BRX820_PWM2     ((brx820_pwm_regdef *)(0x1f020120UL))
#define BRX820_PWM3     ((brx820_pwm_regdef *)(0x1f020140UL))
#define BRX820_PWM4     ((brx820_pwm_regdef *)(0x1f020160UL))
#define BRX820_PWM5     ((brx820_pwm_regdef *)(0x1f020180UL))

#define SYSTEM_CLOCK 40000000

#endif
