#include "phm320_gpio.h"
#include "phm320_timer.h"
#include "bsp_timer.h"
#include "phm320_interrupts.h"



/*
 * 测试说明：
 * 1、切换不同的定时器PORT和对应的定时器时间
 * 2、通过LED的变化判断定时器中断是否响应
 * 3、测试定时器启动停止是否正常
 * */



int main()
{
    __enable_excp_irq();
    led_init();
    timer_init(TIMER2, DDL_IRQ_PRIORITY_02);
    timer_start(TIMER2, 16100000);
    timer_stop(uint8_t timer_id);
    while (1) {
    ;
    }
    return 0;
}
