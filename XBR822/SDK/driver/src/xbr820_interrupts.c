#include "xbr820_interrupts.h"
#include "csi_core.h"

void handle_trap(unsigned int cause, unsigned int epc, unsigned int regs[32])
{
    while (1) {}
}

#define      IRQ_NUM_MAX            (20u)

func_ptr_t irq_handler[IRQ_NUM_MAX] = {NULL};

em_result_t set_irq(const stc_irq_set_cfg_t *irq_set_cfg)
{
    em_result_t result_ret = OK;

    if ((irq_set_cfg->irq_number > IRQ_NUM_MAX) || (irq_set_cfg->irq_number < 0))
    {
        result_ret = ERROR;
    } else {
        irq_handler[irq_set_cfg->irq_number] = irq_set_cfg->irq_func_pointer;
    }

    csi_vic_set_prio(irq_set_cfg->irq_number, irq_set_cfg->irq_priority);
    set_shv_irq(irq_set_cfg->irq_number);
    set_rising_edge_irq(irq_set_cfg->irq_number);

    return result_ret;
}

em_result_t start_irq_x(irq_number_e irq_number)
{
    em_result_t result_ret = OK;

    if ((irq_number > IRQ_NUM_MAX) || (irq_number < 0))
    {
        result_ret = ERROR;
    } else {
        csi_vic_clear_pending_irq(irq_number);
        csi_vic_enable_irq(irq_number);
    }

    return result_ret;
}

em_result_t stop_irq_x(irq_number_e irq_number)
{
    em_result_t result_ret = OK;

    if ((irq_number > IRQ_NUM_MAX) || (irq_number < 0))
    {
        result_ret = ERROR;
    } else {
        csi_vic_disable_irq(irq_number);
        csi_vic_clear_pending_irq(irq_number);
    }

    return result_ret;
}

em_result_t enable_irq_all(void)
{
    em_result_t result_ret = OK;

    __enable_irq();

    return result_ret;
}

em_result_t disable_irq_all(void)
{
    em_result_t result_ret = OK;

    __disable_irq();

    return result_ret;
}

__INT_HANDLER __SECTION_INT void IRQ001_Handler(void)
{
    if (NULL != irq_handler[UART_RX_IRQ])
    {
        irq_handler[UART_RX_IRQ]();
    }
}


__INT_HANDLER __SECTION_INT void IRQ002_Handler(void)
{
    if (NULL != irq_handler[UART_TX_IRQ])
    {
        irq_handler[UART_TX_IRQ]();
    }
}


__INT_HANDLER __SECTION_INT void IRQ003_Handler(void)
{
    if (NULL != irq_handler[TIMER1_IRQ])
    {
        irq_handler[TIMER1_IRQ]();
    }
}


__INT_HANDLER __SECTION_INT void IRQ004_Handler(void)
{
    if (NULL != irq_handler[TIMER2_IRQ])
    {
        irq_handler[TIMER2_IRQ]();
    }
}


__INT_HANDLER __SECTION_INT void IRQ005_Handler(void)
{
    if (NULL != irq_handler[TIMER3_IRQ])
    {
        irq_handler[TIMER3_IRQ]();
    }
}


__INT_HANDLER __SECTION_INT void IRQ006_Handler(void)
{
    if (NULL != irq_handler[TIMER4_IRQ])
    {
        irq_handler[TIMER4_IRQ]();
    }
}


__INT_HANDLER __SECTION_INT void IRQ007_Handler(void)
{
    if (NULL != irq_handler[ADC_DONE_IRQ])
    {
        irq_handler[ADC_DONE_IRQ]();
    }
}

__INT_HANDLER __SECTION_INT void IRQ009_Handler(void)
{
    if (NULL != irq_handler[IR_IRQ])
    {
        irq_handler[IR_IRQ]();
    }
}


__INT_HANDLER __SECTION_INT void IRQ010_Handler(void)
{
    if (NULL != irq_handler[WDG_IRQ])
    {
        irq_handler[WDG_IRQ]();
    }
}


__INT_HANDLER __SECTION_INT void IRQ011_Handler(void)
{
    if (NULL != irq_handler[GPIO_PA0_IRQ])
    {
        irq_handler[GPIO_PA0_IRQ]();
    }
}


__INT_HANDLER __SECTION_INT void IRQ012_Handler(void)
{
    if (NULL != irq_handler[GPIO_PA1_IRQ])
    {
        irq_handler[GPIO_PA1_IRQ]();
    }
}


__INT_HANDLER __SECTION_INT void IRQ013_Handler(void)
{
    if (NULL != irq_handler[GPIO_PA2_IRQ])
    {
        irq_handler[GPIO_PA2_IRQ]();
    }
}

__INT_HANDLER __SECTION_INT void IRQ014_Handler(void)
{
    if (NULL != irq_handler[GPIO_PA3_IRQ])
    {
        irq_handler[GPIO_PA3_IRQ]();
    }
}

__INT_HANDLER __SECTION_INT void IRQ017_Handler(void)
{
    if (NULL != irq_handler[LIGHT_SENSOR_IRQ])
    {
        irq_handler[LIGHT_SENSOR_IRQ]();
    }
}

__INT_HANDLER __SECTION_INT void IRQ018_Handler(void)
{
    if (NULL != irq_handler[FREQ_DET_IRQ])
    {
        irq_handler[FREQ_DET_IRQ]();
    }
}

__INT_HANDLER __SECTION_INT void IRQ019_Handler(void)
{
    if (NULL != irq_handler[I2C_MASTER_IRQ])
    {
        irq_handler[I2C_MASTER_IRQ]();
    }
}

__INT_HANDLER __SECTION_INT void IRQ020_Handler(void)
{
    if (NULL != irq_handler[I2C_SLAVE_IRQ])
    {
        irq_handler[I2C_SLAVE_IRQ]();
    }
}

