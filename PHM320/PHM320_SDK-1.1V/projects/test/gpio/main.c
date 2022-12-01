#include "phm320_gpio.h"
#include "phm320_interrupts.h"

void irq_test(void)
{
    top_clear_flag();
    while (gpio_get_flag(P1_0) || gpio_get_flag(P1_1) \
            || gpio_get_flag(P1_1) || gpio_get_flag(P1_1)) {
        if (gpio_get_flag(P1_0)) {
            gpio_clear_flag(P1_0);
            // to do
        }
        if (gpio_get_flag(P1_1)) {
            gpio_clear_flag(P1_1);
            // to do
        }
        if (gpio_get_flag(P1_2)) {
            gpio_clear_flag(P1_2);
            // to do
        }
        if (gpio_get_flag(P1_3)) {
            gpio_clear_flag(P1_3);
            // to do
        }
    }
}

int main() {
	
	str_gpio_init_cfg_t gpio_cfg;
	clear_mem_struct(gpio_cfg);
	gpio_cfg.gpio_mode     = GPIO_OUT;
    gpio_init(P1_0, &gpio_cfg);	

	clear_mem_struct(gpio_cfg);
    gpio_cfg.gpio_mode     = GPIO_IN;
    gpio_cfg.gpio_int_en   = ENABLE;
    gpio_cfg.gpio_trg_mode = RISING_EDGE;
    gpio_init(P1_2, &gpio_cfg);

    irq_enable_all();
    str_irq_set_cfg_t irq_set_000_cfg;
    irq_set_000_cfg.irq_number = INT_000;
    irq_set_000_cfg.irq_func_pointer = &irq_test;
    irq_set_000_cfg.irq_priority = IRQ_PRIORITY_DEFAULT;
    irq_init(&irq_set_000_cfg);
    irq_start_x(irq_set_000_cfg.irq_number);
	
	top_clear_flag();

    while (1) {
		delay_us(100);
		gpio_toggle(P1_0);
	}

    irq_stop_x(irq_set_000_cfg.irq_number);
    irq_disable_all();
    return 0;
}
