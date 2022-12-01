/**
 * @file phm320_mtpc.c
 * @author Phosense Software Team
 * @brief mtpc C source file
 * @version 1.0.0.0
 * @date 2022-03-21
 * 
 * @copyright Copyright (c) 2022, Phosense-tech, All rights reserved.
 * 
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "phm320_mtpc.h"

/** @{*/

/**
 * @brief run mtp controller
 * 
 * @warning this fuction should be put in ram.
 * 
 * @param [in] mtpc_config pointer to ADC initialization structure.
 *                         see @ref str_mtpc_run_t for details.
 * @return em_result_t
 * - OK no error occurred.  
 */
em_result_t mtpc_run(const str_mtpc_run_t *mtpc_config)
{
    if (mtpc_config->mode > 3 \
        && mtpc_config->mode < 10) {
        PHM320_MTPC->ADDR = mtpc_config->address;
        PHM320_MTPC->DATA = mtpc_config->data;
    }
    PHM320_MTPC->MTPC_CTL_BITS.MODE = mtpc_config->mode;
    while (!PHM320_MTPC->FINISH) {}
    return Ok;
}

/**  @} mtpc_group*/