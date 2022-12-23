/**
  ******************************************************************************
  * @file    xbr820_i2c_slave.h
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
#ifndef __XBR820_I2C_SLAVE_H__
#define __XBR820_I2C_SLAVE_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "pho_common.h"

/** @addtogroup PHO_Periph_Driver
  * @{
  */

/** @addtogroup I2C slave
  * @{
  */

/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/

#define IS_I2C_SLAVE_PERIPH(PERIPH)                          ((PERIPH) == BRX820_I2C_SLAVE)
#define IS_I2C_SLAVE_CLR_IT(IT)                              ((((IT) & 0xFFFFFFE0) == 0) && ((IT) != 0x00))
#define IS_I2C_SLAVE_MASK_IT(IT)                             ((((IT) & 0xFFFFF0FF) == 0) && ((IT) != 0x00))
#define IS_I2C_SLAVE_SR_IT(IT)                               ((((IT) & 0xFFFFFFE0) == 0) && ((IT) != 0x00))

/* Exported macro ------------------------------------------------------------*/
#define I2C_SLAVE_SR_RW_DONE                                          (1ul << 0)
#define I2C_SLAVE_SR_NACK                                             (1ul << 1)
#define I2C_SLAVE_SR_STOP                                             (1ul << 2)
#define I2C_SLAVE_SR_ADDR                                             (1ul << 3)
#define I2C_SLAVE_SR_RW                                               (1ul << 4)

#define I2C_SLAVE_CLR_RW                                              (1ul << 0)
#define I2C_SLAVE_CLR_NACK                                            (1ul << 1)
#define I2C_SLAVE_CLR_STOP                                            (1ul << 2)
#define I2C_SLAVE_CLR_ADDR                                            (1ul << 3)
#define I2C_SLAVE_CLR_INT                                             (1ul << 4)

#define I2C_SLAVE_RW_MASK                                             (1ul << 8)
#define I2C_SLAVE_NACK_MASK                                           (1ul << 9)
#define I2C_SLAVE_STOP_MASK                                           (1ul << 10)
#define I2C_SLAVE_ADDR_MASK                                           (1ul << 11)

/* Exported functions --------------------------------------------------------*/
typedef void (*fun_i2c_slave)(void);
void i2c_slave_irq_cfg(fun_i2c_slave _handler, uint8_t _priority, uint8_t _int_num);

void I2C_slave_int_cmd(brx820_i2c_slave_regdef *i2c_unit, uint32_t i2c_it, em_functional_state_t state);
void I2C_slave_clear_flag(brx820_i2c_slave_regdef *i2c_unit, uint32_t i2c_it);
void I2C_slave_init(brx820_i2c_slave_regdef *i2c_unit, uint8_t slave_addr);
void I2C_slave_deinit(brx820_i2c_slave_regdef *i2c_unit);
em_flag_status_t I2C_slave_get_int_status(brx820_i2c_slave_regdef *i2c_unit, uint32_t I2C_flag);
uint8_t I2C_slave_read_data(brx820_i2c_slave_regdef *i2c_unit);
uint8_t I2C_slave_read_word_addr(brx820_i2c_slave_regdef *i2c_unit);
void I2C_slave_write_data(brx820_i2c_slave_regdef *i2c_unit, uint8_t data);

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

