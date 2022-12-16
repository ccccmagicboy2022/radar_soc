#ifndef __BSP_PWM_H__
#define __BSP_PWM_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "stdint.h"
#include "xbr820.h"

void pwm_init(PWM_t *pwm, uint32_t pwm_freq, uint32_t pwm_duty);

#endif
