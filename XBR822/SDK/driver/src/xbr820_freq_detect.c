/**
  ******************************************************************************
  * @file    xbr820_freq_detect.c
  * @author  software Team
  * @version V1.0.0
  * @date    24-December-2021
  * @brief   This file provides firmware functions to manage the
  *          functionalities of the pwm
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
#include "xbr820_utility.h"
#include "xbr820_interrupts.h"
#include "xbr820_freq_detect.h"

/** @addtogroup PHO_Periph_Driver
  * @{
  */

/** @defgroup FREQ_DETECT
  * @{
  */
void freq_detect_init(brx820_freq_detect_regdef * freq, const freq_detect_Cfg* freq_det_init)
{
    assert_param(IS_FREQ_PERIPH(freq));

    freq->FREQ_DETECT_CTRL_f.FREQ_DET_EN = freq_det_init->enable;
    freq->FREQ_DETECT_CTRL_f.FREQ_DET_INT_EN = freq_det_init->int_en;
    freq->FREQ_DETECT_CFG_f.FREQ_DET_INTERVAL = freq_det_init->interval;
}


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/**
  * @brief  freq_detect_enable. The timer should be set a initial value
  * @param  freq_detect: freq and counter.
  * @retval none.
  */
void freq_detect_enable(brx820_freq_detect_regdef *freq)
{
    assert_param(IS_FREQ_PERIPH(freq));

    freq->FREQ_DETECT_CTRL_f.FREQ_DET_EN = 1;
    freq->FREQ_DETECT_CTRL_f.FREQ_DET_INT_EN = 1;
}

/**
  * @brief  freq_detect_disable.
  * @param  freq
  * @retval none.
  */
void freq_detect_disable(brx820_freq_detect_regdef *freq)
{
    assert_param(IS_FREQ_PERIPH(freq));

    freq->FREQ_DETECT_CTRL_f.FREQ_DET_EN = 0;
    freq->FREQ_DETECT_CTRL_f.FREQ_DET_INT_EN = 0;
}

/**
  * @brief  freq_get_value.
  * @param  freq: freq and freq_value.
  * @retval none.
  */
uint32_t freq_get_value(brx820_freq_detect_regdef *freq)
{
    assert_param(IS_FREQ_PERIPH(freq));

    return freq->FREQ_DETECT_VALUE_f.FREQ_DET_VAL;
}


/**
  * @brief  freq_get_interrupt_status.
  *         Reset means counting from the init value again.
  * @param  freq and freq_status.
  * @retval none.
  */
uint8_t freq_get_interrupt_status(brx820_freq_detect_regdef *freq)
{
    assert_param(IS_FREQ_PERIPH(freq));

    return freq->FREQ_DETECT_CTRL_f.FREQ_DET_STATUS;
}

void freq_clr_interrupt_status(brx820_freq_detect_regdef *freq)
{
    assert_param(IS_FREQ_PERIPH(freq));

    freq->FREQ_DETECT_CTRL_f.FREQ_DET_STATUS = 1;

}



