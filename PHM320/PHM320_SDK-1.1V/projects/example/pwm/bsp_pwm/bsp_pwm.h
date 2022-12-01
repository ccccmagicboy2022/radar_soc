#ifndef __BSP_PWM_H__
#define __BSP_PWM_H__

#include "typdef.h"

#ifdef __cplusplus
extern "C" {
#endif

enum pwm_sort
{
    PWM_1,
    PWM_2,
    PWM_3,
    PWM_4,
    PWM_5,
};

void pwm_init(int pwm_index);
void pwm_start(uint32_t pwm_port, uint32_t pwm_freq, uint32_t pwm_duty);
void pwm_stop(uint32_t pwm_port);

#endif