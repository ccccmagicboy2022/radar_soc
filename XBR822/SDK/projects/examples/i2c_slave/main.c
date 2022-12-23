#include "xbr820.h"
#include "xbr820_i2c_slave.h"
#include "xbr820_interrupts.h"
#include "bsp_i2c_slave.h"

int main()
{
    i2c_slave_Cfg_t slave;
    uint8_t reg3 = 0xEB;
    uint8_t val3 = 0x00;
    uint8_t reg3x = 0;
    uint8_t val3x = 0;

    slave.slave_addr = 0xE2;
    i2c_slave_init_bsp(&slave);

    while(1)
    {
        i2c_slave_rev_reg(&reg3x, &val3x);

        if (reg3 == reg3x)
        {
            val3 = val3x;
        }
    }

    return 0;
}

