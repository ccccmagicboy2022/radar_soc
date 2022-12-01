#include "phm320_gpio.h"
#include "bsp_pwm.h"
#include "phm320_pwm.h"





int main()
{
    
    pwm_init(PWM_4);
    pwm_start(PWM_4, 10000, 50);

    while (1) {
	;
    }
    return 0;
}
