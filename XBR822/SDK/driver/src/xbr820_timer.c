/**
 * @file xbr820_timer.c
 * @author Phosense Software Team
 * @brief pwm C source file
 * @version 1.0.0.0
 * @date 2022-03-23
 *
 * @copyright Copyright (c) 2022, Phosense-tech, All rights reserved.
 *
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "xbr820_timer.h"
#include "csi_core.h"
#include "xbr820_gpio.h"

/** @{*/

/**
  * @brief  Start the timer. The timer should be set a initial value, or use the default value 0xFFF00000.
  * @param  timer: which is a defined structure, include timerID, counter.
  * @retval 0 for success, -1 for wrong input param.
  */
int timer_enable(Timer_Cfg_t *timer)
{
    if ((timer == NULL) || (timer->id > (CONFIG_TIMER_NUM - 1)))
        return -1;

    brx820_timer_regdef *tmr_reg = ((brx820_timer_regdef*)(BRX820_TIMER1));
    __IO uint32_t* tmr_Init = &(tmr_reg->TIMER_INIT);
    __IO uint32_t* tmr_En = &(tmr_reg->TIMER_CTRL);

    tmr_Init[timer->id] = timer->counter;
    tmr_En[timer->id] = 0x1;

    return 0;
}

/**
  * @brief  Stop the timer.
  * @param  timer: which is a defined structure, include timerID, counter.
  * @retval 0 for success, -1 for wrong input param.
  */
int timer_disable(Timer_Cfg_t *timer)
{
    if ((timer == NULL) || (timer->id > (CONFIG_TIMER_NUM - 1)))
        return -1;

    brx820_timer_regdef *tmr_reg = ((brx820_timer_regdef*)(BRX820_TIMER1));

    __IO uint32_t* tmr_En = &(tmr_reg->TIMER_CTRL);
    tmr_En[timer->id] = 0;

    csi_vic_disable_irq(TIMER1_IRQ + timer->id);

    return 0;
}

/**
  * @brief  Reset the timer according to the param id.
  *                 Reset means counting from the init value again.
  * @param  timer: which is a defined structure, include timerID, counter.
  * @retval 0 for success, -1 for wrong input param.
  */
int timer_reset(Timer_Cfg_t *timer)
{
    if ((timer == NULL) || (timer->id > (CONFIG_TIMER_NUM - 1)))
        return -1;

    brx820_timer_regdef *tmr_reg = ((brx820_timer_regdef*)(BRX820_TIMER1));

    __IO uint32_t* tmr_Init = &(tmr_reg->TIMER_INIT);

    tmr_Init[timer->id] = 0xFFFFF;

    return 0;
}

/**
  * @brief  Restart the timer according to the param id.
  *                 That means counting from the init value again.
  * @param  timer: which is a defined structure, include timerID, counter.
  * @retval 0 for success, -1 for wrong input param.
  */
int timer_restart(Timer_Cfg_t *timer)
{
    if ((timer == NULL) || (timer->id > (CONFIG_TIMER_NUM - 1)))
        return -1;

    brx820_timer_regdef *tmr_reg = ((brx820_timer_regdef*)(BRX820_TIMER1));
    __IO uint32_t* tmr_En = &(tmr_reg->TIMER_CTRL);
    __IO uint32_t* tmr_Init = &(tmr_reg->TIMER_INIT);

    tmr_En[timer->id] = 0;
    tmr_Init[timer->id] = 0xFFFFF;
    tmr_En[timer->id] = 1;

    return 0;
}

/**
  * @brief  Set the timer's initial value.
  * @param  timer: which is a defined structure, include timerID, counter.
  * @retval 0 for success, -1 for wrong input param.
  */
int timer_set_initvalue(Timer_Cfg_t *timer)
{
    if ((timer == NULL) || (timer->id > (CONFIG_TIMER_NUM - 1)))
        return -1;

    brx820_timer_regdef *tmr_reg = ((brx820_timer_regdef*)(BRX820_TIMER1));

    __IO uint32_t* tmr_Init = &(tmr_reg->TIMER_INIT);
    tmr_Init[timer->id] = timer->counter;

    return 0;
}

/**
  * @brief  Get the timer's initial value.
  * @param  timer: which is a defined structure, include timerID, counter.
  * @retval To return the timer's initial value for success. -1 for wrong input param.
  */
int timer_get_initvalue(Timer_Cfg_t *timer)
{
    int retval = 0;
    if ((timer == NULL) || (timer->id > (CONFIG_TIMER_NUM - 1)))
        return -1;

    brx820_timer_regdef *tmr_reg = ((brx820_timer_regdef*)(BRX820_TIMER1));

    __IO uint32_t* tmr_Init = &(tmr_reg->TIMER_INIT);
    retval = tmr_Init[timer->id];
    return retval;
}

/**
  * @brief  Get the timer's current value.
  * @param  timer: which is a defined structure, include timerID, counter.
  * @retval  the timer's current value; -1 for wrong timer id.
  */
int timer_get_currentval(Timer_Cfg_t *timer)
{
    int retval = 0;

    if ((timer == NULL) || (timer->id > (CONFIG_TIMER_NUM - 1)))
        return -1;

    brx820_timer_regdef *tmr_reg = ((brx820_timer_regdef*)(BRX820_TIMER1));

    __I uint32_t *tmrCurr = &(tmr_reg->TIMER_CNT);
    retval = tmrCurr[timer->id];
    return retval;
}

/**  @} timer_group*/

