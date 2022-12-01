#include "phm320_gpio.h"
#include "phm320_timer.h"
#include "bsp_timer.h"
#include "phm320_interrupts.h"







int main()
{
    __enable_excp_irq();
    led_init();
    timer_init(TIMER2, DDL_IRQ_PRIORITY_02);
    timer_start(TIMER2, 1000000);
    watch_dog(1,1,16100000);  //递减计数
    
    static int num = 0;
      while (1) {
      num++;

	if(num == 50000)
	{
	    num = 0;
	    gpio_toggle(P1_2); 
	   break;
	}
    }
    return 0;
}
