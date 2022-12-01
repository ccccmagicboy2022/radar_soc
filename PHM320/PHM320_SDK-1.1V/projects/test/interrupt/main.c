#include "phm320_interrupts.h"

void irq_test_000(void)
{
    csi_vic_set_pending_irq(INT_001);
    irq_enable_all();
    while (1) {}
}

void irq_test_001(void)
{
    csi_vic_set_pending_irq(INT_002);
    irq_enable_all();
    while (1) {}
}

void irq_test_002(void)
{
    csi_vic_set_pending_irq(INT_003);
    irq_enable_all();
    while (1) {}
}

void irq_test_003(void)
{
    csi_vic_set_pending_irq(INT_004);
    irq_enable_all();
    while (1) {}
}

void irq_test_004(void)
{
    csi_vic_set_pending_irq(INT_005);
    irq_enable_all();
    while (1) {}
}

void irq_test_005(void)
{
    csi_vic_set_pending_irq(INT_006);
    irq_enable_all();
    while (1) {}
}

void irq_test_006(void)
{
    while (1) {}
}


int main()
{
	*(uint32_t *)0xe0800000 = 7;
    irq_enable_all();
    str_irq_set_cfg_t irq_set_cfg;
    irq_set_cfg.irq_number = INT_000;
    irq_set_cfg.irq_func_pointer = &irq_test_000;
    irq_set_cfg.irq_priority = DDL_IRQ_PRIORITY_00;
    irq_init(&irq_set_cfg);
    irq_start_x(irq_set_cfg.irq_number);

    irq_set_cfg.irq_number = INT_001;
    irq_set_cfg.irq_func_pointer = &irq_test_001;
    irq_set_cfg.irq_priority = DDL_IRQ_PRIORITY_01;
    irq_init(&irq_set_cfg);
    irq_start_x(irq_set_cfg.irq_number);

    irq_set_cfg.irq_number = INT_002;
    irq_set_cfg.irq_func_pointer = &irq_test_002;
    irq_set_cfg.irq_priority = DDL_IRQ_PRIORITY_02;
    irq_init(&irq_set_cfg);
    irq_start_x(irq_set_cfg.irq_number);

    irq_set_cfg.irq_number = INT_003;
    irq_set_cfg.irq_func_pointer = &irq_test_003;
    irq_set_cfg.irq_priority = DDL_IRQ_PRIORITY_03;
    irq_init(&irq_set_cfg);
    irq_start_x(irq_set_cfg.irq_number);

    irq_set_cfg.irq_number = INT_004;
    irq_set_cfg.irq_func_pointer = &irq_test_004;
    irq_set_cfg.irq_priority = DDL_IRQ_PRIORITY_04;
    irq_init(&irq_set_cfg);
    irq_start_x(irq_set_cfg.irq_number);

    irq_set_cfg.irq_number = INT_005;
    irq_set_cfg.irq_func_pointer = &irq_test_005;
    irq_set_cfg.irq_priority = DDL_IRQ_PRIORITY_05;
    irq_init(&irq_set_cfg);
    irq_start_x(irq_set_cfg.irq_number);

    irq_set_cfg.irq_number = INT_006;
    irq_set_cfg.irq_func_pointer = &irq_test_006;
    irq_set_cfg.irq_priority = DDL_IRQ_PRIORITY_06;
    irq_init(&irq_set_cfg);
    irq_start_x(irq_set_cfg.irq_number);

    csi_vic_set_pending_irq(INT_000);

    while (1) {}

    irq_stop_x(irq_set_cfg.irq_number);
    irq_disable_all();
    return 0;
}
