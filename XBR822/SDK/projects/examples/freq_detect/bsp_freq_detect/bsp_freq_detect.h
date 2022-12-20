#ifndef __BSP_TIMER_H__
#define __BSP_TIMER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "stdint.h"
#include "xbr820.h"

typedef void (*fun_timer)(void);


void freq_detect_irqhandler(void);
void freq_detect_irq_cfg(fun_timer timer_handler, uint8_t timer_priority, uint8_t timer_int);
uint8_t get_freq_det_flag(void);
void set_freq_det_flag(uint8_t flag0);

#ifdef __cplusplus
}
#endif


#endif
