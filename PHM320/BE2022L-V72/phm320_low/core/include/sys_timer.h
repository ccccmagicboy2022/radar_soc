#ifndef __SYS_TIMER_H
#define __SYS_TIMER_H

#include "pho_common.h"

typedef enum em_sys_timer_ctl
{
    DISABLE = 0;
    ENABLE = 1;
} em_sys_timer_ctl_t;

void sys_timer_ctl(em_sys_timer_ctl_t sys_timer_ctl);
void sys_timer_getval(uint32_t *low32, uint32_t *high32);
void sys_timer_setcmp(uint32_t *low32, uint32_t *high32);
void sys_timer_delay_us(uint32_t delay_time);

#endif