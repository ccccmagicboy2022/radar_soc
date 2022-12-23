/**
  ******************************************************************************
  * @file    xbr820_i2c_master.h
  * @author  software Team
  * @version V1.0.0
  * @date    24-December-2021
  * @brief   This file contains all the functions prototypes for the I2C firmware
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
#ifndef __XBR820_I2C_MASTER_H__
#define __XBR820_I2C_MASTER_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "pho_common.h"
#include "xbr820_interrupts.h"

/** @addtogroup PHO_Periph_Driver
  * @{
  */

/** @addtogroup I2C master
  * @{
  */

/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/

#define IS_I2C_MASTER_PERIPH(PERIPH)                         ((PERIPH) == BRX820_I2C_MASTER)
#define IS_I2C_CLOCK_SPEED(SPEED)                            (((SPEED) >= 0x1) && ((SPEED) <= 400000))
#define IS_I2C_CONFIG_IT(IT)                                 ((((IT) & 0xFFFFFFF0) == 0) && ((IT) != 0x00))
#define IS_I2C_STATUS_BIT(IT)                                 ((((IT) & 0xFFFFFFE0) == 0) && ((IT) != 0x00))

/* Exported macro ------------------------------------------------------------*/
#define I2C_INT_NACK                                                  (1ul << 0)
#define I2C_INT_STOP                                                  (1ul << 1)
#define I2C_INT_TIMEOUT                                               (1ul << 2)
#define I2C_INT_RW_DONE                                               (1ul << 3)

#define I2C_SR_NACK                                                   (1ul << 0)
#define I2C_SR_STOP                                                   (1ul << 1)
#define I2C_SR_TIMEOUT                                                (1ul << 2)
#define I2C_SR_IDLE                                                   (1ul << 3)
#define I2C_SR_RW_DONE                                                (1ul << 4)

/* Exported functions --------------------------------------------------------*/
typedef void (*fun_i2c_master)(void);
void i2c_master_irq_cfg(fun_i2c_master _handler, uint8_t _priority, uint8_t _int_num);

void I2C_int_cmd(brx820_i2c_master_regdef *i2c_unit, uint32_t i2c_it, em_functional_state_t state);
void I2C_clear_flag(brx820_i2c_master_regdef *i2c_unit, uint32_t i2c_it);
void I2C_init(brx820_i2c_master_regdef *i2c_unit, uint32_t clk);
void I2C_deinit(brx820_i2c_master_regdef *i2c_unit);
void I2C_read_data(brx820_i2c_master_regdef *i2c_unit, uint8_t *data, uint8_t pos, uint8_t flag);
void I2C_start_read(brx820_i2c_master_regdef *i2c_unit, uint16_t reg_addr, uint8_t word_addr);
void I2C_start_write(brx820_i2c_master_regdef *i2c_unit);
void I2C_config_slave_addr(brx820_i2c_master_regdef *i2c_unit, uint8_t slave_addr);
void I2C_set_rw_num(brx820_i2c_master_regdef *i2c_unit, uint8_t len);
em_flag_status_t I2C_get_int_status(brx820_i2c_master_regdef *i2c_unit, uint32_t I2C_flag);
uint8_t I2C_get_trans_number(brx820_i2c_master_regdef *i2c_unit);
void I2C_master_set_transmit_buffer(brx820_i2c_master_regdef *i2c_unit, uint8_t slot, uint8_t val);

#ifdef __cplusplus
}
#endif

#endif
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT Phosense-tech *****END OF FILE****/
