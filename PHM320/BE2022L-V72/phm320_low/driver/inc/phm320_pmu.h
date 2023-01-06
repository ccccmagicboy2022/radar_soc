#ifndef __PHM320_PMU_H___
#define __PHM320_PMU_H___

#include "pho_common.h"

#define PLUS_HIGH_LEVEL_DURATION   7// 11.2US   6- 9.6us/50us    5- 8us@10MHz	PWM频率20k		//10 - 10us@16MHz，PWM频率16k

typedef enum em_powered_way
{
    PLUS    = 0,
    ALWAYS  = 1,
}em_powered_way_t;

void ldo_powered_way(em_powered_way_t powered_way);
void first_init();

#endif
