/**
 * @file phm320_interrupts.h
 * @author Phosense Software Team
 * @brief interrupts driver head file
 * @version 1.0.0.0
 * @date 2022-03-21
 * 
 * @copyright Copyright (c) 2022, Phosense-tech, All rights reserved.
 * 
 */
#ifndef __PHM320_INTERRUPTS_H___
#define __PHM320_INTERRUPTS_H___

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "pho_common.h"

/**
 * @defgroup interrupts_group Interrupt
 * @{
 */

/**
 * @brief  interrupts request set structure definition
 * 
 */
typedef struct str_irq_set_cfg
{
    irq_number_e irq_number;
    func_ptr_t irq_func_pointer;
    uint32_t irq_priority;
}str_irq_set_cfg_t;

/** define INT section and machine interrupt */
#define     __SECTION_INT   __attribute__ ((section ("INT")))
#define     __INT_HANDLER   __attribute__ ((interrupt ("machine")))

/** Default Priority for IRQ */
#define     IRQ_PRIORITY_DEFAULT    0u

/** Interrupt priority level 0 ~ 7 */
#define     DDL_IRQ_PRIORITY_00         (0u)
#define     DDL_IRQ_PRIORITY_01         (1u)
#define     DDL_IRQ_PRIORITY_02         (2u)
#define     DDL_IRQ_PRIORITY_03         (3u)
#define     DDL_IRQ_PRIORITY_04         (4u)
#define     DDL_IRQ_PRIORITY_05         (5u)
#define     DDL_IRQ_PRIORITY_06         (6u)
#define     DDL_IRQ_PRIORITY_07         (7u)

/*******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
em_result_t irq_init(const str_irq_set_cfg_t *irq_set_cfg);
em_result_t irq_start_x(irq_number_e irq_number);
em_result_t irq_stop_x(irq_number_e irq_number);
em_result_t irq_enable_all(void);
em_result_t irq_disable_all(void);

/**  @} interrupts_group*/

#endif  // __PHM320_INTERRUPTS_H___
