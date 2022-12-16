/**
 * @file phm320_pmu.c
 * @author Phosense Software Team
 * @brief mtpc C head file
 * @version 1.0.0.0
 * @date 2022-03-22
 *
 * @copyright Copyright (c) 2022, Phosense-tech, All rights reserved.
 *
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "phm320_pmu.h"

/** @{*/

/**
 * @brief choose power work way
 *
 * @param [in] powered_way pointer to ADC initialization structure.
 *                         see @ref em_powered_way_t for details.
 */
void ldo_powered_way(em_powered_way_t powered_way)
{
    PHM320_TOP->ANALOG_A_BITS.RF1_EN = 1;
    PHM320_TOP->ANALOG_A_BITS.RF2_EN = 1;
    PHM320_TOP->ANALOG_A_BITS.RF4_EN = 1;
    PHM320_TOP->ANALOG_B_BITS.RF_EN_SEL = powered_way;
    PHM320_TOP->ADC_CTL_BITS.ADC_DATA_CLRN = 1;

    if (PLUS == powered_way) {
        PHM320_TOP->ADC_CTL &= (~(0xff << 16));
        PHM320_TOP->ADC_CTL |= ((16 * PLUS_HIGH_LEVEL_DURATION) << 16);
        PHM320_TOP->ANALOG_B_BITS.PGA_DC_TRIM = 0b010100;
    } else {
        PHM320_TOP->ANALOG_B_BITS.PGA_DC_TRIM = 0b010011;
    }
    PHM320_TOP->ANALOG_B_BITS.PGA_EN = 1;
    PHM320_TOP->ANALOG_B_BITS.PGA_BYPASS = 0;
    PHM320_TOP->ANALOG_B_BITS.ADC_POW_DONE = 1;
    PHM320_TOP->ADC_CTL_BITS.PGA_GAIN = 2;
    PHM320_TOP->ADC_CTL_BITS.ADC_VREF_SEL = 0b01;
}

/**  @} pmu_group*/
