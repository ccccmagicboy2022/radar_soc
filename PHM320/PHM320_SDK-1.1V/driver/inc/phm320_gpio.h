/**
 * @file phm320_gpio.h
 * @author Phosense Software Team
 * @brief gpio driver C head file
 * @version 1.0.0.0
 * @date 2022-03-21
 * 
* @copyright Copyright (c) 2022, Phosense-tech, All rights reserved.
 * 
 */

#ifndef __PHM320_GPIO_H___
#define __PHM320_GPIO_H___

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "pho_common.h"


/**
 * @defgroup gpio_group General Purpose Input/Output(GPIO)
 * @{
 */

/**
 * @brief GPIO Pin Index enumeration
 */
typedef enum em_pin
{
    P1_0 = 0,
    P1_1 = 1,
    P1_2 = 2,
    P1_3 = 3,
    P1_4 = 4,
    P1_5 = 5,
    P1_6 = 6,
}em_pin_t;

/**
 * @brief GPIO Function enumeration
 * 
 */
typedef enum em_pin_func
{
    FUNC_GPIO       = 0,
    FUNC_PWM        = 1,
    FUNC_BBP        = 2,
    FUNC_IR         = 3,
}em_pin_func_t;

/**
 * @brief GPIO Configuration Mode enumeration
 * 
 */
typedef enum em_pin_mode
{
    GPIO_IN  = 0,
    GPIO_OUT = 1,
}em_gpio_mode_t;

/**
 * @brief TOP module interrupt controller trig mode enumeration
 * 
 */
typedef enum em_top_trg_mode
{
    RISING_EDGE   = 0,
    FALLING_EDGE  = 1,
    ALL_EDGE      = 2,
    HIGH_LEVEL    = 4,
    LOW_LEVEL     = 5,
} em_top_trg_mode_t;

/**
 * @brief GPIO init structure definition
 * 
 */
typedef struct str_gpio_init
{
    em_gpio_mode_t        gpio_mode;
    em_functional_state_t gpio_int_en;
    em_top_trg_mode_t     gpio_trg_mode;
} str_gpio_init_cfg_t;

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
em_result_t pin_set_func(em_pin_t pin_sel, em_pin_func_t func_sel);
em_result_t gpio_init(em_pin_t pin_sel, const str_gpio_init_cfg_t *gpio_init_cfg);
em_flag_status_t gpio_get_flag(em_pin_t pin_sel);
em_result_t gpio_clear_flag(em_pin_t pin_sel);
em_flag_status_t gpio_get(em_pin_t pin_sel);
em_result_t gpio_set(em_pin_t pin_sel);
em_result_t gpio_reset(em_pin_t pin_sel);
em_result_t gpio_toggle(em_pin_t pin_sel);
em_result_t top_clear_flag(void);

/**  @} gpio_group*/

#endif  // __PHM320_GPIO_H___
