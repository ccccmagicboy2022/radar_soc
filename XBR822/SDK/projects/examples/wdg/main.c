#include "xbr820.h"
#include "xbr820_wdg.h"

int main()
{
    str_wdg_init_t dog;
    dog.duty_ms = 10000;
    
    wdg_priority_cfg(WDG_irqhandler, IRQ_PRIORITY_DEFAULT);

    wdg_init(&dog);

    while(1);
    
    return 0;
}
