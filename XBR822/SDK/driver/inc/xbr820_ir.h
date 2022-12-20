/**
  ******************************************************************************
  * @file    xbr820_ir.h
  * @author  software Team
  * @version V1.0.0
  * @date    24-December-2021
  * @brief   This file contains all the functions prototypes for the IR firmware
  *          library.
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
#ifndef __XBR820_IR_H__
#define __XBR820_IR_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "xbr820_interrupts.h"
#include "xbr820.h"

/* Exported constants --------------------------------------------------------*/

#define IS_IR_PERIPH(PERIPH)                                 ((PERIPH) == BRX820_IR)
#define IS_IR_CONFIG_IT(IT)                                  ((((IT) <= 0x0F) && ((IT) >= 0x00))

/* Exported types ------------------------------------------------------------*/
typedef struct {
    uint32_t ir_mode;
    uint32_t ir_code;
} IR_mc_t;

/* Exported functions --------------------------------------------------------*/
void IR_clr_int(brx820_ir_regdef *ir_clr);
int IR_read_code(IR_mc_t *irdata, brx820_ir_regdef *ircfg);

#ifdef __cplusplus
}
#endif

#endif
