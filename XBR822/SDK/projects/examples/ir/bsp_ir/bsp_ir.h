#ifndef __BSP_IR_H__
#define __BSP_IR_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "stdint.h"

void ir_init(uint8_t ir_priorityr);
void ir_deinit(void);
void ir_test(void);
void IR_irqhandler(void);

#endif