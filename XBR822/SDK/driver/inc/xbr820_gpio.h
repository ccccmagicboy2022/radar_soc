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

typedef enum 
{
	PA0_FUNC_GPIO = 0u,
	PA0_FUNC_IR_IN = 1u,
	PA0_FUNC_OSC32K = 9u,
	PA0_FUNC_SADC0 = 10u
}em_pin_pa0_func_t;

typedef enum 
{
	PA1_FUNC_GPIO = 0u,
	PA1_FUNC_PWM1 = 6u,
	PA1_FUNC_IO_VALUE_P = 8u,
	PA1_FUNC_XTAL40M = 9u,
	PA1_FUNC_SADC1 = 10u
}em_pin_pa1_func_t;

typedef enum 
{
	PA2_FUNC_GPIO = 0u,
	PA2_FUNC_PWM2 = 6u,
	PA2_FUNC_PLL_PRE = 9u,
	PA2_FUNC_SADC2 = 10u
}em_pin_pa2_func_t;

typedef enum 
{
	PA3_FUNC_GPIO = 0u,
	PA3_FUNC_PWM3 = 6u,
	PA3_FUNC_IO_VALUE_N = 8u,
	PA3_FUNC_PLL_FB = 9u,
	PA3_FUNC_SADC3 = 10u
}em_pin_pa3_func_t;

typedef enum 
{
	PA4_FUNC_GPIO = 0u,
	PA4_FUNC_MSCL = 3u,
	PA4_FUNC_PWM4 = 6u,
	PA4_FUNC_SADC4 = 10u
}em_pin_pa4_func_t;

typedef enum 
{
	PA5_FUNC_GPIO = 0u,
	PA5_FUNC_MSDA = 3u,
	PA5_FUNC_PWM5 = 6u,
	PA5_FUNC_LIGHT_TRIGGER = 9u,
	PA5_FUNC_SADC5 = 10u
}em_pin_pa5_func_t;

typedef enum 
{
	PA6_FUNC_GPIO = 0u,
	PA6_FUNC_UART_RX = 2u,
	PA6_FUNC_LIGHT_LATCH = 9u,
	PA6_FUNC_SADC6 = 10u
}em_pin_pa6_func_t;

typedef enum 
{
	PA7_FUNC_GPIO = 0u,
	PA7_FUNC_UART_TX = 2u,
	PA7_FUNC_LIGHT_FLAG = 9u,
	PA7_FUNC_SADC7 = 10u
}em_pin_pa7_func_t;

typedef enum 
{
	PB0_FUNC_GPIO = 0u,
	PB0_FUNC_SSCL = 3u,
	PB0_FUNC_PWM1 = 6u,
	PB0_FUNC_SADC8 = 10u
}em_pin_pb0_func_t;

typedef enum 
{
	PB1_FUNC_GPIO = 0u,
	PB1_FUNC_SSDA = 3u,
	PB1_FUNC_PWM2 = 6u,
	PB1_FUNC_SADC9 = 10u
}em_pin_pb1_func_t;

typedef enum 
{
	PB2_FUNC_GPIO = 0u,
	PB2_FUNC_PWM3 = 6u,
	PB2_FUNC_IO_VALUE_P = 8u,
	PB2_FUNC_SADC10 = 10u
}em_pin_pb2_func_t;

typedef enum 
{
	PB3_FUNC_GPIO = 0u,
	PB3_FUNC_PWM4 = 6u,
	PB3_FUNC_IO_VALUE_N = 8u,
	PB3_FUNC_SADC11 = 10u
}em_pin_pb3_func_t;

typedef enum 
{
	PB4_FUNC_GPIO = 0u,
	PB4_FUNC_PWM5 = 6u,
	PB4_FUNC_SADC_DONE = 10u
}em_pin_pb4_func_t;

typedef enum 
{
	PB5_FUNC_GPIO = 0u,
}em_pin_pb5_func_t;

typedef enum em_pin_mode
{
    GPIO_IN  = 0,
    GPIO_OUT = 1,
}em_gpio_inout_t;

typedef struct str_gpio_init
{
    em_gpio_inout_t        gpio_inout;
	em_functional_state_t  gpio_int_en;
} str_gpio_init_cfg_t;

em_result_t pin_set_func(brx820_gpio_regdef *px, em_pin_t pin_sel,
                            uint8_t func_sel);
em_result_t gpio_init(brx820_gpio_regdef *px, em_pin_t pin_sel,
                        const str_gpio_init_cfg_t *gpio_init_cfg);
em_flag_status_t gpio_get(brx820_gpio_regdef *px, em_pin_t pin_sel);
em_result_t gpio_set(brx820_gpio_regdef *px, em_pin_t pin_sel);
em_result_t gpio_reset(brx820_gpio_regdef *px, em_pin_t pin_sel);
em_result_t gpio_toggle(brx820_gpio_regdef *px, em_pin_t pin_sel);

#endif
