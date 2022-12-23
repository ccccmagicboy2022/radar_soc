#include "xbr820.h"
#include "xbr820_sys_timer.h"

int main()
{
    uint32_t hi32;
    uint32_t lo32;

    em_functional_state_t systimer_ctl = ENABLE;

    sys_timer_start(systimer_ctl);

    hi32 = 0x33ff2255;
    lo32 = 0x88fe1122;

    sys_timer_getval(&lo32, &hi32);
    hi32++;
    lo32++;
    sys_timer_setcmp(&lo32, &hi32);

    while(1);

    return 0;
}
