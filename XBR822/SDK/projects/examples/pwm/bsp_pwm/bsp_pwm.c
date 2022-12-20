#include "bsp_pwm.h"
#include "stdint.h"
#include <stdio.h>
#include <string.h>
#include "xbr820.h"
#include "xbr820_pwm.h"
#include "xbr820_utility.h"


void pwm_init(uint8_t id, uint32_t pwm_freq, uint32_t pwm_duty)
{
    PWM_Config_t pwmconf;
	
    pwmconf.freq = pwm_freq;
    pwmconf.duty = pwm_duty;
	pwmconf.idx = id;
    pwm_enable(&pwmconf);
}

