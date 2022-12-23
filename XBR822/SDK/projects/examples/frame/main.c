#include "xbr820_interrupts.h"
#include "xbr820_frame.h"
#include "bsp_frame.h"
#include "xbr820.h"

int main()
{
	frame_mc_t cfg;
	
	cfg.sel = 0x01;
	cfg.start_wait = 0x5;
	cfg.t1 = 0xEA600;
	cfg.t2 = 0x17700;
	
	frame_init(BRX820_FRAME, &cfg);
	
    while(1)
    {
        //pass
    }
    return 0;
}
