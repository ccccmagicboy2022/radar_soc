#include "xbr820.h"
#include "xbr820_frame.h"
#include "xbr820_utility.h"
#include "xbr820_interrupts.h"

void frame_init(brx820_frame_regdef *frame_unit, frame_mc_t* cfg)
{
	assert_param(IS_FRAME_PERIPH(frame_unit));
	
	frame_unit->CR1_f.SEL = cfg->sel;
	frame_unit->CR1_f.START_WAIT = cfg->start_wait;
	frame_unit->T1 = cfg->t1;
	frame_unit->T2 = cfg->t2;
}


