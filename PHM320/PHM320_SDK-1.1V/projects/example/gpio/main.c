#include "phm320_gpio.h"
int main() {
    int a;
    pin_set_func(P1_0, FUNC_GPIO);
    str_gpio_init_cfg_t gpio_cfg;
    gpio_cfg.gpio_mode   = GPIO_OUT;
    gpio_init(P1_0, &gpio_cfg);
    gpio_set(P1_0);
    gpio_reset(P1_0);
    gpio_toggle(P1_0);

    pin_set_func(P1_2, FUNC_PWM);
    pin_set_func(P1_3, FUNC_BBP);
    pin_set_func(P1_5, FUNC_IR);

    gpio_cfg.gpio_mode   = GPIO_IN;
    gpio_cfg.gpio_int_en = ENABLE;
    gpio_init(P1_1, &gpio_cfg);
    a = gpio_get(P1_1);
}
