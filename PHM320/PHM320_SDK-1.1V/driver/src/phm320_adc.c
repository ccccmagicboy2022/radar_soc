/**
 * @file phm320_adc.c
 * @author Phosense Software Team
 * @brief adc driver C source file
 * @version 1.0.0.0
 * @date 2022-03-18
 * 
* @copyright Copyright (c) 2022, Phosense-tech, All rights reserved.
 * 
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "phm320_adc.h"

/** @{*/

/**
 * @brief initializes an ADC instance.
 * 
 * @param [in] adc_init_cfg pointer to ADC initialization structure.
 *                          see @ref str_adc_init_cfg_t for details.
 * @return em_result_t 
 * - OK no error occurred.
 * - ERRORINVALIDPARAMETER parameter error.
 */
em_result_t adc_init(const str_adc_init_cfg_t *adc_init_cfg)
{
    PHM320_TOP->ADC_CTL_BITS.ADC_CH_MUX = adc_init_cfg->ADC_CHANNEL;
    PHM320_TOP->ADC_CTL_BITS.ADC_EN = 1;
    if (adc_init_cfg->ADC_SAMPLE_MODE) {
        PHM320_TOP->TOP_CTLB_BITS.ADC_TRG_SEL = 0;
        PHM320_TOP->BB_CTL = (PHM320_TOP->BB_CTL & (~0xfful)) \
                            | ((32000 / adc_init_cfg->ADC_SAMPLE_RATE) & 0xfful);
        PHM320_TOP->BB_CTL_BITS.BPEN = 1;
    } else {
        PHM320_TOP->TOP_CTLB_BITS.ADC_TRG_SEL = 1;
    }

    return Ok;
}

/**
 * @brief start ADC, and get the data.
 * 
 * @param [out] adc_val the address to store ADC value.
 * @return em_result_t
 * - OK no error occurred. 
 */
em_result_t adc_get_polling(uint16_t *adc_val)
{
    adc_wait_ready();
    adc_get_data(adc_val);
    adc_clear_flag();
    return Ok;
}

/**
 * @brief start ADC.
 * 
 * @return em_result_t
 * - OK no error occurred. 
 */
em_result_t adc_start_sample(void)
{
    PHM320_TOP->TOP_CTLB_BITS.ADC_TRG = 1;
    delay_us(1);
    PHM320_TOP->TOP_CTLB_BITS.ADC_TRG = 0;
    return Ok;
}

/**
 * @brief wait adc ready
 * 
  * @return em_result_t
 * - OK no error occurred. 
 */
em_result_t adc_wait_ready(void)
{
    while (!(PHM320_TOP->TOP_INT_FLAG_BITS.ADC)) {}
    return Ok;
}

/**
 * @brief get adc data
 * 
 * @param [out] adc_val the address to store ADC value.
 * @return em_result_t
 * - OK no error occurred. 
 */
em_result_t adc_get_data(uint16_t *adc_val)
{
    *adc_val = PHM320_TOP->ADC_DATA;
    return Ok;
}

/**
 * @brief clear adc finish flag for next get data
 * 
 * @return em_result_t
 * - OK no error occurred.  
 */
em_result_t adc_clear_flag(void)
{
    PHM320_TOP->TOP_INT_CLEAR_BITS.ADC = 1;
    return Ok;
}

/**  @} adc_group*/