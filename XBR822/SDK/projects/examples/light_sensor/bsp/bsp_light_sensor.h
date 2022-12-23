#ifndef __BSP_LIGHT_SENSOR_H__
#define __BSP_LIGHT_SENSOR_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "stdint.h"

void ls_init(void);
void ls_deinit(void);
void light_sensor_irqhandler(void);

#ifdef __cplusplus
}
#endif

#endif
