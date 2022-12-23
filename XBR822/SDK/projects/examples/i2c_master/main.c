#include "xbr820.h"
#include "bsp_i2c_master.h"
#include "xbr820_i2c_master.h"
#include "xbr820_interrupts.h"

int main()
{
    uint8_t i2c_reg0 = 0;
    uint8_t res = 0;
    i2c_master_Cfg_t xbr;

    xbr.i2c_speed = 10000;
    xbr.slave_addr = 0xE2;

    i2c_master_init(&xbr);
    res = i2c_master_read_reg(0x03, &i2c_reg0);
    res = i2c_master_write_reg(0x03, 0x05);
    res = i2c_master_read_reg(0x03, &i2c_reg0);

    while(1)
    {
        //pass
    }

    return 0;
}

