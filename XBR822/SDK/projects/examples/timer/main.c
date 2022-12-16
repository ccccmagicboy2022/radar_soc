#include "xbr821.h"
#include "xbr821_timer.h"
#include "bsp_timer.h"
#include "xbr821_interrupts.h"


int main()
{
    timer_priority_cfg(TIMER1_irqhandler, IRQ_PRIORITY_DEFAULT, TIMER1_IRQ);

    timer_init(TIMER1, 16100000);

    while(1);

    return 0;
}
