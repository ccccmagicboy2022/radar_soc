/**
 * @file phm320_adc.c
 * @author Phosense Software Team
 * @brief mtpc C head file
 * @version 1.0.0.0
 * @date 2022-03-21
 * 
 * @copyright Copyright (c) 2022, Phosense-tech, All rights reserved.
 * 
 */

#ifndef __PHM320_MTPC_H___
#define __PHM320_MTPC_H___

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "pho_common.h"

/**
 * @defgroup mtpc_group MTP Controller(MTPC)
 * @{
 */

/**
 * @brief mtpc mode enumeration
 * 
 */
typedef enum em_mtpc_mode
{
    AHB_READ         = 0u,
    AHB_READX        = 1u,
    CHIP_EARSE_MB    = 2u,
    CHIP_EARSE_XB    = 3u,
    SECTOR_EARSE_MB  = 4u,
    SECTOR_ERASE_XB  = 5u,
    PROGRAM_MB       = 6u,
    PROGRAM_XB       = 7u,
    PROGRAM_MB_TEST  = 8u,
    PROGRAM_XB_TEST  = 9u,
    PROGRAM_REF_MB   = 10u,
    PROGRAM_REF_XB   = 11u,
    POWER_ON         = 12u,
    POWER_DOWN       = 13u,
} em_mtpc_mode_t;

/**
 * @brief mtpc run structure definition
 * 
 */
typedef struct str_mtpc_run
{
    em_mtpc_mode_t        mode;
    uint32_t              address;
    uint32_t              data;
} str_mtpc_run_t;

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
em_result_t mtpc_run(const str_mtpc_run_t *mtpc_config);

/**  @} mtpc_group*/

#endif