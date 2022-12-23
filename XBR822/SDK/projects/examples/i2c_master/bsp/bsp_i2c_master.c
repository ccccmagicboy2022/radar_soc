#include "bsp_i2c_master.h"
#include "stdint.h"
#include "xbr820.h"
#include "xbr820_i2c_master.h"
#include "xbr820_utility.h"
#include "xbr820_interrupts.h"

void i2c_master_init(i2c_master_Cfg_t* i2c_mast)
{
    I2C_config_slave_addr(BRX820_I2C_MASTER, i2c_mast->slave_addr);
    I2C_init(BRX820_I2C_MASTER, i2c_mast->i2c_speed);
    I2C_int_cmd(BRX820_I2C_MASTER, I2C_INT_RW_DONE | I2C_INT_STOP, ENABLE);
    i2c_master_irq_cfg(i2c_master_irqhandler, IRQ_PRIORITY_DEFAULT, I2C_MASTER_IRQ);
}

int i2c_master_read_reg(uint8_t reg_addr, uint8_t* data)
{
    I2C_clear_flag(BRX820_I2C_MASTER, I2C_INT_STOP);
    I2C_set_rw_num(BRX820_I2C_MASTER, 1);
    I2C_start_read(BRX820_I2C_MASTER, reg_addr, 0);

    while (I2C_get_int_status(BRX820_I2C_MASTER, I2C_SR_STOP) != SET)
    {
        //wait
    }

    return 0;
}

int i2c_master_write_reg(uint8_t reg_addr, uint8_t data)
{
    I2C_clear_flag(BRX820_I2C_MASTER, I2C_INT_STOP);
    I2C_set_rw_num(BRX820_I2C_MASTER, 3);
    I2C_master_set_transmit_buffer(BRX820_I2C_MASTER, 0, reg_addr);
    I2C_master_set_transmit_buffer(BRX820_I2C_MASTER, 1, data);
    I2C_start_write(BRX820_I2C_MASTER);

    while (I2C_get_int_status(BRX820_I2C_MASTER, I2C_SR_STOP) != SET)
    {
        //wait
    }

    return 0;
}

__attribute__ ((section ("INT"))) void i2c_master_irqhandler(void)
{
    /*do something*/
    csi_vic_clear_pending_irq(I2C_MASTER_IRQ);

    if (I2C_get_int_status(BRX820_I2C_MASTER, I2C_SR_RW_DONE) == SET)
    {
        I2C_clear_flag(BRX820_I2C_MASTER, I2C_INT_RW_DONE);
    }

    if (I2C_get_int_status(BRX820_I2C_MASTER, I2C_SR_TIMEOUT) == SET)
    {
        I2C_clear_flag(BRX820_I2C_MASTER, I2C_INT_TIMEOUT);
    }

    if (I2C_get_int_status(BRX820_I2C_MASTER, I2C_SR_STOP) == SET)
    {
        I2C_clear_flag(BRX820_I2C_MASTER, I2C_INT_STOP);
    }

    if (I2C_get_int_status(BRX820_I2C_MASTER, I2C_SR_NACK) == SET)
    {
        I2C_clear_flag(BRX820_I2C_MASTER, I2C_INT_NACK);
    }

    return;
}
