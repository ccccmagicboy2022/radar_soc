#ifndef __BSP_I2C_SLAVE_H__
#define __BSP_I2C_SLAVE_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "stdint.h"
#include "xbr820.h"
#include "xbr820_i2c_slave.h"

typedef struct
{
    uint8_t slave_addr;
}i2c_slave_Cfg_t;

void i2c_slave_init_bsp(i2c_slave_Cfg_t* i2c_slav);
void i2c_slave_irqhandler(void);
void i2c_slave_prepare_write_data(uint8_t data);

void i2c_slave_rev_reg(uint8_t* reg, uint8_t* dat);


#ifdef __cplusplus
}
#endif


#endif
