/**
 * @file phm320_adc.h
 * @author Phosense Software Team
 * @brief adc driver C head file
 * @version 1.0.0.0
 * @date 2022-03-18
 * 
 * @copyright Copyright (c) 2022, Phosense-tech, All rights reserved.
 * 
 */

#ifndef __PHM320_ADC_H__
#define __PHM320_ADC_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "pho_common.h"

/**
 * @defgroup adc_group Analog-to-Digital Converter(ADC)
 * @{
 */

/**
 * @brief adc channel selection
 * 
 */
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

/**
 * @brief adc work mode selection
 * 
 */
typedef enum em_adc_sa_mode
{
    SINGLE = 0,
    AUTO = 1,
} em_adc_sa_mode_t;

/**
 * @brief ADC init structure definition
 * 
 */
typedef struct str_adc_init
{
    em_adc_ch_sel_t  ADC_CHANNEL;
    em_adc_sa_mode_t ADC_SAMPLE_MODE;
    uint32_t         ADC_SAMPLE_RATE;
} str_adc_init_cfg_t;

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
em_result_t adc_init(const str_adc_init_cfg_t *adc_init_cfg);
em_result_t adc_get_polling(uint16_t *adc_val);
em_result_t adc_start_sample(void);
em_result_t adc_wait_ready(void);
em_result_t adc_get_data(uint16_t *adc_val);
em_result_t adc_clear_flag(void);

/**  @} adc_group*/

#endif

