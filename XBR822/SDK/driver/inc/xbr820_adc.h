/**
 * @file xbr820_adc.h
 * @author Phosense Software Team
 * @brief adc driver C head file
 * @version 1.0.0.0
 * @date 2022-12-08
 * 
 * @copyright Copyright (c) 2022, Phosense-tech, All rights reserved.
 * 
 */

#ifndef __XBR820_ADC_H__
#define __XBR820_ADC_H__

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
} em_adc_ch_sel_t;

/**
 * @brief adc trigger mode selection
 * 
 */
typedef enum em_adc_trigger_mode
{
    SCAN_PERIOD = 0,
    WHOLE_CHIRP = 1,
} em_adc_trigger_mode_t;

/**
 * @brief adc trigger source selection
 * 
 */
typedef enum em_adc_trigger_src
{
    ADC_DONE = 0,
    ADC_TD = 1,
} em_adc_trigger_src_t;


/**
 * @brief ADC init structure definition
 * 
 */
typedef struct str_adc_init
{
    em_adc_ch_sel_t  ADC_CHANNEL;
    em_adc_trigger_mode_t ADC_SAMPLE_TRI_MODE;
    em_adc_trigger_src_t ADC_SAMPLE_TRI_SRC;
    uint32_t         ADC_SAMPLE_RATE;
    uint32_t         ADC_SAMPLE_DELAY_CYCLE;
    uint32_t         ADC_SAMPLE_BEGIN;
    uint32_t         ADC_SAMPLE_END;
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

