#include "gpio.h"

void gpio_config()
{
    pin_set_func(P1_0, FUNC_GPIO);
	pin_set_func(P1_1, FUNC_GPIO);
	
    str_gpio_init_cfg_t gpio_cfg;
    clear_mem_struct(gpio_cfg);

    gpio_cfg.gpio_mode   = GPIO_OUT;
    gpio_init(P1_0, &gpio_cfg);
	//gpio_set(P1_0);
	PHM320_TOP->GPIO_VAL |= (1ul << P1_0);
	
    gpio_init(P1_4, &gpio_cfg);
	pin_set_func(P1_4,FUNC_PWM);
	
    gpio_cfg.gpio_mode     = GPIO_IN;
    gpio_cfg.gpio_int_en   = ENABLE;
    gpio_cfg.gpio_trg_mode = FALLING_EDGE;
    gpio_init(P1_1, &gpio_cfg);


 
    str_irq_set_cfg_t irq_set_000_cfg;
    irq_set_000_cfg.irq_number = INT_000;
    irq_set_000_cfg.irq_func_pointer = &irq_test;
    irq_set_000_cfg.irq_priority = IRQ_PRIORITY_DEFAULT;
    irq_init(&irq_set_000_cfg);
    irq_start_x(irq_set_000_cfg.irq_number);

    irq_disable_all();
	

}

