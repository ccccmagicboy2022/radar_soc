#include "phm320_adc.h"
#include "phm320_interrupts.h"

unsigned short int a;

void irq_test(void)
{
    adc_get_data(&a);
    adc_clear_flag();
}

int main() {
    str_adc_init_cfg_t adc_init_cfg;
#ifdef __AUTO_ADC
    adc_init_cfg.ADC_CHANNEL = CH1;
    adc_init_cfg.ADC_SAMPLE_MODE = AUTO;
    adc_init_cfg.ADC_SAMPLE_RATE = 1000;
    adc_init(&adc_init_cfg);
    while (1) {
        adc_get_polling(&a);
    }
#endif

#ifdef __SINGLE_ADC
    adc_init_cfg.ADC_CHANNEL = CH1;
    adc_init_cfg.ADC_SAMPLE_MODE = SINGLE;
    adc_init(&adc_init_cfg);
    while (1) {
        delay_us(1000);
        adc_start_sample();
        adc_get_polling(&a);
    }
#endif

#ifdef __INT_ADC
    adc_init_cfg.ADC_CHANNEL = CH1;
    adc_init_cfg.ADC_SAMPLE_MODE = SINGLE;
    adc_init(&adc_init_cfg);

    irq_enable_all();
    str_irq_set_cfg_t irq_000_set_cfg;
    irq_000_set_cfg.irq_number = INT_000;
    irq_000_set_cfg.irq_func_pointer = &irq_test;
    irq_000_set_cfg.irq_priority = IRQ_PRIORITY_DEFAULT;
    irq_init(&irq_000_set_cfg);
    irq_start_x(irq_000_set_cfg.irq_number);

    PHM320_TOP->TOP_INT_MASK_BITS.ADC = 0;
    PHM320_TOP->TOP_INT_MODE_BITS.ADC = 0b100;

    while (1) {
        delay_us(1000);
        adc_start_sample();
    }

    irq_stop_x(irq_000_set_cfg.irq_number);
    irq_disable_all();
#endif
    return 0;
}
