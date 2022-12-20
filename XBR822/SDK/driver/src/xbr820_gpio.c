#include "xbr820_gpio.h"

em_result_t pin_set_func(brx820_gpio_regdef *px, em_pin_t pin_sel,
                            uint8_t func_sel)
{
    px->PS &= (~(0b1111 << (pin_sel * 4)));
    px->PS |= (func_sel << (pin_sel * 4));
    return OK;
}

em_result_t gpio_init(brx820_gpio_regdef *px, em_pin_t pin_sel,
                        const str_gpio_init_cfg_t *gpio_init_cfg)
{
    px->CTL_f.INOUT &= (~(1 << pin_sel));
    px->CTL_f.INOUT |= ((1 ^ gpio_init_cfg->gpio_inout) << pin_sel);
    return OK;
}

em_flag_status_t gpio_get(brx820_gpio_regdef *px, em_pin_t pin_sel)
{
    return (px->CTL_f.VALUE >> pin_sel) & 1;
}

em_result_t gpio_set(brx820_gpio_regdef *px, em_pin_t pin_sel)
{
    px->CTL_f.VALUE |= (1 << pin_sel);
    return OK;
}

em_result_t gpio_reset(brx820_gpio_regdef *px, em_pin_t pin_sel)
{
    px->CTL_f.VALUE &= (~(1 << pin_sel));
    return OK;
}

em_result_t gpio_toggle(brx820_gpio_regdef *px, em_pin_t pin_sel)
{
    px->CTL_f.VALUE ^= (1 << pin_sel);
    return OK;
}
