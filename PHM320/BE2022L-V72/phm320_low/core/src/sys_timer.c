#include "sys_timer.h"

typedef struct {
    __IO uint32_t EN       :1;
    __IO uint32_t          :31;
} str_sys_timer_t;

#define SYS_TIMER_EN  (((str_sys_timer_t *)(0x1f020000))->EN)
#define MTIMECMPLO    (*(uint32_t *)0xe0004000)
#define MTIMECMPHI    (*(uint32_t *)0xe0004004)
#define MTIMELO       (*(uint32_t *)0xe000bff8)
#define MTIMEHI       (*(uint32_t *)0xe000bffc)

void sys_timer_ctl(em_sys_timer_ctl_t sys_timer_ctl)
{
    SYS_TIMER_EN = sys_timer_ctl;
}

void sys_timer_getval(uint32_t *low32, uint32_t *high32)
{
    *low32 = MTIMELO;
    *high32 = MTIMEHI;
}

void sys_timer_setcmp(uint32_t *low32, uint32_t *high32)
{
    MTIMECMPLO = *low32;
    MTIMECMPHI = *high32;
}

void sys_timer_delay_us(uint32_t delay_time)
{
	sys_timer_ctl(ENABLE);
	while(MTIMELO < (delay_time * 16)) {}
	sys_timer_ctl(DISABLE);
}