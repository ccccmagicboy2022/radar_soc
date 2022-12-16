/**
 * @file xbr820_ir.c
 * @author Phosense Software Team
 * @brief ir driver C source file
 * @version 1.0.0.0
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022, Phosense-tech, All rights reserved.
 * 
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "xbr820_ir.h"

/** @{*/

/**
 * @brief  IR module interface to clear the interrupt of IR.
 * @param  none.
 * @retval none.
*/
void ir_clr_int(void)
{
    brx820_ir_regdef *ir_reg;
    ir_reg = (brx820_ir_regdef*)(BRX820_IR);

    //not find
}

/**
 * @brief  IR module interface to get out the incoming data.
 * @param  data: which is a defined structure, include ir_mode and ir_code.
 *             It is an output param.
 * @retval en_result_t the new result of ir_read_code.
 */
int ir_read_code(IR_mc_t *irdata)
{
    if (irdata == NULL) {
        return -1;
    }
    brx820_ir_regdef* ir_reg;

    ir_reg = (brx820_ir_regdef*)(BRX820_IR);
    
    irdata->ir_mode = ((ir_reg->IR_CMD_f.IR_REPEAT) << 1) | (ir_reg->IR_CMD_f.IR_INT_STA);
    irdata->ir_code = ir_reg->IR_READ_DATA;
    return 0;
}

/**  @} ir_group*/
