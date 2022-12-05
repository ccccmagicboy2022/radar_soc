#ifndef __XBR826_INTERRUPTS_H___
#define __XBR826_INTERRUPTS_H___

#include "pho_common.h"

typedef enum irq_number
{
    INT_SOFT                 = 3,
    INT_SYS_TIMER            = 7,
    INT_EXTERNAL            = 11,
    INT_000                 = 16,
    INT_001                 = 17,
    INT_002                 = 18,
    INT_003                 = 19,
    INT_004                 = 20,
    INT_005                 = 21,
    INT_006                 = 22,
    INT_007                 = 23,
}irq_number_e;

typedef struct str_irq_set_conf
{
    irq_number_e irq_number;
    func_ptr_t irq_func_pointer;
    uint32_t irq_priority;
}str_irq_set_cfg_t;

/* Default Priority for IRQ */
#define     IRQ_PRIORITY_DEFAULT    0u

#define     __SECTION_INT   __attribute__ ((section ("INT")))
#define     __INT_HANDLER   __attribute__ ((interrupt ("machine")))

/* Interrupt priority level 0 ~ 7 */
#define     DDL_IRQ_PRIORITY_00         (0u)
#define     DDL_IRQ_PRIORITY_01         (1u)
#define     DDL_IRQ_PRIORITY_02         (2u)
#define     DDL_IRQ_PRIORITY_03         (3u)
#define     DDL_IRQ_PRIORITY_04         (4u)
#define     DDL_IRQ_PRIORITY_05         (5u)
#define     DDL_IRQ_PRIORITY_06         (6u)
#define     DDL_IRQ_PRIORITY_07         (7u)

em_result_t irq_init(const str_irq_set_cfg_t *irq_set_cfg);
em_result_t irq_start_x(irq_number_e irq_number);
em_result_t irq_stop_x(irq_number_e irq_number);
em_result_t irq_enable_all(void);
em_result_t irq_disable_all(void);

#endif
