#ifndef __SYS_TIMER_H
#define __SYS_TIMER_H

#include "xbr820.h"
#include "pho_common.h"

void sys_timer_start(em_functional_state_t sys_timer_ctl);
void sys_timer_getval(uint32_t *low32, uint32_t *high32);
void sys_timer_setcmp(uint32_t *low32, uint32_t *high32);

#endif
