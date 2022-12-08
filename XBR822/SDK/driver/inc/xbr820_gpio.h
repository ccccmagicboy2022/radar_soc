#ifndef __XBR820_GPIO_H___
#define __XBR820_GPIO_H___

#include "pho_common.h"

typedef enum em_pin
{
    PX_0 = 0,
    PX_1 = 1,
    PX_2 = 2,
    PX_3 = 3,
    PX_4 = 4,
    PX_5 = 5,
    PX_6 = 6,
    PX_7 = 7,
}em_pin_t;

typedef enum em_pin_func
{
    FUNC_GPIO       = 0u,
    FUNC_IR_IN      = 1u,
    FUNC_OSC32K     = 2u,
    FUNC_SADC0      = 3u,
    FUNC_PWM1       = 4u,
    FUNC_IO_VALUE_P = 5u,
    FUNC_XTAL40M    = 6u,
    FUNC_SADC1      = 7u,
    FUNC_PWM2       = 8u,
    FUNC_PLL_PRE    = 9u,
    FUNC_SADC2      = 10u,
    FUNC_PWM3       = 11u,
    FUNC_IO_VALUE_N = 12u,
    FUNC_PLL_FB     = 13u,
    FUNC_SADC3      = 14u,
    FUNC_MSCL       = 15u,
    FUNC_PWM4       = 16u,
    FUNC_SADC4      = 17u,
    FUNC_MSDA       = 18u,
    FUNC_PWM5       = 19u,
    FUNC_LIGHT_TRIGGER = 20u,
    FUNC_SADC5      = 21u,
    FUNC_UART_RX    = 22u,
    FUNC_LIGHT_LATCH= 23u,
    FUNC_SADC6      = 24u,
    FUNC_UART_TX    = 25u,
    FUNC_LIGHT_FLAG = 26u,
    FUNC_SADC7      = 27u,
    FUNC_SSCL       = 28u,
    FUNC_SADC8      = 29u,
    FUNC_SSDA       = 30u,
    FUNC_SADC9      = 31u,
    FUNC_SADC10     = 32u,
    FUNC_SADC11     = 33u,
    FUNC_SADC_DONE  = 34u,
}em_pin_func_t;

typedef enum em_pin_mode
{
    GPIO_IN  = 0,
    GPIO_OUT = 1,
}em_gpio_inout_t;

typedef struct str_gpio_init
{
    em_gpio_inout_t        gpio_inout;
} str_gpio_init_cfg_t;

em_result_t pin_set_func(brx820_gpio_regdef *px, em_pin_t pin_sel,
                            em_pin_func_t func_sel);
em_result_t gpio_init(brx820_gpio_regdef *px, em_pin_t pin_sel,
                        const str_gpio_init_cfg_t *gpio_init_cfg);
em_flag_status_t gpio_get(brx820_gpio_regdef *px, em_pin_t pin_sel);
em_result_t gpio_set(brx820_gpio_regdef *px, em_pin_t pin_sel);
em_result_t gpio_reset(brx820_gpio_regdef *px, em_pin_t pin_sel);
em_result_t gpio_toggle(brx820_gpio_regdef *px, em_pin_t pin_sel);

#endif