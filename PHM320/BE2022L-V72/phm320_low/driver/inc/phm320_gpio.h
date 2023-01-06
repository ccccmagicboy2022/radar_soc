#ifndef __PHM320_GPIO_H___
#define __PHM320_GPIO_H___

#include "pho_common.h"

typedef enum em_pin
{
    P1_0 = 0,
    P1_1 = 1,
    P1_2 = 2,
    P1_3 = 3,
    P1_4 = 4,
    P1_5 = 5,
    P1_6 = 6,
	P1_7 = 7,
}em_pin_t;

typedef enum em_pin_func
{
    FUNC_GPIO       = 0u,
    FUNC_PWM        = 1u,
    FUNC_BBP        = 2u,
    FUNC_IR         = 3u,
}em_pin_func_t;

typedef enum em_pin_mode
{
    GPIO_IN  = 0,
    GPIO_OUT = 1,
}em_gpio_mode_t;

typedef enum em_top_trg_mode
{
    RISING_EDGE   = 0u,
    FALLING_EDGE  = 1u,
    ALL_EDGE      = 2u,
    HIGH_LEVEL    = 4u,
    LOW_LEVEL     = 5u,
} em_top_trg_mode_t;

typedef struct str_gpio_init
{
    em_gpio_mode_t        gpio_mode;
    em_functional_state_t gpio_int_en;
    em_top_trg_mode_t     gpio_trg_mode;
} str_gpio_init_cfg_t;

em_result_t pin_set_func(em_pin_t pin_sel, em_pin_func_t func_sel);
em_result_t gpio_init(em_pin_t pin_sel, const str_gpio_init_cfg_t *gpio_init_cfg);
em_flag_status_t gpio_get_flag(em_pin_t pin_sel);
//em_result_t gpio_clear_flag(em_pin_t pin_sel);
em_flag_status_t gpio_get(em_pin_t pin_sel);
//em_result_t gpio_set(em_pin_t pin_sel);
//em_result_t gpio_reset(em_pin_t pin_sel);
//em_result_t gpio_toggle(em_pin_t pin_sel);
em_result_t top_clear_flag(void);

#endif  // __PHM320_GPIO_H___
