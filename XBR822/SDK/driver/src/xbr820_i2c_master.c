#include "xbr820.h"
#include "xbr820_i2c_master.h"

#define BUFFER_LEN                      (8U)

typedef union {
	uint32_t val;
	uint8_t ch[4];
} uint32_char_t;

void i2c_enable_int(void)
{
	BRX820_I2C_master->INT_EN.ONE_BYTE_FINISH = 1;
	BRX820_I2C_master->INT_EN.FINISH = 1;
}

void i2c_init(uint32_t clk)
{
	BRX820_I2C_master->CLK_DIV = (uint32_t)SYSTEM_CLOCK / clk / 8;
    BRX820_I2C_master->CLK_EN = 1;
	BRX820_I2C_master->INT_CLEAR.FINISH = 1;
	BRX820_I2C_master->INT_CLEAR.ONE_BYTE_FINISH = 1;
	BRX820_I2C_master->INT_CLEAR.NACK = 1;
	BRX820_I2C_master->INT_CLEAR.TIME_OUT = 1;
}

void i2c_deinit(void)
{
    BRX820_I2C_master->CLK_EN = 0;
}

void i2c_read_one_byte(uint8_t *data, uint8_t pos, uint8_t flag)
{
	if (!flag)
		data[0] = ((BRX820_I2C_master->R_DATA0) >> (pos * 8)) & 0xff;
	else
		data[0] = ((BRX820_I2C_master->R_DATA1) >> (pos * 8)) & 0xff;
}

void i2c_read_data(uint8_t *data, uint8_t len)
{
	int i;

	for (i = 0; i < len; i++) {

		while (BRX820_I2C_master->STATUS_f.ONE_BYTE_FINISH == 0);
		BRX820_I2C_master->INT_CLEAR.ONE_BYTE_FINISH = 1;
		if (i <= 3)
			i2c_read_one_byte(&data[i], i, 0);
		else
			i2c_read_one_byte(&data[i], i - 4, 1);
	}
}

void i2c_read_setup(uint16_t reg_addr, uint8_t word_addr)
{
	BRX820_I2C_master->REG_ADDR = reg_addr;

	if (word_addr)
		BRX820_I2C_master->CMD = 0xF;
	else
		BRX820_I2C_master->CMD = 7;

	BRX820_I2C_master->CMD_W = 1;
}

void i2c_recv(uint8_t slave_addr, uint16_t reg_addr, uint8_t word_addr, uint8_t *data, uint8_t len, uint32_t timeout)
{
	int i, times, rem;

	if (NULL == data)
		return;

	times = len / 8;
	rem = len % 8;

	BRX820_I2C_master->SLAVE_ADDR = slave_addr << 1;
	BRX820_I2C_master->DATA_LENTH = len - 1;
	BRX820_I2C_master->REG_ADDR = reg_addr;

	if (word_addr)
		BRX820_I2C_master->CMD = 0xF;
	else
		BRX820_I2C_master->CMD = 7;

	BRX820_I2C_master->CMD_W = 1;

	while (BRX820_I2C_master->STATUS_f.ONE_BYTE_FINISH == 0);
	BRX820_I2C_master->INT_CLEAR.ONE_BYTE_FINISH = 1;

	for (i = 0; i < times; i++)
		i2c_read_data(data, 8);
	i2c_read_data(&data[times * 8], rem);

	while (BRX820_I2C_master->STATUS_f.FINISH == 0);
	BRX820_I2C_master->INT_CLEAR.FINISH=1;

	return;
}

void i2c_write_data(uint8_t *data, uint8_t len, uint8_t flag)
{
	int i;
	uint32_t tmp = 0;

	for (i = 0; i < len; i++)
		tmp |= data[i] << (8 * i);

	if (flag)
    	BRX820_I2C_master->T_DATA1 = tmp;
	else
		BRX820_I2C_master->T_DATA0 = tmp;
}

void i2c_start(void)
{
    BRX820_I2C_master->CMD = 1;
	BRX820_I2C_master->CMD_W = 1;
}

void i2c_config_addr(uint8_t slave_addr, uint8_t len)
{
	BRX820_I2C_master->SLAVE_ADDR = slave_addr << 1;
	BRX820_I2C_master->DATA_LENTH = len - 1;
}

uint32_t i2c_master_get_status()
{
	return BRX820_I2C_master->STATUS;
}

void i2c_transmit(uint8_t slave_addr, uint8_t *data, uint8_t len, uint32_t timeout)
{
	int i = 0, tmp, flag = 0, wait = 1;

	if (NULL == data)
		return;

	i2c_config_addr(slave_addr, len);

	if (len < 4) {
		i2c_write_data(data, len, 0);
		i += len;
	} else {
		i2c_write_data(data, 4, 0);
		tmp = len - 4;
		tmp = tmp > 4 ? 4 : tmp;
		i2c_write_data(&data[4], tmp, 1);
		i = tmp + 4;
	}

	i2c_start();

	while (i != len) {
		while (wait) {
			if (BRX820_I2C_master->STATUS_f.ONE_BYTE_FINISH) {
				BRX820_I2C_master->INT_CLEAR.ONE_BYTE_FINISH = 1;
				if (i - BRX820_I2C_master->STATUS_f.DATA_NUM <= 4)
					wait = 0;
			}
		}
		wait = 1;
		tmp = len - i;
		tmp = tmp > 4 ? 4 : tmp;
		i2c_write_data(&data[i], tmp, flag);
		flag = flag == 0 ? 1 : 0;
		i += tmp;
	}

	while (BRX820_I2C_master->STATUS_f.FINISH == 0);
	BRX820_I2C_master->INT_CLEAR.FINISH = 1;

	if (BRX820_I2C_master->STATUS_f.ONE_BYTE_FINISH)
		BRX820_I2C_master->INT_CLEAR.ONE_BYTE_FINISH = 1;

	return;
}

uint8_t is_i2c_busy(void)
{
	return BRX820_I2C_master->STATUS_f.IDLE;
}