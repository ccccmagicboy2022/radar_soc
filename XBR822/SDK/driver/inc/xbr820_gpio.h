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
    FUNC_UART_TX    = 2u,
    FUNC_UART_RX    = 3u,
    FUNC_PWM        = 6u,
    FUNC_BB_OUT     = 8u,
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