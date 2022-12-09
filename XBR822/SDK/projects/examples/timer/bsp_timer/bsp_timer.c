#include "bsp_timer.h"
#include "stdint.h"
#include "xbr820.h"
#include "xbr820_timer.h"
#include "xbr820_utility.h"

/**
 * @brief  timer_priority_cfg
 * @note   The timer will react to the remoter from now on.
 * @param  timer_handler, timer_priority and timer_int.
 * @retval none.
 */
void timer_priority_cfg(fun_timer timer_handler, uint8_t timer_priority, uint8_t timer_int)
{
    assert_param(IS_TIMER_CONFIG_IT(timer_priority));
    assert_param(IS_TIMER_CONFIG_INT(timer_int));

    stc_irq_set_cfg_t  irq_timer_set_cfg;
    irq_timer_set_cfg.irq_number = timer_int;
    irq_timer_set_cfg.irq_func_pointer = timer_handler;
    irq_timer_set_cfg.irq_priority = timer_priority;
    set_irq(&irq_timer_set_cfg);
    start_irq_x(irq_timer_set_cfg.irq_number);
}

/**
 * @brief  timer initialize.
 * @note   The timer will react to the remoter from now on.
 * @param  timer_cfg and counter,.
 * @retval none.
 */
void timer_init(TIMER_t *timer, uint32_t counter)
{
    //set_pin_func(P1_5, FUNC_IR);
    timer_enable(timer, counter);
}

__attribute__ ((section ("INT"))) void TIMER1_irqhandler(void)
{
    /*do something*/
    csi_vic_clear_pending_irq(TIMER1_IRQ);
    return;
}

__attribute__ ((section ("INT"))) void TIMER2_irqhandler(void)
{
    /*do something*/
    csi_vic_clear_pending_irq(TIMER2_IRQ);
    return;
}

__attribute__ ((section ("INT"))) void TIMER3_irqhandler(void)
{
    /*do something*/
    csi_vic_clear_pending_irq(TIMER3_IRQ);
    return;
}

__attribute__ ((section ("INT"))) void TIMER4_irqhandler(void)
{
    /*do something*/
    csi_vic_clear_pending_irq(TIMER4_IRQ);
    return;
}