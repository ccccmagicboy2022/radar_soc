#ifndef __BSP_WDG_H__
#define __BSP_WDG_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "stdint.h"
#include "xbr820.h"

/* Includes ------------------------------------------------------------------*/
#include "xbr820_interrupts.h"
#include "xbr820_utility.h"

/* Exported constants --------------------------------------------------------*/

#define IS_WDG_PERIPH(PERIPH)                                   ((PERIPH) == BRX820_WDG)
#define IS_WDG_CONFIG_IT(IT)                                    ((((IT) <= 0x0F) && ((IT) >= 0x00))

/* Exported types ------------------------------------------------------------*/


/* Exported functions --------------------------------------------------------*/
void wdg_enable(brx820_wdg_regdef *wdg, uint32_t wdg_counter);
void wdg_disable(brx820_wdg_regdef *wdg);

typedef void (*fun_wdg)(void);
/**
 * @brief wdg init structure definition
 *
 */
typedef struct str_wdg_init
{
    uint32_t         duty_ms;
} str_wdg_init_t;



void wdg_priority_cfg(fun_wdg wdg_handler, uint8_t wdg_priority);
void wdg_init(const str_wdg_init_t *wdg_init_cfg);
void WDG_irqhandler(void);

#ifdef __cplusplus
{
#endif

#endif
