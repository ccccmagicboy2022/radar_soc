#include "bsp_pwm.h"
#include "xbr820.h"


int main()
{
    pwm_init(PWM1, 1000, 90);

    while(1);

    return 0;
}
