#ifndef __DRV_I2C_SL_H__
#define __DRV_I2C_SL_H__

#include "typdef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ================================================================================ */
/* ================                I2C Slave declaration                ================ */
/* ================================================================================ */

typedef volatile union{
	uint32_t status;
	struct{
		uint32_t slave_rw    		:1;
		uint32_t slave_nackb    	:1;
		uint32_t slave_stopb    	:1;
		uint32_t slave_addrb    	:1;
		uint32_t slave_rw_o    	:1;
		uint32_t          :27;
	}Bits;
}I2C_SL_Intr;

typedef volatile struct {
    __IOM   uint32_t    slavedev        :8;     //device id[7:1]; what about bit0
    __IM    uint32_t    :24;
    
    __IOM   uint32_t    en_slaveb   :1;     //iic slave enable signal
    __IM    uint32_t    :31;
    
    __IM   uint32_t    slaveb_data        :8;     //slave data from iic slave interface
    __IM   uint32_t    slaveb_addr        :8;     //slave addr from iic slave interface
    __IM    uint32_t    :16;
    
    __IOM   uint32_t    slaveb_data_2_iic   :8;     //data to iic slave interface
    __IM    uint32_t    :24;

    __IM   I2C_SL_Intr    slave_int;     //iic slave rw(write/read data done)

    __IOM   uint32_t    rel_slb_rw        :1;     //release iic slave rw
    __IOM   uint32_t    rel_slb_nack        :1;     //release iic slave nak
    __IOM   uint32_t    rel_slb_stop        :1;     //release iic slave stop
    __IOM   uint32_t    rel_slb_addr        :1;     //release iic slave addr
    __IOM   uint32_t    rel_slb_int        :1;     //release iic slave int
    __IM    uint32_t    :3;  
    __IOM   uint32_t    msk_slb_rw        :1;     //mask iic slave rw
    __IOM   uint32_t    msk_slb_nack        :1;     //mask iic slave nak
    __IOM   uint32_t    msk_slb_stop        :1;     //mask iic slave stop
    __IOM   uint32_t    msk_slb_addr        :1;     //mask iic slave addr
    __IM    uint32_t    :20;    
}I2C_SReg_t;

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