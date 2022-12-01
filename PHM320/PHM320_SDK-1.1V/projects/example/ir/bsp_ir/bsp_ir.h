#ifndef  __BSP_IR_H__
#define  __BSP_IR_H__


#include "typdef.h"

#ifdef __cplusplus
extern "C" {
#endif


void IR_irqhandler(void) ;
void ir_test(void);
void ir_init(uint8_t  ir_priority);
void led_init(void);


#endif