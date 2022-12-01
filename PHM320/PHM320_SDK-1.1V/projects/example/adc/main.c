#include "phm320_adc.h"
int main() {
	unsigned short int a;

    str_adc_init_cfg_t adc_init_cfg;
    adc_init_cfg.ADC_CHANNEL = CH1;
    adc_init_cfg.ADC_SAMPLE_MODE = SINGLE;
    adc_init(&adc_init_cfg);
    while (1) {
        delay_us(1000);
        adc_start_sample();
        adc_get_polling(&a);
    }
}
