#include "phm320_gpio.h"

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

/*
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
*/
    default:
        //while (1) {}
        break;
    }
    return Ok;
}

em_result_t gpio_init(em_pin_t pin_sel, const str_gpio_init_cfg_t *gpio_init_cfg)
{
    PHM320_TOP->GPIO_OUT_EN = (PHM320_TOP->GPIO_OUT_EN & (~(1 << pin_sel))) \
                                | ((gpio_init_cfg->gpio_mode ^ 1) << pin_sel);
    if (pin_sel < 4) {
        PHM320_TOP->TOP_INT_MASK = (PHM320_TOP->TOP_INT_MASK & (~(1 << pin_sel))) \
                                    | ((gpio_init_cfg->gpio_int_en ^ 1) << pin_sel);
        PHM320_TOP->TOP_INT_MODE = (PHM320_TOP->TOP_INT_MODE & (~(0b111 << (3 * pin_sel)))) \
                                    | (gpio_init_cfg->gpio_trg_mode << (3 * pin_sel));
    }
    return Ok;
}
/*
em_flag_status_t gpio_get(em_pin_t pin_sel)
{
    return (PHM320_TOP->GPIO_VAL >> pin_sel) & 1;
}


em_flag_status_t gpio_get_flag(em_pin_t pin_sel)
{
    return (PHM320_TOP->TOP_INT_FLAG >> pin_sel) & 1;
}


em_result_t gpio_clear_flag(em_pin_t pin_sel)
{
    if (pin_sel < 4) {
        PHM320_TOP->TOP_INT_CLEAR = 1u << pin_sel;
    }
    return Ok;
}


em_result_t gpio_set(em_pin_t pin_sel)
{
    PHM320_TOP->GPIO_VAL |= (1ul << pin_sel);
    return Ok;
}

em_result_t gpio_reset(em_pin_t pin_sel)
{
    PHM320_TOP->GPIO_VAL &= (~(1ul << pin_sel));
    return Ok;
}

em_result_t gpio_toggle(em_pin_t pin_sel)
{
    PHM320_TOP->GPIO_VAL ^= (1ul << pin_sel);
    return Ok;
}
*/
em_result_t top_clear_flag(void)
{
    PHM320_TOP->TOP_INT_CLEAR_BITS.OUT = 1;
    return Ok;
}
