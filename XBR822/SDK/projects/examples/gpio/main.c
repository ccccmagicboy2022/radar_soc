#include "xbr820_gpio.h"
#include "xbr820.h"

int main()
{
    int a = 0;
    pin_set_func(BRX820_GPIO_PA, PX_0, PA0_FUNC_GPIO);

    str_gpio_init_cfg_t gpio_cfg;
    gpio_cfg.gpio_inout = GPIO_OUT;
    gpio_init(BRX820_GPIO_PA, PX_0, &gpio_cfg);

    gpio_set(BRX820_GPIO_PA, PX_0);
    gpio_reset(BRX820_GPIO_PA, PX_0);
    gpio_toggle(BRX820_GPIO_PA, PX_0);

    pin_set_func(BRX820_GPIO_PA, PX_7, PA7_FUNC_UART_TX);
    pin_set_func(BRX820_GPIO_PA, PX_6, PA6_FUNC_UART_RX);

    gpio_cfg.gpio_inout   = GPIO_IN;
    gpio_cfg.gpio_int_en = ENABLE;
    gpio_init(BRX820_GPIO_PA, PX_1, &gpio_cfg);
    a = gpio_get(BRX820_GPIO_PA, PX_1);
}
