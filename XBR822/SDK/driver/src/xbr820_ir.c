/**
  ******************************************************************************
  * @file    xbr820_ir.c
  * @author  software Team
  * @version V1.0.0
  * @date    24-December-2021
  * @brief   This file provides firmware functions to manage the
  *          functionalities of the InfraRed (IR)
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2021 PHOSENSE </center></h2>
  *
  * Licensed under Liberty SW License Agreement V1, (the "License");
  * You may not use this file except in compliance with the License.

  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "xbr820.h"
#include "xbr820_ir.h"
#include "xbr820_utility.h"
#include "xbr820_interrupts.h"

/** @addtogroup PHO_Periph_Driver
  * @{
  */

/** @defgroup IR
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
 * @brief  IR struct.
 * @note   Specifies the IR mode. This parameter can be 0~3, 0: no data; 1: income data; 2: 3: repeat data
 * @note   Specifies the IR code from remoter receiver.This parameter is include 4 byte,that is 16 bits customer code
 * @note   8 bits data code and 8 bitsdata-conversion.
 */

/**
 * @brief  IR module interface to clear the interrupt of IR.
 * @param  none.
 * @retval none.
*/
void IR_clr_int(brx820_ir_regdef *ir_clr)
{
    assert_param(IS_IR_PERIPH(ir_clr));
	
    ir_clr->IR_CMD_f.IR_INT_STA = 0;
}

/**
 * @brief  IR module interface to get out the incoming data.
 * @param  data: which is a defined structure, include ir_mode and ir_code.
 *             It is an output param.
 * @retval 0 for success. -1 for wrong input param.
 */
int IR_read_code(IR_mc_t *irdata, brx820_ir_regdef *ircfg)
{
    assert_param(IS_IR_PERIPH(ircfg));
	
    irdata->ir_mode = ((ircfg->IR_CMD_f.IR_REPEAT) <<1) | (ircfg->IR_CMD_f.IR_INT_STA);
    irdata->ir_code = ircfg->IR_READ_DATA;
    return 0;
}