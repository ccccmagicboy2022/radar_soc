#ifndef __BSP_TIMER_H__
#define __BSP_TIMER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "stdint.h"
#include "xbr820.h"

typedef void (*fun_timer)(void);


void TIMER1_irqhandler(void);
void TIMER2_irqhandler(void);
void TIMER3_irqhandler(void);
void TIMER4_irqhandler(void);
void timer_priority_cfg(fun_timer timer_handler, uint8_t timer_priority, uint8_t timer_int);
void timer_init(TIMER_t *timer, uint32_t counter);
#endif
