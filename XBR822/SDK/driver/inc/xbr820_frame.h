#ifndef __XBR820_IR_H__
#define __XBR820_IR_H__

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "xbr820_interrupts.h"
#include "xbr820.h"

/* Exported constants --------------------------------------------------------*/

#define IS_FRAME_PERIPH(PERIPH)                                 ((PERIPH) == BRX820_FRAME)

/* Exported types ------------------------------------------------------------*/
typedef struct {
    uint32_t t1;
    uint32_t t2;
	uint32_t sel;
	uint32_t start_wait;
} frame_mc_t;

/* Exported functions --------------------------------------------------------*/
void frame_init(brx820_frame_regdef *frame_unit, frame_mc_t* cfg);

#ifdef __cplusplus
}
#endif

#endif
