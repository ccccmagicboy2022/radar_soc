#include "bsp_pwm.h"
#include "xbr820.h"
#include "xbr820_pwm.h"

int main()
{
    pwm_init(PWM1, 1000, 90);
	pwm_init(PWM2, 1000, 90);
	pwm_init(PWM3, 1000, 90);
	pwm_init(PWM4, 1000, 90);
	pwm_init(PWM5, 1000, 90);

    while(1);

    return 0;
}
