#include "phm320_timer.h"
#include "typdef.h"
#include "csi_core.h"
#include "phm320_gpio.h"
#include "phm320.h"

/**
  * @brief  Start the timer. The timer should be set a initial value, or use the default value 0xFFF00000.
  * @param  timer: which is a defined structure, include timerID, counter.
  * @retval 0 for success, -1 for wrong input param.
  */
int timer_enable(Timer_Cfg_t *timer)
{
    if ((timer == NULL) || (timer->id > (CONFIG_TIMER_NUM - 1)))
        return -1;

   STC_reg_st *tmr_reg = ((STC_reg_st*)(PHM320_STC_BASE));
    __IO uint32_t* tmr_Init = &(tmr_reg->tmr0_init_val);

    tmr_Init[timer->id] = timer->counter;

    tmr_reg->enable.encfg |= (0x10 << (timer->id));
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

    STC_reg_st *tmr_reg = ((STC_reg_st*)(PHM320_STC_BASE));

    tmr_reg->enable.encfg &= ~(0x10 << (timer->id));

    csi_vic_disable_irq(INT_003 + timer->id);

    return 0;
}

/**
  * @brief  Reset the timer according to the param id.
  * 				Reset means counting from the init value again.
  * @param  timer: which is a defined structure, include timerID, counter.
  * @retval 0 for success, -1 for wrong input param.
  */
int timer_reset(Timer_Cfg_t *timer)
{
    if ((timer == NULL) || (timer->id > (CONFIG_TIMER_NUM - 1)))
        return -1;

    STC_reg_st *tmr_reg = ((STC_reg_st*)(PHM320_STC_BASE));
    tmr_reg->enable.encfg |= (0x100 << (timer->id));
    return 0;
}

/**
  * @brief  Restart the timer according to the param id.
  * 				That means counting from the init value again.
  * @param  timer: which is a defined structure, include timerID, counter.
  * @retval 0 for success, -1 for wrong input param.
  */
int timer_restart(Timer_Cfg_t *timer)
{
    if ((timer == NULL) || (timer->id > (CONFIG_TIMER_NUM - 1)))
        return -1;

    STC_reg_st *tmr_reg = ((STC_reg_st*)(PHM320_STC_BASE));
    tmr_reg->enable.encfg |= (0x100 << (timer->id));
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

    STC_reg_st *tmr_reg = ((STC_reg_st*)(PHM320_STC_BASE));

    __IO uint32_t *tmr_Init = &(tmr_reg->tmr0_init_val);
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

    STC_reg_st *tmr_reg = ((STC_reg_st*) (PHM320_STC_BASE));
    __IO uint32_t *tmr_Init = &(tmr_reg->tmr0_init_val);
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

    STC_reg_st *tmr_reg = ((STC_reg_st*)(PHM320_STC_BASE));
    __I uint32_t *tmrCurr = &(tmr_reg->tmr0_cur_cnt);
    retval = tmrCurr[timer->id];
    return retval;
}

/**
  * @brief  Enable the WatchDog timer. This is a cpu watchdog, only reset cpu not system.
  * @param  wdg: which is a defined structure, include watchdog counter, enable and reset enable settings.
  * @retval 0 for success, -1 for wrong input param.
  */
int wdg_config(WDGCfg *wdg)
{
    if (wdg == NULL)
        return -1;

    STC_reg_st *tmr_reg = ((STC_reg_st*)(PHM320_STC_BASE ));

    tmr_reg->wdg_cnt = wdg->counter;
    tmr_reg->enable.bits.wdg_rst_en = wdg->reset_enable;	/* watch dog reset enable*/
    tmr_reg->enable.bits.wdg_en = wdg->enable;		/* watch dog counter enable */
    return 0;
}

