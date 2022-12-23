#include "bsp_i2c_slave.h"
#include "stdint.h"
#include "xbr820.h"
#include "xbr820_i2c_slave.h"
#include "xbr820_utility.h"
#include "xbr820_interrupts.h"

uint8_t slave_trans_flag = 0;
uint8_t slave_rev_flag = 0;

void i2c_slave_init_bsp(i2c_slave_Cfg_t* i2c_slav)
{
    I2C_slave_init(BRX820_I2C_SLAVE, i2c_slav->slave_addr);
    I2C_slave_int_cmd(BRX820_I2C_SLAVE, I2C_SLAVE_RW_MASK | I2C_SLAVE_STOP_MASK, ENABLE);
    i2c_slave_irq_cfg(i2c_slave_irqhandler, IRQ_PRIORITY_DEFAULT, I2C_SLAVE_IRQ);
}

void i2c_slave_prepare_write_data(uint8_t data)
{
    I2C_slave_write_data(BRX820_I2C_SLAVE, data);
}

void i2c_slave_rev_reg(uint8_t* reg, uint8_t* dat)
{
    while (slave_trans_flag == 0)
    {
        //wait
    }

    *dat = I2C_slave_read_data(BRX820_I2C_SLAVE);
    *reg = I2C_slave_read_word_addr(BRX820_I2C_SLAVE);
}

__attribute__ ((section ("INT"))) void i2c_slave_irqhandler(void)
{
    /*do something*/
    csi_vic_clear_pending_irq(I2C_SLAVE_IRQ);
    I2C_slave_clear_flag(BRX820_I2C_SLAVE, I2C_SLAVE_CLR_INT);

    if (I2C_slave_get_int_status(BRX820_I2C_SLAVE, I2C_SLAVE_SR_RW_DONE) == SET)
    {
        I2C_slave_clear_flag(BRX820_I2C_SLAVE, I2C_SLAVE_CLR_RW);
        if (I2C_slave_get_int_status(BRX820_I2C_SLAVE, I2C_SLAVE_SR_RW) == SET)
        {
            //transmit
        }
        else
        {
            //rev
        }
    }

    if (I2C_slave_get_int_status(BRX820_I2C_SLAVE, I2C_SLAVE_SR_NACK) == SET)
    {
        I2C_slave_clear_flag(BRX820_I2C_SLAVE, I2C_SLAVE_CLR_NACK);
    }

    if (I2C_slave_get_int_status(BRX820_I2C_SLAVE, I2C_SLAVE_SR_STOP) == SET)
    {
        I2C_slave_clear_flag(BRX820_I2C_SLAVE, I2C_SLAVE_CLR_STOP);
        if (I2C_slave_get_int_status(BRX820_I2C_SLAVE, I2C_SLAVE_SR_RW) == SET)
        {
            //transmit
            slave_trans_flag = 1;
        }
        else
        {
            //rev
            slave_rev_flag = 1;
        }
    }

    if (I2C_slave_get_int_status(BRX820_I2C_SLAVE, I2C_SLAVE_SR_ADDR) == SET)
    {
        I2C_slave_clear_flag(BRX820_I2C_SLAVE, I2C_SLAVE_CLR_ADDR);
        if (I2C_slave_get_int_status(BRX820_I2C_SLAVE, I2C_SLAVE_SR_RW) == SET)
        {
            //transmit
        }
        else
        {
            //rev
        }
    }

    return;
}
