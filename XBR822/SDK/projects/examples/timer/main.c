#include "xbr820.h"
#include "xbr820_timer.h"
#include "bsp_timer.h"
#include "xbr820_interrupts.h"

int main()
{
    timer_irq_cfg(TIMER1_irqhandler, IRQ_PRIORITY_DEFAULT, TIMER1_IRQ);

    timer_init(TIMER1, 40*1000*1000);

    while(1);

    return 0;
}
