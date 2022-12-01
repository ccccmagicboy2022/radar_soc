#include "phm320_interrupts.h"
#include "bsp_timer.h"
#include "phm320_timer.h"
#include "phm320_interrupts.h"
#include "phm320.h"
#include "phm320_gpio.h"


void timer_init(uint8_t timer_id,  uint8_t timer_priority)
{
    str_irq_set_cfg_t  irq_timer_set_cfg;
    switch (timer_id) {
    case TIMER0:
        irq_timer_set_cfg.irq_number = INT_003;
        irq_timer_set_cfg.irq_func_pointer = &TIM0_IRQHandler;
        irq_timer_set_cfg.irq_priority = timer_priority;
        irq_init(&irq_timer_set_cfg);
        irq_start_x(irq_timer_set_cfg.irq_number);
        break;
    case TIMER1:
        irq_timer_set_cfg.irq_number = INT_004;
        irq_timer_set_cfg.irq_func_pointer = &TIM1_IRQHandler;
        irq_timer_set_cfg.irq_priority = timer_priority;
        irq_init(&irq_timer_set_cfg);
        irq_start_x(irq_timer_set_cfg.irq_number);
        break;
    case TIMER2:
        irq_timer_set_cfg.irq_number = INT_005;
        irq_timer_set_cfg.irq_func_pointer = &TIM2_IRQHandler;
        irq_timer_set_cfg.irq_priority = timer_priority;
        irq_init(&irq_timer_set_cfg);
        irq_start_x(irq_timer_set_cfg.irq_number);
        break;
    case TIMER3:
        irq_timer_set_cfg.irq_number = INT_006;
        irq_timer_set_cfg.irq_func_pointer = &TIM3_IRQHandler;
        irq_timer_set_cfg.irq_priority = timer_priority;
        irq_init(&irq_timer_set_cfg);
        irq_start_x(irq_timer_set_cfg.irq_number);
        break;
    default:
        break;
    }
}
void timer_start(uint8_t timer_id, uint32_t timer_cmpvalue)
{
    Timer_Cfg_t timerconf;
    timerconf.id  = timer_id;
    timerconf.counter = timer_cmpvalue;       /*16100000 -- 1s*/
    timer_enable(&timerconf);
}

void timer_stop(uint8_t timer_id)
{
    Timer_Cfg_t timerconf;
    timerconf.id  = timer_id;
    timer_disable(&timerconf);
}

void watch_dog(uint8_t dog_reset_enable, uint8_t dog_counter_enable, uint32_t dog_cmpvalue)
{
    WDGCfg dogconf;
    dogconf.enable = dog_counter_enable;
    dogconf.reset_enable = dog_reset_enable;
    dogconf.counter = dog_cmpvalue;

    wdg_config(&dogconf);
}

void led_init(void)
{
    pin_set_func(P1_2, FUNC_GPIO);
    str_gpio_init_cfg_t gpio_cfg;
    gpio_cfg.gpio_mode   = GPIO_OUT;
    gpio_init(P1_2, &gpio_cfg);
}


#define   STCCTL    (PHM320_STC_BASE + 0x00)
#define   TMCLR(i)			(0x100 << (i))

__attribute__ ((section ("INT")))  void timer_irqhandler(int index)
{
      reg32_set(STCCTL, TMCLR(index));
}

 __attribute__ ((section ("INT"))) void TIM0_IRQHandler(void)
{
    timer_irqhandler(0);
    gpio_toggle(P1_2);
}

__attribute__ ((section ("INT"))) void TIM1_IRQHandler(void)
{
    timer_irqhandler(1);
    gpio_toggle(P1_2);
}

__attribute__ ((section ("INT"))) void TIM2_IRQHandler(void)
{
    timer_irqhandler(2);
    gpio_toggle(P1_2);
}
__attribute__ ((section ("INT"))) void TIM3_IRQHandler(void)
{
    timer_irqhandler(3);
     gpio_toggle(P1_2);
}

__attribute__ ((section ("INT"))) void WDG_IRQHandler(void)
{
    
}