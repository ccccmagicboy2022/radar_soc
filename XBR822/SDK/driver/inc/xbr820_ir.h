/**
 * @file xbr820_ir.h
 * @author Phosense Software Team
 * @brief ir driver head file
 * @version 1.0.0.0
 * @date 2022-03-23
 *
 * @copyright Copyright (c) 2022, Phosense-tech, All rights reserved.
 *
 */

#ifndef __XBR820_IR_H__
#define __XBR820_IR_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "pho_common.h"


/**
 * @defgroup ir_group IR
 * @{
 */

/* Exported types ------------------------------------------------------------*/
typedef struct {
    uint32_t ir_mode;     /*!< Specifies the IR mode. This parameter can be 0~3
                                            0: no data; 1: income data; 2: 3: repeat data */
    uint32_t ir_code;    /*!< Specifies the IR code from remoter receiver.
                            This parameter is include 4 byte,
                            that is 16 bits customer code, 8 bits data code and 8 bitsdata-conversion */
} IR_mc_t;

/* Exported functions --------------------------------------------------------*/
int ir_read_code(IR_mc_t* irdata);
void ir_clr_int(void);

/**  @} ir_group*/

#endif
