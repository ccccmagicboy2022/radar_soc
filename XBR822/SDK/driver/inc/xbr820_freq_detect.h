/**
  ******************************************************************************
  * @file    xbr820_timer.h
  * @author  software Team
  * @version V1.0.0
  * @date    24-December-2021
  * @brief   This file contains all the functions prototypes for the PWM firmware
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
#ifndef __XBR820_FREQ_DETECT_H__
#define  __XBR820_FREQ_DETECT_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "xbr820_interrupts.h"

/* Exported constants --------------------------------------------------------*/

#define IS_FREQ_PERIPH(PERIPH)                                  ((PERIPH) == BRX820_FREQ_DETECT)


/* Exported types ------------------------------------------------------------*/
typedef struct{
    uint32_t    enable;
    uint32_t    int_en;
    uint32_t    interval;
}freq_detect_Cfg;

/* Exported functions --------------------------------------------------------*/
void freq_detect_init(brx820_freq_detect_regdef * freq, const freq_detect_Cfg* freq_det_init);
void freq_detect_enable(brx820_freq_detect_regdef *freq);
void freq_detect_disable(brx820_freq_detect_regdef *freq);
uint32_t freq_get_value(brx820_freq_detect_regdef *freq);
uint8_t freq_get_interrupt_status(brx820_freq_detect_regdef *freq);
void freq_clr_interrupt_status(brx820_freq_detect_regdef *freq);

#ifdef __cplusplus
}
#endif


