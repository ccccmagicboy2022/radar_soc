/**
  ******************************************************************************
  * @file    xbr820_i2c_slave.c
  * @author  software Team
  * @version V1.0.0
  * @date    24-December-2021
  * @brief   This file provides firmware functions to manage the
  *          functionalities of the Inter-integrated circuit (I2C)
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
#include "xbr820_i2c_slave.h"
#include "xbr820_utility.h"

/** @addtogroup PHO_Periph_Driver
  * @{
  */

/** @defgroup I2C slave
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/ 
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
 * @brief  Enables or disables the specified I2C interrupts.
 * @param  i2c_unit: select the I2C peripheral.
 * @param  i2c_it: specifies the I2C interrupts sources to be enabled or disabled. 
 *          This parameter can be any combination of the following values:
 *             @arg I2C_SLAVE_RW_MASK
 *             @arg I2C_SLAVE_NACK_MASK
 *             @arg I2C_SLAVE_STOP_MASK
 *             @arg I2C_SLAVE_ADDR_MASK
 * @param  state: new state of the specified I2C interrupts.
 *          This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void I2C_slave_int_cmd(I2C_slave_t *i2c_unit, uint32_t i2c_it, en_functional_state_t state)

    assert_param(IS_I2C_SLAVE_PERIPH(i2c_unit));
    assert_param(IS_FUNCTIONAL_STATE(state));
    assert_param(IS_I2C_SLAVE_MASK_IT(i2c_it));

    if (state == DISABLE)
        i2c_unit->CR |= i2c_it;
    else
        i2c_unit->CR &= ~i2c_it;
}

/**
 * @brief  clear the specified I2C interrupt flags.
 * @param  i2c_unit: select the I2C peripheral.
 * @param  i2c_it: specifies the I2C interrupts sources to be enabled or disabled. 
 *          This parameter can be any combination of the following values:
 *             @arg I2C_SLAVE_CLR_RW
 *             @arg I2C_SLAVE_CLR_NACK
 *             @arg I2C_SLAVE_CLR_STOP
 *             @arg I2C_SLAVE_CLR_ADDR
 *             @arg I2C_SLAVE_CLR_INT
 * @retval None
 */
void I2C_slave_clear_flag(I2C_slave_t *i2c_unit, uint32_t i2c_it)
{
    assert_param(IS_I2C_SLAVE_PERIPH(i2c_unit));
    assert_param(IS_I2C_SLAVE_CLR_IT(i2c_it));

    i2c_unit->CR |= i2c_it;
}

/**
 * @brief initialize I2C peripheral
 * 
 * @param i2c_unit select the I2C peripheral.
 * @param slave_addr the slave address
 * @retval None
 */
void I2C_slave_init(I2C_slave_t *i2c_unit, uint8_t slave_addr)
{
    assert_param(IS_I2C_SLAVE_PERIPH(i2c_unit));

    i2c_unit->SLAVE_ADDR_f.SLAVE_ADDR = slave_addr << 1;
    i2c_unit->EN_SLAVE_f.EN_SLAVE = 1;
}

/**
 * @brief de-initialize I2C unit
 * @param i2c_unit select the I2C peripheral.
 * @retval None
 */
void I2C_slave_deinit(I2C_slave_t *i2c_unit)
{
    assert_param(IS_I2C_SLAVE_PERIPH(i2c_unit));

    i2c_unit->EN_SLAVE_f.EN_SLAVE = 0;
}

/**
 * @brief checks whether the specified I2C interrupt has occurred or not.
 * 
 * @param i2c_unit select the I2C peripheral.
 * @param I2C_flag specifies the interrupt source to check.
 *          This parameter can be any combination of the following values:
 *              @arg I2C_SLAVE_SR_RW_DONE
 *              @arg I2C_SLAVE_SR_NACK
 *              @arg I2C_SLAVE_SR_STOP
 *              @arg I2C_SLAVE_SR_ADDR
 *              @arg I2C_SLAVE_SR_RW
 * @return en_flag_status the new state of I2C_IT (SET or RESET).
 */
en_flag_status I2C_slave_get_int_status(I2C_slave_t *i2c_unit, uint32_t I2C_flag)
{
    en_flag_status ret = RESET;

    assert_param(IS_I2C_SLAVE_PERIPH(i2c_unit));
    assert_param(IS_I2C_SLAVE_SR_IT(I2C_flag));

    if (0ul != i2c_unit->SR & I2C_flag)
        ret = SET;

    return ret;
}

/**
 * @brief read data from i2c data register.
 * 
 * @param i2c_unit select the I2C peripheral.
 * @return uint8_t data from i2c.
 */
uint8_t I2C_slave_read_data(I2C_slave_t *i2c_unit)
{
    assert_param(IS_I2C_SLAVE_PERIPH(i2c_unit));

    return i2c_unit->RECV_DATA_f.RECV_DATA;
}

/**
 * @brief read addr from i2c data register.
 * 
 * @param i2c_unit select the I2C peripheral.
 * @return uint8_t word addr from i2c.
 */
uint8_t I2C_slave_read_word_addr(I2C_slave_t *i2c_unit)
{
    assert_param(IS_I2C_SLAVE_PERIPH(i2c_unit));

    return i2c_unit->RECV_DATA_f.RECV_ADDR;
}

/**
 * @brief write data to be sent to register.
 * 
 * @param i2c_unit select the I2C peripheral.
 * @param data data to be sent.
 */
void I2C_slave_write_data(I2C_slave_t *i2c_unit, uint8_t data)
{
    assert_param(IS_I2C_SLAVE_PERIPH(i2c_unit));

    i2c_unit->SEND_DATA_f.SEND_DATA = data;
}
/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT Phosense-tech *****END OF FILE****/
