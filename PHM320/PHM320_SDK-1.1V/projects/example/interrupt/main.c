#include "phm320_interrupts.h"

void irq_test(void)
{
    while (1) {}
}

int main()
{
    irq_enable_all();
    stc_irq_set_cfg_t irq_000_set_cfg;
    irq_000_set_cfg.irq_number = INT_000; /* irq number */
    irq_000_set_cfg.irq_func_pointer = &irq_test;
    irq_000_set_cfg.irq_priority = IRQ_PRIORITY_DEFAULT;
    irq_init(&irq_000_set_cfg);
    irq_start_x(irq_000_set_cfg.irq_number);
    while (1) {}

    irq_stop_x(irq_000_set_cfg.irq_number);
    irq_disable_all();
    return 0;
}
