#include "bsp_freq_detect.h"
#include "stdint.h"
#include "xbr820.h"
#include "xbr820_freq_detect.h"
#include "xbr820_utility.h"
#include "xbr820_interrupts.h"

uint8_t flag = 0;

uint8_t get_freq_det_flag(void)
{
	return flag;
}

void set_freq_det_flag(uint8_t flag0)
{
	flag = flag0;
}

void freq_detect_irq_cfg(fun_timer _handler, uint8_t _priority, uint8_t _int)
{
    stc_irq_set_cfg_t  irq_set_cfg;
	
    irq_set_cfg.irq_number = _int;
    irq_set_cfg.irq_func_pointer = _handler;
    irq_set_cfg.irq_priority = _priority;
	
    set_irq(&irq_set_cfg);
    start_irq_x(irq_set_cfg.irq_number);
}

__attribute__ ((section ("INT"))) void freq_detect_irqhandler(void)
{
    /*do something*/
    csi_vic_clear_pending_irq(FREQ_DET_IRQ);
	
	if (freq_get_interrupt_status(BRX820_FREQ_DETECT))
	{
		set_freq_det_flag(1);
		freq_clr_interrupt_status(BRX820_FREQ_DETECT);
	}
	
    return;
}
