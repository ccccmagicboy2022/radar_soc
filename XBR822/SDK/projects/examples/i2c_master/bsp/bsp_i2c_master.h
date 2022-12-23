#ifndef __BSP_I2C_MASTER_H__
#define __BSP_I2C_MASTER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "stdint.h"
#include "xbr820.h"
#include "xbr820_i2c_master.h"

typedef struct
{
    uint8_t slave_addr;
    uint32_t i2c_speed;
}i2c_master_Cfg_t;

void i2c_master_init(i2c_master_Cfg_t* i2c_mast);
int i2c_master_read_reg(uint8_t reg_addr, uint8_t* data);
int i2c_master_write_reg(uint8_t reg_addr, uint8_t data);
void i2c_master_irqhandler(void);

#ifdef __cplusplus
}
#endif


#endif
