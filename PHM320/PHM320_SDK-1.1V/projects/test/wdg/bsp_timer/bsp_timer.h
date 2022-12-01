#ifndef __BSP_TIMER_H__
#define __BSP_TIMER_H__

#include "typdef.h"

#ifdef __cplusplus
extern "C" {
#endif

void timer_init(uint8_t timer_id,  uint8_t timer_priority);
void timer_start(uint8_t timer_id, uint32_t timer_cmpvalue);
void timer_stop(uint8_t timer_id);
void watch_dog(uint8_t dog_reset_enable, uint8_t dog_counter_enable, uint32_t dog_cmpvalue);
void TIM0_IRQHandler(void);
void TIM1_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM3_IRQHandler(void);
void led_init(void);
#endif