#include "stdint.h"
#include "xbr820.h"
#include "xbr820_wdg.h"

/**
 * @brief  wdg initialize.
 * @note   The wdg will react to the remoter from now on.
 * @param  wdg_handler, wdg_priority .
 * @retval none.
 */
void wdg_priority_cfg(fun_wdg wdg_handler, uint8_t wdg_priority)
{
    stc_irq_set_cfg_t  irq_wdg_set_cfg;
	
    irq_wdg_set_cfg.irq_number = WDG_IRQ;
    irq_wdg_set_cfg.irq_func_pointer = wdg_handler;
    irq_wdg_set_cfg.irq_priority = wdg_priority;
    set_irq(&irq_wdg_set_cfg);
	
    start_irq_x(irq_wdg_set_cfg.irq_number);
}

/**
 * @brief  wdg initialize.
 * @note   The wdg will react to the remoter from now on.
 * @param  timer_cfg and counter.
 * @retval none.
 */
void wdg_init(const str_wdg_init_t *wdg_init_cfg)
{
    uint32_t counter;

    counter = wdg_init_cfg->duty_ms / 1000 * SYSTEM_CLOCK;

    wdg_enable(BRX820_WDG, counter);
}

__attribute__ ((section ("INT"))) void WDG_irqhandler(void)
{
    /*do something*/
    csi_vic_clear_pending_irq(WDG_IRQ);
    return;
}

/**
  * @brief  enable the WatchDog timer. This is a cpu watchdog, only reset cpu not system.
  * @param  wdg: which is a defined structure, include watchdog counter, enable and reset enable settings.
  * @retval none.
  */
void wdg_enable(brx820_wdg_regdef *wdg, uint32_t wdg_counter)
{
    assert_param(IS_WDG_PERIPH(wdg));

    wdg->WDG_CFG_f.WDG_INT_EN = 1;
    wdg->WDG_CFG_f.WDG_RST_EN = 1;
    wdg->STC_WDG_CNT_REG = wdg_counter;
}


/**
  * @brief   wdg_disable.
  * @param  wdg: which is a defined structure
  * @retval none.
  */
void wdg_disable(brx820_wdg_regdef *wdg)
{
    assert_param(IS_WDG_PERIPH(wdg));

    wdg->WDG_CFG_f.WDG_INT_EN = 0;
    wdg->WDG_CFG_f.WDG_RST_EN = 0;
}

void feed_dog(brx820_wdg_regdef *wdg)
{
    assert_param(IS_WDG_PERIPH(wdg));

    wdg->WDG_CFG_f.WDG_RST_EN = 0;
    wdg->WDG_CFG_f.WDG_RST_EN = 1;
}


