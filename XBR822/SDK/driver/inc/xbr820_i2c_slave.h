#ifndef __DRV_I2C_SL_H__
#define __DRV_I2C_SL_H__

#include "typdef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ================================================================================ */
/* ================                I2C Slave declaration                ================ */
/* ================================================================================ */

#define I2C_SL_ENABLE     1
#define I2C_SL_DISABLE     0

#define I2C_SL_INTR_RW     1<<0
#define I2C_SL_INTR_NACK     1<<1
#define I2C_SL_INTR_STOP     1<<2
#define I2C_SL_INTR_ADDR     1<<3
#define I2C_SL_INTR_RWO     1<<4

#define I2C_SL_REL_RW     1<<0
#define I2C_SL_REL_NACK     1<<1
#define I2C_SL_REL_STOP     1<<2
#define I2C_SL_REL_ADDR     1<<3
#define I2C_SL_REL_RWO     1<<4

#define I2C_SL_MSK_RW     1<<8
#define I2C_SL_MSK_NACK     1<<9
#define I2C_SL_MSK_STOP     1<<10
#define I2C_SL_MSK_ADDR     1<<11
#define I2C_SL_MSK_RWO     1<<12

/**
  * @brief  I2C slave initialize.
  *
  * @note   To assign an address for this I2C slave deive and enable it.
  *
  * @param  sl_addr: I2C slave device's address.
  * @retval none.
  */
void I2C_SL_Init(uint8_t sl_addr);

/**
  * @brief  I2C slave de-initialize.
  *
  * @note   Disable this I2C slave device and set its address to zero.
  *
  * @param  none.
  * @retval none.
  */
void I2C_SL_DeInit(void);

/**
  * @brief  I2C slave device send data to the interface, eg. to the I2C master.
  * @param  data: which will be sent to the interface.
  *             It is an input param.
  * @retval none.
  */
void I2C_SL_SendData(uint8_t data);

/**
  * @brief  I2C slave device receive data from the interface, eg. from the I2C master.
  * @param  data: which is received from the interface.
  *             It is an output param.
  * @retval none.
  */
/**
  * @brief  I2C slave device receive data from the interface, eg. from the I2C master.
  * @param  data: which is received from the interface.
  *             It is an output param.
  * @retval none.
  */
uint8_t I2C_SL_RecvSubAddr(void) ;

/**
  * @brief  I2C slave device receive data from the interface, eg. from the I2C master.
  * @param  data: which is received from the interface.
  *             It is an output param.
  * @retval none.
  */
uint8_t I2C_SL_RecvData( void) ;

uint8_t I2C_SL_GetIntr(void) ;

void I2C_SL_ClrIntr(void);

uint32_t I2C_SL_RecvOrSend(void) ;

void I2C_SL_Clr_RW(void);
void I2C_SL_Clr_addr(void);
#ifdef __cplusplus
}
#endif


#endif // __DRV_I2C_SL_H__
