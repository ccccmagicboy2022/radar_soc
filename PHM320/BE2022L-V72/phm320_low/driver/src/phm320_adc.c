
#include "phm320_adc.h"

/*
em_result_t adc_init(const str_adc_init_cfg_t *adc_init_cfg)
{
    PHM320_TOP->ADC_CTL_BITS.ADC_CH_MUX = adc_init_cfg->ADC_CHANNEL;
    PHM320_TOP->ADC_CTL_BITS.ADC_EN = 1;
    //if (adc_init_cfg->ADC_SAMPLE_MODE) {
        PHM320_TOP->TOP_CTLB_BITS.ADC_TRG_SEL = 0;
      //  PHM320_TOP->BB_CTL = (PHM320_TOP->BB_CTL & (~0xfful)) | ((32000 / adc_init_cfg->ADC_SAMPLE_RATE) & 0xfful);
	   PHM320_TOP->BB_CTL = (PHM320_TOP->BB_CTL & (~0xfful)) | (2 & 0xfful);
        PHM320_TOP->BB_CTL_BITS.BPEN = 1;
   // } 
	//else {
   //     PHM320_TOP->TOP_CTLB_BITS.ADC_TRG_SEL = 1;
   // }

    return Ok;
}
*/

em_result_t adc_init(unsigned char ch)		//默认AUTO,16000
{
    PHM320_TOP->ADC_CTL_BITS.ADC_CH_MUX = ch;
    PHM320_TOP->ADC_CTL_BITS.ADC_EN = 1;
	
   // if (adc_init_cfg->ADC_SAMPLE_MODE) 
	{
        PHM320_TOP->TOP_CTLB_BITS.ADC_TRG_SEL = 0;
 //       PHM320_TOP->BB_CTL = (PHM320_TOP->BB_CTL & (~0xfful)) \
 //                           | ((32000 / adc_init_cfg->ADC_SAMPLE_RATE) & 0xfful);
  
      PHM320_TOP->BB_CTL = (PHM320_TOP->BB_CTL & (~0xfful)) | (2*20);	//1K FS				
							
        PHM320_TOP->BB_CTL_BITS.BPEN = 1;
    } 
	//else 
	//{
    //    PHM320_TOP->TOP_CTLB_BITS.ADC_TRG_SEL = 1;
    //}

    return Ok;
}

/*
em_result_t adc_get_polling(uint16_t *adc_val)
{
    adc_wait_ready();
    adc_get_data(adc_val);
    adc_clear_flag();
    return Ok;
}

em_result_t adc_start_sample(void)
{
    PHM320_TOP->TOP_CTLB_BITS.ADC_TRG = 1;
    delay_us(1);
    PHM320_TOP->TOP_CTLB_BITS.ADC_TRG = 0;
    return Ok;
}

em_result_t adc_wait_ready(void)
{
    while (!(PHM320_TOP->TOP_INT_FLAG_BITS.ADC)) {}
    return Ok;
}

em_result_t adc_get_data(uint16_t *adc_val)
{
    *adc_val = PHM320_TOP->ADC_DATA;
    return Ok;
}

em_result_t adc_clear_flag(void)
{
    PHM320_TOP->TOP_INT_CLEAR_BITS.ADC = 1;
    return Ok;
}
*/