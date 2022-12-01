/**
 * @file phm320_interrupts.c
 * @author Phosense Software Team
 * @brief interrupts driver C source file
 * @version 1.0.0.0
 * @date 2022-03-21
 * 
 * @copyright Copyright (c) 2022, Phosense-tech, All rights reserved.
 * 
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "phm320_interrupts.h"
#include "csi_core.h"

/** @{*/

/**
 * @brief non-vector entry function
 * 
 * @param [in] cause 
 * @param [in] epc 
 * @param [in] regs 
 */
void handle_trap(unsigned int cause, unsigned int epc, unsigned int regs[32])
{
    while (1) {}
}

/** Max IRQ Handler. */
#define      IRQ_NUM_MAX            (23u)

/** array of interrupt function pointers. */
func_ptr_t irq_handler[IRQ_NUM_MAX] = {NULL};

/**
 * @brief init interrupt request
 * 
 * @param [in] irq_set_cfg  pointer to interrupt initialization structure.
 *                          see @ref str_irq_set_cfg_t for details.
 * @return em_result_t
 * - OK no error occurred.
 */
em_result_t irq_init(const str_irq_set_cfg_t *irq_set_cfg)
{
    em_result_t result_ret = Ok;

    if ((irq_set_cfg->irq_number > IRQ_NUM_MAX) || (irq_set_cfg->irq_number < 0)) {
        result_ret = ERRORINVALIDPARAMETER;
    } else {
        irq_handler[irq_set_cfg->irq_number] = irq_set_cfg->irq_func_pointer;
    }

    csi_vic_set_prio(irq_set_cfg->irq_number, irq_set_cfg->irq_priority);
    set_shv_irq(irq_set_cfg->irq_number);
    set_rising_edge_irq(irq_set_cfg->irq_number);

    return result_ret;
}

/**
 * @brief start irq_number
 * 
 * @param [in] irq_number irq number, This parameter can be
 *                                    any composed value of @ref irq_number_e
 * @return em_result_t
 * - OK no error occurred. 
 */
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

/**
 * @brief stop irq_number
 * 
 * @param [in] irq_number irq number, This parameter can be
 *                                    any composed value of @ref irq_number_e
 * @return em_result_t
 * - OK no error occurred. 
 */
em_result_t irq_stop_x(irq_number_e irq_number)
{
    em_result_t result_ret = Ok;

    if ((irq_number > IRQ_NUM_MAX) || (irq_number < 0)) {
        result_ret = ERRORINVALIDPARAMETER;
    } else {
        csi_vic_disable_irq(irq_number);
        csi_vic_clear_pending_irq(irq_number);
    }

    return result_ret;
}

/**
 * @brief enable irq
 * 
 * @return em_result_t
 * - OK no error occurred.
 */
em_result_t irq_enable_all(void)
{
    em_result_t result_ret = Ok;

    __enable_irq();

    return result_ret;
}

/**
 * @brief disable irq
 * 
 * @return em_result_t
 * - OK no error occurred. 
 */
em_result_t irq_disable_all(void)
{
    em_result_t result_ret = Ok;

    __disable_irq();

    return result_ret;
}

/**
 * @brief top irq
 * 
 */
__INT_HANDLER __SECTION_INT void IRQ000_Handler(void)
{
    if (NULL != irq_handler[INT_000]) {
        irq_handler[INT_000]();
    }
}

/**
 * @brief ir irq
 * 
 */
__INT_HANDLER __SECTION_INT void IRQ001_Handler(void)
{
    if (NULL != irq_handler[INT_001]) {
        irq_handler[INT_001]();
    }
}

/**
 * @brief wdg irq
 * 
 */
__INT_HANDLER __SECTION_INT void IRQ002_Handler(void)
{
    if (NULL != irq_handler[INT_002]) {
        irq_handler[INT_002]();
    }
}

/**
 * @brief timer1 irq
 * 
 */
__INT_HANDLER __SECTION_INT void IRQ003_Handler(void)
{
    if (NULL != irq_handler[INT_003]) {
        irq_handler[INT_003]();
    }
}

/**
 * @brief timer2 irq
 * 
 */
__INT_HANDLER __SECTION_INT void IRQ004_Handler(void)
{
    if (NULL != irq_handler[INT_004]) {
        irq_handler[INT_004]();
    }
}

/**
 * @brief timer3 irq
 * 
 */
__INT_HANDLER __SECTION_INT void IRQ005_Handler(void)
{
    if (NULL != irq_handler[INT_005]) {
        irq_handler[INT_005]();
    }
}

/**
 * @brief timer4 irq
 * 
 */
__INT_HANDLER __SECTION_INT void IRQ006_Handler(void)
{
    if (NULL != irq_handler[INT_006]) {
        irq_handler[INT_006]();
    }
}

/**  @} interrupts_group*/
