#include "bsp_pwm.h"
#include "phm320_pwm.h"
#include "phm320_gpio.h"



void pwm_init(int pwm_index)
{
    switch (pwm_index) {
    case PWM_1:
        pin_set_func(P1_0, FUNC_PWM);
        break;
    case PWM_2:
        pin_set_func(P1_1, FUNC_PWM);
        break;
    case PWM_3:
        pin_set_func(P1_2, FUNC_PWM);
        break;
    case PWM_4:
        pin_set_func(P1_3, FUNC_PWM);
        break;
    case PWM_5:
        pin_set_func(P1_4, FUNC_PWM);
        break;
    default:
        break;
    }
}
void pwm_start(uint32_t pwm_port, uint32_t pwm_freq, uint32_t pwm_duty )
{
    PWM_Config_t pwmconf;

    pwmconf.idx  =  pwm_port;
    pwmconf.freq =  pwm_freq;
    pwmconf.duty = pwm_duty;
    pwm_enable(&pwmconf);
}

void pwm_stop(uint32_t pwm_port)
{
    PWM_Config_t pwmconf;

    pwmconf.idx  =  pwm_port;
    pwm_disable(&pwmconf);
}