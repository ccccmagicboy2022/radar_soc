/**
  ******************************************************************************
  * @file    xbr820_i2c_master.c
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
#include "xbr820_i2c_master.h"
#include "xbr820_utility.h"

/** @addtogroup PHO_Periph_Driver
  * @{
  */

/** @defgroup I2C master
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
 *             @arg I2C_INT_NACK
 *             @arg I2C_INT_STOP
 *             @arg I2C_INT_TIMEOUT
 *             @arg I2C_INT_RW_DONE
 * @param  state: new state of the specified I2C interrupts.
 *          This parameter can be: ENABLE or DISABLE.
 * @retval None
 */
void I2C_int_cmd(I2C_master_t *i2c_unit, uint32_t i2c_it, en_functional_state_t state)

    assert_param(IS_I2C_MASTER_PERIPH(i2c_unit));
    assert_param(IS_FUNCTIONAL_STATE(state));
    assert_param(IS_I2C_CONFIG_IT(i2c_it));

    if (state != DISABLE)
        i2c_unit->INT_EN |= i2c_it;
    else
        i2c_unit->INT_EN &= ~i2c_it;
}

/**
 * @brief  clear the specified I2C interrupt flags.
 * @param  i2c_unit: select the I2C peripheral.
 * @param  i2c_it: specifies the I2C interrupts sources to be enabled or disabled. 
 *          This parameter can be any combination of the following values:
 *             @arg I2C_INT_NACK
 *             @arg I2C_INT_STOP
 *             @arg I2C_INT_TIMEOUT
 *             @arg I2C_INT_RW_DONE
 * @retval None
 */
void I2C_clear_flag(I2C_master_t *i2c_unit, uint32_t i2c_it)
{
    assert_param(IS_I2C_MASTER_PERIPH(i2c_unit));
    assert_param(IS_I2C_CONFIG_IT(i2c_it));

    i2c_unit->INT_CLR |= i2c_it;
}

/**
 * @brief initialize I2C peripheral
 * 
 * @param i2c_unit select the I2C peripheral.
 * @param clk I2C clock speed
 * @retval None
 */
void I2C_init(I2C_master_t *i2c_unit, uint32_t clk)
{
    assert_param(IS_I2C_MASTER_PERIPH(i2c_unit));
    assert_param(IS_I2C_CLOCK_SPEED(clk));

    I2C_clear_flag(i2c_unit, I2C_INT_NACK | I2C_INT_STOP | I2C_INT_TIMEOUT | I2C_INT_RW_DONE);
    i2c_unit->CLK_DIV = (uint32_t)SYSTEM_CLOCK / clk / 8;
    i2c_unit->CLK_EN = 1;
}

/**
 * @brief de-initialize I2C unit
 * @param i2c_unit select the I2C peripheral.
 * @retval None
 */
void I2C_deinit(I2C_master_t *i2c_unit)
{
    assert_param(IS_I2C_MASTER_PERIPH(i2c_unit));

    i2c_unit->CLK_EN = 0;
}

/**
 * @brief read data register, one byte per time
 * 
 * @param i2c_unit select the I2C peripheral.
 * @param data point to the data buffer.
 * @param pos the position from which data is read.
 * @param flag the data register from which data is read.
 */
void I2C_read_data(I2C_master_t *i2c_unit, uint8_t *data, uint8_t pos, uint8_t flag)
{
    if (!flag)
        data[0] = ((i2c_unit->IICM_2_DATA0) >> (pos * 8)) & 0xff;
    else
        data[0] = ((i2c_unit->IICM_2_DATA1) >> (pos * 8)) & 0xff;
}

/**
 * @brief start i2c read operation
 * 
 * @param i2c_unit select the I2C peripheral.
 * @param reg_addr register address.
 * @param word_addr denote if the address is byte address or word address.
 *          This parameter can be any combination of the following values:
 *              0
 *              1
 */
void I2C_start_read(I2C_master_t *i2c_unit, uint16_t reg_addr, uint8_t word_addr)
{
    assert_param(IS_I2C_MASTER_PERIPH(i2c_unit));

    i2c_unit->SLAVE_ADDR_f.SLAVE_ADDR = reg_addr;

    if (word_addr)
        i2c_unit->CMD_CR_f.CPU_CMD = 0xF;
    else
        i2c_unit->CMD_CR_f.CPU_CMD = 7;

    i2c_unit->CMD_CR_f.CPU_CMD_W = 1;
}

/**
 * @brief start i2c write operation
 * 
 * @param i2c_unit select the I2C peripheral.
 * @retval None
 */
void I2C_start_write(I2C_master_t *i2c_unit)
{
    assert_param(IS_I2C_MASTER_PERIPH(i2c_unit));

    i2c_unit->CMD_CR_f.CPU_CMD = 1;
    i2c_unit->CMD_CR_f.CPU_CMD_W = 1;
}

/**
 * @brief config i2c slave address
 * 
 * @param i2c_unit select the I2C peripheral.
 * @param slave_addr i2c slave address
 */
void I2C_config_slave_addr(I2C_master_t *i2c_unit, uint8_t slave_addr)
{
    assert_param(IS_I2C_MASTER_PERIPH(i2c_unit));

    i2c_unit->SLAVE_ADDR_f.SLAVE_ADDR = slave_addr << 1;
}

/**
 * @brief set i2c transfer data number.
 * 
 * @param i2c_unit select the I2C peripheral.
 * @param len transfer data number.
 */
void I2C_set_rw_num(I2C_master_t *i2c_unit, uint8_t len)
{
    assert_param(IS_I2C_MASTER_PERIPH(i2c_unit));

    i2c_unit->NWORD_f.NWORD = len - 1;
}

/**
 * @brief checks whether the specified I2C interrupt has occurred or not.
 * 
 * @param i2c_unit select the I2C peripheral.
 * @param I2C_flag specifies the interrupt source to check.
 *          This parameter can be any combination of the following values:
 *              @arg I2C_SR_NACK
 *              @arg I2C_SR_STOP
 *              @arg I2C_SR_TIMEOUT
 *              @arg I2C_SR_IDLE
 *              @arg I2C_SR_RW_DONE
 * @return en_flag_status the new state of I2C_IT (SET or RESET).
 */
en_flag_status I2C_get_int_status(I2C_master_t *i2c_unit, uint32_t I2C_flag)
{
    en_flag_status ret = RESET;

    assert_param(IS_I2C_MASTER_PERIPH(i2c_unit));
    assert_param(IS_I2C_STATUS_BIT(I2C_flag));

    if (0ul != i2c_unit->STATUS & I2C_flag)
        ret = SET;

    return ret;
}

/**
 * @brief get the data num transfered.
 * 
 * @param i2c_unit select the I2C peripheral.
 * @return uint8_t data transfer number.
 */
uint8_t I2C_get_trans_number(I2C_master_t *i2c_unit)
{
    assert_param(IS_I2C_MASTER_PERIPH(i2c_unit));

    return i2c_unit->STATUS_f.DATA_NUM;
}
/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT Phosense-tech *****END OF FILE****/