#ifndef _IIC_MASTER_H_
#define _IIC_MASTER_H_

#include "xbr820.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NACK_INT_MASK                    (1ul << 0)
#define FINISH_INT_MASK                  (1ul << 1)
#define TIMEOUT_INT_MASK                 (1ul << 2)
#define RW_DONE_INT_MASK                 (1ul << 4)

static inline uint32_t get_data_num(void)
{
	return BRX820_I2C_master->STATUS_f.DATA_NUM;
}
void i2c_init(uint32_t clk);
void i2c_enable_int(void);
void i2c_clear_int(void);
void i2c_start(void);
void i2c_config_addr(uint8_t slave_addr, uint8_t len);
void i2c_write_data(uint8_t *data, uint8_t len, uint8_t flag);
void i2c_read_one_byte(uint8_t *data, uint8_t pos, uint8_t flag);
void i2c_read_setup(uint16_t reg_addr, uint8_t word_addr);
void i2c_deinit(void);
uint8_t is_i2c_busy(void);
void i2c_transmit(uint8_t slave_addr, uint8_t *data, uint8_t len, uint32_t timeout);
void i2c_recv(uint8_t slave_addr, uint16_t reg_addr, uint8_t word_addr, uint8_t *data, uint8_t len, uint32_t timeout);
uint32_t i2c_master_get_status();


static inline void i2c_clear_rw_done(void)
{
#if 0
	int ret;

	if (I2C_master->STATUS & RW_DONE_INT_MASK) {
		I2C_master->INT_CLEAR.ONE_BYTE_FINISH = 1;
		ret = 0;
	} else if (I2C_master->STATUS & FINISH_INT_MASK) {
		I2C_master->INT_CLEAR.FINISH = 1;
		ret = 1;
	}

	return ret;
#endif
	BRX820_I2C_master->INT_CLEAR.ONE_BYTE_FINISH = 1;
}

static inline void i2c_clear_stop(void)
{
	BRX820_I2C_master->INT_CLEAR.FINISH = 1;
}

#ifdef __cplusplus
}
#endif

#endif


