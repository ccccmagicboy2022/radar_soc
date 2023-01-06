#include "phm320_interrupts.h"
#include "csi_core.h"

void handle_trap(unsigned int cause, unsigned int epc, unsigned int regs[32])
{
    while (1) {}
}

#define      IRQ_NUM_MAX            (23u)

//func_ptr_t irq_handler[IRQ_NUM_MAX] = {NULL};

em_result_t irq_init(const str_irq_set_cfg_t *irq_set_cfg)
{
    em_result_t result_ret = Ok;

    if ((irq_set_cfg->irq_number > IRQ_NUM_MAX) || (irq_set_cfg->irq_number < 0)) {
        result_ret = ERRORINVALIDPARAMETER;
    } else {
        //irq_handler[irq_set_cfg->irq_number] = irq_set_cfg->irq_func_pointer;
		csi_vic_set_prio(irq_set_cfg->irq_number, irq_set_cfg->irq_priority);
		set_shv_irq(irq_set_cfg->irq_number);
		set_rising_edge_irq(irq_set_cfg->irq_number);		
    }

  
    return result_ret;
}

em_result_t irq_start_x(irq_number_e irq_number)
{
    em_result_t result_ret = Ok;

    if ((irq_number > IRQ_NUM_MAX) || (irq_number < 0)) {
        result_ret = ERRORINVALIDPARAMETER;
    } else {
        csi_vic_clear_pending_irq(irq_number);
        csi_vic_enable_irq(irq_number);
    }

    return result_ret;
}

//em_result_t irq_stop_x(irq_number_e irq_number)
//{
//    em_result_t result_ret = Ok;
//
//    if ((irq_number > IRQ_NUM_MAX) || (irq_number < 0)) {
//        result_ret = ERRORINVALIDPARAMETER;
//    } else {
//        csi_vic_disable_irq(irq_number);
//        csi_vic_clear_pending_irq(irq_number);
//    }
//
//    return result_ret;
//}

em_result_t irq_enable_all(void)
{
    em_result_t result_ret = Ok;

    __enable_irq();

    return result_ret;
}

em_result_t irq_disable_all(void)
{
    em_result_t result_ret = Ok;

    __disable_irq();

    return result_ret;
}

//__INT_HANDLER __SECTION_INT void IRQ000_Handler(void)
//{
//    if (NULL != irq_handler[INT_000]) {
//       irq_handler[INT_000]();
//    }
//}
//
//__INT_HANDLER __SECTION_INT void IRQ001_Handler(void)
//{
//    if (NULL != irq_handler[INT_001]) {
//        irq_handler[INT_001]();
//    }
//}
//
//__INT_HANDLER __SECTION_INT void IRQ002_Handler(void)
//{
//    if (NULL != irq_handler[INT_002]) {
//        irq_handler[INT_002]();
//    }
//}
//
//__INT_HANDLER __SECTION_INT void IRQ003_Handler(void)
//{
//    if (NULL != irq_handler[INT_003]) {
//        irq_handler[INT_003]();
//    }
//}
//
//__INT_HANDLER __SECTION_INT void IRQ004_Handler(void)
//{
//    if (NULL != irq_handler[INT_004]) {
//        irq_handler[INT_004]();
//    }
//}
//
//__INT_HANDLER __SECTION_INT void IRQ005_Handler(void)
//{
//    if (NULL != irq_handler[INT_005]) {
//        irq_handler[INT_005]();
//    }
//}
//
//__INT_HANDLER __SECTION_INT void IRQ006_Handler(void)
//{
//    if (NULL != irq_handler[INT_006]) {
//        irq_handler[INT_006]();
//    }
//}

