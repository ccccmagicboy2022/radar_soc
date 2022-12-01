#include "phm320_gpio.h"
#include "phm320_ir.h"
#include "bsp_ir.h"
#include "phm320_interrupts.h"


int main()
{
    irq_enable_all();
    led_init();
    ir_init(IRQ_PRIORITY_DEFAULT);
    
    while (1) {
        ir_test();
    }
    return 0;
}
