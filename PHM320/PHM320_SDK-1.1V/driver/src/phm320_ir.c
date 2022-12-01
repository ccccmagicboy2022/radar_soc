/**
 * @file phm320_ir.c
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
#include "phm320_ir.h"

/** @{*/

/**
 * @brief  IR module interface to clear the interrupt of IR.
 * @param  none.
 * @retval none.
*/
void ir_clr_int(void)
{
    IR_reg_t *ir_reg;
    ir_reg = (IR_reg_t*)(PHM320_IR_BASE);

    ir_reg->rf_int_clr = 1;
    ir_reg->rf_cmp_clr = 1;
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
    IR_reg_t* ir_reg;

    ir_reg = (IR_reg_t*)(PHM320_IR_BASE);
    irdata->ir_mode = ((ir_reg->ir_repeat) << 1) | (ir_reg->ir_int);
    irdata->ir_code = ir_reg->ir_data;
    return 0;
}

/**  @} ir_group*/
