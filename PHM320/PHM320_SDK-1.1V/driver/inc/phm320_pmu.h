/**
 * @file phm320_pmu.h
 * @author Phosense Software Team
 * @brief mtpc C head file
 * @version 1.0.0.0
 * @date 2022-03-22
 * 
 * @copyright Copyright (c) 2022, Phosense-tech, All rights reserved.
 * 
 */

#ifndef __PHM320_PMU_H___
#define __PHM320_PMU_H___

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "pho_common.h"

/**
 * @defgroup pmu_group Power Management Unit(PMU)
 * @{
 */

/** define power time, max is 16*/
#define PLUS_HIGH_LEVEL_DURATION   10  // us

/**
 * @brief power work way enumeration
 * 
 */
typedef enum em_powered_way
{
    PLUS    = 0,
    ALWAYS  = 1,
}em_powered_way_t;

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
void ldo_powered_way(em_powered_way_t powered_way);

/**  @} pmu_group*/

#endif
