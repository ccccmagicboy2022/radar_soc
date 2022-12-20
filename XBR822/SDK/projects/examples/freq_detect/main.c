#include "xbr820.h"
#include "xbr820_freq_detect.h"
#include "xbr820_interrupts.h"
#include "bsp_freq_detect.h"

int main()
{
	freq_detect_Cfg f_config;
	uint32_t freq_value = 0;
	
    freq_detect_irq_cfg(freq_detect_irqhandler, IRQ_PRIORITY_DEFAULT, FREQ_DET_IRQ);

	f_config.enable = 1;
	f_config.int_en = 1;
	f_config.interval = 1000;
	
    freq_detect_init(BRX820_FREQ_DETECT, &f_config);

    while(1)
	{
		if (get_freq_det_flag())
		{
			freq_value = freq_get_value(BRX820_FREQ_DETECT);
			set_freq_det_flag(0);
		}
	}

    return 0;
}
