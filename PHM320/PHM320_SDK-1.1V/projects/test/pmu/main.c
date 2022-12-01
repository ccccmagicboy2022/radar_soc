#include "phm320_adc.h"
#include "phm320_pmu.h"

int main() {
    str_adc_init_cfg_t adc_init_cfg;
    adc_init_cfg.ADC_CHANNEL = CH1;
    adc_init_cfg.ADC_SAMPLE_MODE = AUTO;
    adc_init_cfg.ADC_SAMPLE_RATE = 1000;
    adc_init(&adc_init_cfg);

    ldo_powered_way(ALWAYS);
    ldo_powered_way(PLUS);

    return 0;
}
