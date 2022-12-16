#include "xbr821_interrupts.h"
#include "xbr821_ir.h"
#include "bsp_ir.h"



int main()
{
    enable_irq_all();
    ir_init(IRQ_PRIORITY_DEFAULT);
    while(1)
    {
        ir_test();
    }
    return 0;
}
