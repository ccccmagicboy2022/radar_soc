#include "phm320_gpio.h"
#include "phm320_timer.h"
#include "bsp_timer.h"
#include "phm320_interrupts.h"







int main()
{
    __enable_excp_irq();
    led_init();
    timer_init(TIMER2, DDL_IRQ_PRIORITY_02);
    timer_start(TIMER2, 16100000);

    while (1) {
    ;
    }
    return 0;
}
