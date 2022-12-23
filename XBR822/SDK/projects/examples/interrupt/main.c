#include "xbr820.h"
#include "xbr820_interrupts.h"

__attribute__ ((section ("INT"))) void irq_test(void)
{
    while(1);
}

int main()
{
    enable_irq_all();

    stc_irq_set_cfg_t irq_000_set_cfg;

    irq_000_set_cfg.irq_number = GPIO_PA0_IRQ;
    irq_000_set_cfg.irq_func_pointer = &irq_test;
    irq_000_set_cfg.irq_priority = IRQ_PRIORITY_DEFAULT;

    set_irq(&irq_000_set_cfg);

    start_irq_x(irq_000_set_cfg.irq_number);

    while(1);
    return 0;
}
