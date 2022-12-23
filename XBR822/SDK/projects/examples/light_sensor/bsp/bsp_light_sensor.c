#include "bsp_light_sensor.h"
#include "stdint.h"
#include "xbr820.h"
#include "xbr820_light_sensor.h"
#include "xbr820_utility.h"

uint8_t flag_update = 0;

void ls_init(void)
{
	light_sensor_mc_t cfg;
	
	cfg.delay = 5;
	cfg.interval_select = 3;
	cfg.mode = 0;
	
	light_sensor_init(BRX820_LIGHT_SENSOR, &cfg);
	light_sensor_irq_cfg(light_sensor_irqhandler, IRQ_PRIORITY_DEFAULT, LIGHT_SENSOR_IRQ);
	light_sensor_int_cmd(BRX820_LIGHT_SENSOR, LIGHT_SENSOR_SR_INT, ENABLE);
	
}

void ls_deinit(void)
{
	light_sensor_int_cmd(BRX820_LIGHT_SENSOR, LIGHT_SENSOR_SR_INT, DISABLE);
	stop_irq_x(LIGHT_SENSOR_IRQ);
}

__attribute__ ((section ("INT"))) void light_sensor_irqhandler(void)
{
    csi_vic_clear_pending_irq(LIGHT_SENSOR_IRQ);

    if (light_get_int_status(BRX820_LIGHT_SENSOR, LIGHT_SENSOR_SR_INT) == SET)
    {
        light_sensor_clr_int(BRX820_LIGHT_SENSOR);
		flag_update = 1;
    }
	
    return;
}
