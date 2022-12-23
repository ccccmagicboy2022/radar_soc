#include "xbr820_interrupts.h"
#include "xbr820_light_sensor.h"
#include "bsp_light_sensor.h"
#include "xbr820.h"

extern uint8_t flag_update;

int main()
{
	uint8_t ls_flag = 0;
	ls_init();
	
    while(1)
    {
        if (flag_update)
		{
			ls_flag = light_sensor_get_flag(BRX820_LIGHT_SENSOR);
			flag_update = 0;
		}
    }
    return 0;
}
