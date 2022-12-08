/**
 * @file xbr820_adc.c
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
#include "xbr820_adc.h"

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
    //adc_init_cfg->ADC_CHANNEL;
    BRX820_DSP_ADC->CTL_f.ADC_DIV = SYSTEM_CLOCK / adc_init_cfg->ADC_SAMPLE_RATE;
    BRX820_DSP_ADC->CTL_f.TRI_MODE = adc_init_cfg->ADC_SAMPLE_TRI_MODE;
    BRX820_DSP_ADC->CTL_f.TRI_SRC = adc_init_cfg->ADC_SAMPLE_TRI_SRC;
    BRX820_DSP_ADC->DELAY_f.ADC_DELAY = adc_init_cfg->ADC_SAMPLE_DELAY_CYCLE;
    BRX820_DSP_ADC->RANGE_f.ADC_BEGIN = adc_init_cfg->ADC_SAMPLE_BEGIN;
    BRX820_DSP_ADC->RANGE_f.ADC_END = adc_init_cfg->ADC_SAMPLE_END;

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
    xbr820_TOP->TOP_CTLB_BITS.ADC_TRG = 1;
    delay_us(1);
    xbr820_TOP->TOP_CTLB_BITS.ADC_TRG = 0;
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
    while (!(xbr820_TOP->TOP_INT_FLAG_BITS.ADC)) {}
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
    *adc_val = PHM820_TOP->ADC_DATA;
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
    PHM820_TOP->TOP_INT_CLEAR_BITS.ADC = 1;
    return Ok;
}

/**  @} adc_group*/