#include "xbr820.h"
#include "xbr820_light_sensor.h"
#include "xbr820_utility.h"
#include "xbr820_interrupts.h"

void light_sensor_irq_cfg(fun_light_sensor _handler, uint8_t _priority, uint8_t _int_num)
{
    stc_irq_set_cfg_t  set_cfg;

    set_cfg.irq_number = _int_num;
    set_cfg.irq_func_pointer = _handler;
    set_cfg.irq_priority = _priority;

    set_irq(&set_cfg);
    start_irq_x(set_cfg.irq_number);
}

void light_sensor_int_cmd(brx820_light_sensor_regdef *ls_unit, uint32_t ls_it, em_functional_state_t state)
{
    assert_param(IS_LIGHT_SENSOR_PERIPH(ls_unit));
    assert_param(IS_FUNCTIONAL_STATE(state));
    assert_param(IS_LIGHT_SENSOR_CONFIG_IT(ls_it));

    if (state != DISABLE)
        ls_unit->CR2 |= ls_it;
    else
        ls_unit->CR2 &= ~ls_it;
}

void light_sensor_clr_int(brx820_light_sensor_regdef *ls_unit)
{
    assert_param(IS_LIGHT_SENSOR_PERIPH(ls_unit));

    ls_unit->CR2 &= ~LIGHT_SENSOR_SR_INT;
}

void light_sensor_init(brx820_light_sensor_regdef *ls_unit, light_sensor_mc_t *mc_data)
{
	assert_param(IS_LIGHT_SENSOR_PERIPH(ls_unit));
	
	ls_unit->CR1_f.TRIM = mc_data->mode;
	ls_unit->CR2_f.DELAY = mc_data->delay;
	ls_unit->CR2_f.INTERVAL_SELECT = mc_data->interval_select;
}

uint8_t light_sensor_get_flag(brx820_light_sensor_regdef *ls_unit)
{
	assert_param(IS_LIGHT_SENSOR_PERIPH(ls_unit));
	return ls_unit->CR2_f.FLAG;
}

void light_sensor_reset(brx820_light_sensor_regdef *ls_unit)
{
	assert_param(IS_LIGHT_SENSOR_PERIPH(ls_unit));
	ls_unit->CR1_f.RESETN = 1;
}

em_flag_status_t light_get_int_status(brx820_light_sensor_regdef *ls_unit, uint32_t flag)
{
    em_flag_status_t ret = RESET;

	assert_param(IS_LIGHT_SENSOR_PERIPH(ls_unit));

    if (0ul != ((ls_unit->CR2) & (flag)))
        ret = SET;

    return ret;
}
