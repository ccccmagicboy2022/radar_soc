/**
 * @file phm320_adc.c
 * @author Phosense Software Team
 * @brief gpio driver C source file
 * @version 1.0.0.0
 * @date 2022-03-21
 * 
* @copyright Copyright (c) 2022, Phosense-tech, All rights reserved.
 * 
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "phm320_gpio.h"

/** @{*/

/**
 * @brief Port function select
 * 
 * @details only p1-0 to p1-4 can be set gpio, pwm or bbp function
 *          only p1_5 can be set ir function
 * 
 * @param [in] pin_sel GPIO pin index, This parameter can be
 *                                     any composed value of @ref em_pin_t
 * @param [in] func_sel GPIO function, This parameter can be
 *                                     any composed value of @ref em_pin_func_t
 * @return em_result_t 
 * - OK no error occurred.
 * - ERRORINVALIDPARAMETER parameter error.
 */
em_result_t pin_set_func(em_pin_t pin_sel, em_pin_func_t func_sel)
{
    switch (func_sel) {
    case FUNC_GPIO:
        if (pin_sel < 5) {
            PHM320_TOP->TOP_CTLA &= (~(1ul << (pin_sel + 16)));
        } else {
            while (1) {}
        }
        break;

    case FUNC_PWM:
        if (pin_sel < 5) {
            PHM320_TOP->TOP_CTLA |= (1ul << (pin_sel + 16));
            PHM320_TOP->TOP_CTLB &= (~(0x11ul << (pin_sel + 4)));
        } else {
            while (1) {}
        }
        break;

    case FUNC_BBP:
        if (pin_sel < 5) {
            PHM320_TOP->TOP_CTLA |= (1ul << (pin_sel + 16));
            PHM320_TOP->TOP_CTLB &= (~(0x1ul << (pin_sel + 4)));
            PHM320_TOP->TOP_CTLB |= (0x10ul << (pin_sel + 4));
        } else {
            while (1) {}
        }
        break;

    case FUNC_IR:
        if (pin_sel == 5) {
            PHM320_TOP->TOP_CTLA_BITS.MUX6 = 1;
        } else {
            while (1) {}
        }
        break;

    default:
        while (1) {}
        break;
    }
    return Ok;
}

/**
 * @brief Port init
 * 
 * @param [in] pin_sel GPIO pin index, This parameter can be
 *                                     any composed value of @ref em_pin_t
 * @param [in] gpio_init_cfg pointer to GPIO initialization structure.
 *                           see @ref str_gpio_init_cfg_t for details.
 * @return em_result_t
 * - OK no error occurred. 
 */
em_result_t gpio_init(em_pin_t pin_sel, const str_gpio_init_cfg_t *gpio_init_cfg)
{
    PHM320_TOP->GPIO_OUT_EN = (PHM320_TOP->TOP_INT_MODE & (~(1 << pin_sel))) \
                                | ((gpio_init_cfg->gpio_mode ^ 1) << pin_sel);
    if (pin_sel < 4) {
        PHM320_TOP->TOP_INT_MASK = (PHM320_TOP->TOP_INT_MASK & (~(1 << pin_sel))) \
                                    | ((gpio_init_cfg->gpio_int_en ^ 1) << pin_sel);
        PHM320_TOP->TOP_INT_MODE = (PHM320_TOP->TOP_INT_MODE & (~(0b111 << (3 * pin_sel)))) \
                                    | (gpio_init_cfg->gpio_trg_mode << (3 * pin_sel));
    }
    return Ok;
}

/**
 * @brief get gpio input value
 * 
 * @param [in] pin_sel GPIO pin index, This parameter can be
 *                                     any composed value of @ref em_pin_t
 * @return em_flag_status_t 
 * - SET input value = 1.
 * - RESET input value = 0.
 */
em_flag_status_t gpio_get(em_pin_t pin_sel)
{
    return (PHM320_TOP->GPIO_VAL >> pin_sel) & 1;
}

/**
 * @brief get gpio interrupt flag
 * 
 * @param [in] pin_sel GPIO pin index, This parameter can be
 *                                     any composed value of @ref em_pin_t
 * @return em_flag_status_t 
 * - SET interrupt flag = 1.
 * - RESET interrupt flag =0.
 */
em_flag_status_t gpio_get_flag(em_pin_t pin_sel)
{
    return (PHM320_TOP->TOP_INT_FLAG >> pin_sel) & 1;
}

/**
 * @brief clear gpio input interrupt
 * 
 * @param [in] pin_sel GPIO pin index, This parameter can be
 *                                     any composed value of @ref em_pin_t
 * @return em_result_t 
 * - OK no error occurred.
 */
em_result_t gpio_clear_flag(em_pin_t pin_sel)
{
    if (pin_sel < 4) {
        PHM320_TOP->TOP_INT_CLEAR = 1u << pin_sel;
    }
    return Ok;
}

/**
 * @brief set gpio output value to 1
 * 
 * @param [in] pin_sel GPIO pin index, This parameter can be
 *                                     any composed value of @ref em_pin_t
 * @return em_result_t
 * - OK no error occurred.
 */
em_result_t gpio_set(em_pin_t pin_sel)
{
    PHM320_TOP->GPIO_VAL |= (1ul << pin_sel);
    return Ok;
}

/**
 * @brief set gpio output value to 0
 * 
 * @param [in] pin_sel GPIO pin index, This parameter can be
 *                                     any composed value of @ref em_pin_t
 * @return em_result_t
 * - OK no error occurred.
 */
em_result_t gpio_reset(em_pin_t pin_sel)
{
    PHM320_TOP->GPIO_VAL &= (~(1ul << pin_sel));
    return Ok;
}

/**
 * @brief toggle gpio output value
 * 
 * @param pin_sel [in] GPIO pin index, This parameter can be
 *                                     any composed value of @ref em_pin_t
 * @return em_result_t
 * - OK no error occurred.
 */
em_result_t gpio_toggle(em_pin_t pin_sel)
{
    PHM320_TOP->GPIO_VAL ^= (1ul << pin_sel);
    return Ok;
}

/**
 * @brief clear top module interrupt flag
 * 
 * @return em_result_t
 * - OK no error occurred.
 */
em_result_t top_clear_flag(void)
{
    PHM320_TOP->TOP_INT_CLEAR_BITS.OUT = 1;
    return Ok;
}

/**  @} gpio_group*/
