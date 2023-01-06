#ifndef __PHM320_ADC_H__
#define __PHM320_ADC_H__

#include "pho_common.h"

typedef enum em_adc_ch_sel
{
    CH1 = 0,
    CH2 = 1,
    CH3 = 2,
    CH4 = 3,
    CH5 = 4,
    CH6 = 5,
    CH7 = 6,
    CH8 = 7,
} em_adc_ch_sel_t;

typedef enum em_adc_sa_mode_t
{
    SINGLE = 0,
    AUTO = 1,
} em_adc_sa_mode_t;

typedef struct str_adc_init
{
    em_adc_ch_sel_t  ADC_CHANNEL;
    em_adc_sa_mode_t ADC_SAMPLE_MODE;
    uint32_t         ADC_SAMPLE_RATE;
} str_adc_init_cfg_t;

//em_result_t adc_init(const str_adc_init_cfg_t *adc_init_cfg);
em_result_t adc_init(unsigned char ch);
em_result_t adc_get_polling(uint16_t *adc_val);
em_result_t adc_start_sample(void);
em_result_t adc_wait_ready(void);
em_result_t adc_get_data(uint16_t *adc_val);
em_result_t adc_clear_flag(void);

#endif

