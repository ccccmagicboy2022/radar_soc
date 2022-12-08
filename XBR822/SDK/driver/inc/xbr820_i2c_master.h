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

typedef struct {
	__IOM uint32_t NACK              :1;
	__IOM uint32_t FINISH            :1;
	__IOM uint32_t TIME_OUT          :1;
	__IOM uint32_t ONE_BYTE_FINISH   :1;
	__IOM uint32_t 		            :28;        
} I2C_INT;

typedef struct {
	__IM uint32_t NACK             :1;
	__IM uint32_t FINISH           :1;
	__IM uint32_t TIME_OUT         :1;
	__IM uint32_t IDLE             :1;
	__IM uint32_t ONE_BYTE_FINISH  :1;
	uint32_t                       :3;
	__IM uint32_t DATA_NUM         :8;
	uint32_t                      :16;
} I2C_status_t;

typedef struct {
    __IOM uint32_t SLAVE_ADDR       :8; 
	uint32_t                       :24; 
	
    __IOM uint32_t DATA_LENTH       :8;
    uint32_t                       :24;
	
	__IOM uint32_t CMD              :4;
	__IOM uint32_t CMD_W            :1;
	uint32_t                       :27;
	
	__IOM uint32_t WAIT_TIME       :16;
	uint16_t                       :16;
	
    __IOM uint32_t CPU_CLK_STR_EN   :1;
	__IOM uint32_t CPU_LAST_ACK_EN  :1;
	uint32_t                       :30;
	
	__IOM uint32_t REG_ADDR        :16;
	uint32_t                       :16;

	__IOM uint32_t T_DATA0;
	__IOM uint32_t T_DATA1;
	__IOM uint32_t R_DATA0;
	__IOM uint32_t R_DATA1;
	
	union {
		__IM uint32_t STATUS;
		I2C_status_t STATUS_f;
	};
	
	I2C_INT INT_EN;
	
	I2C_INT INT_CLEAR;
	
	__IOM uint32_t CLK_DIV        :16;
	uint32_t 	                  :16;
	
	__IOM uint32_t CLK_EN          :1;
	uint32_t                      :31;	
} IIC_MASTER_REG;

#define I2C_master                      ((IIC_MASTER_REG *)XBR820_I2CM_BASE)

static inline uint32_t get_data_num(void)
{
	return I2C_master->STATUS_f.DATA_NUM;
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
	I2C_master->INT_CLEAR.ONE_BYTE_FINISH = 1;
}

static inline void i2c_clear_stop(void)
{
	I2C_master->INT_CLEAR.FINISH = 1;
}

#ifdef __cplusplus
}
#endif

#endif


