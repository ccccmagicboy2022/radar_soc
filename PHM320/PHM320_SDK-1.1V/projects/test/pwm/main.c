#include "phm320_gpio.h"
#include "bsp_pwm.h"
#include "phm320_pwm.h"





int main()
{
    /*测试说明：
     * 1、切换不同的PWM引脚
     * 2、修改不同的占空比和频率
     * 3、测试启动和停止PWM功能
     * 4、通过示波器查看测试版的测试点输出是否正常
    */
    pwm_init(PWM_4);
    pwm_start(PWM_4, 10000, 50);
    pwm_stop(PWM_4);
    while (1) {
	;
    }
    return 0;
}
