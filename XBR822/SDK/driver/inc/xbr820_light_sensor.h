#ifndef __XBR820_LIGHT_SENSOR_H__
#define __XBR820_LIGHT_SENSOR_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "xbr820_interrupts.h"
#include "xbr820.h"

/* Exported constants --------------------------------------------------------*/

#define IS_LIGHT_SENSOR_PERIPH(PERIPH)                                 ((PERIPH) == BRX820_LIGHT_SENSOR)
#define IS_LIGHT_SENSOR_CONFIG_IT(IT)                                  ((((IT) <= 0x0F) && ((IT) >= 0x00))

#define LIGHT_SENSOR_SR_FLAG                                                   (1ul << 2)
#define LIGHT_SENSOR_SR_INT                                                    (1ul << 1)

/* Exported types ------------------------------------------------------------*/
typedef struct {
    uint32_t mode;
    uint32_t delay;
	uint32_t interval_select;
} light_sensor_mc_t;

/* Exported functions --------------------------------------------------------*/
typedef void (*fun_light_sensor)(void);
void light_sensor_irq_cfg(fun_light_sensor _handler, uint8_t _priority, uint8_t _int_num);
void light_sensor_int_cmd(brx820_light_sensor_regdef *ls_unit, uint32_t ls_it, em_functional_state_t state);
void light_sensor_clr_int(brx820_light_sensor_regdef *ls_unit);
void light_sensor_init(brx820_light_sensor_regdef *ls_unit, light_sensor_mc_t *mc_data);
void light_sensor_reset(brx820_light_sensor_regdef *ls_unit);
uint8_t light_sensor_get_flag(brx820_light_sensor_regdef *ls_unit);
em_flag_status_t light_get_int_status(brx820_light_sensor_regdef *ls_unit, uint32_t flag);


#ifdef __cplusplus
}
#endif

#endif
