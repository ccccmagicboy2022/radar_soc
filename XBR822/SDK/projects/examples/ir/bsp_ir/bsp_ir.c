#include "bsp_ir.h"
#include "stdint.h"
#include "xbr821.h"
#include "xbr821_ir.h"
#include "xbr821_utility.h"


/**
 * @brief  IR initialize.
 * @note   The IR will react to the remoter from now on.
 * @param  ir_priority config.
 * @retval none.
 */
void ir_init(uint8_t ir_priority)
{
    //set_pin_func(P1_5, FUNC_IR);
    assert_param(IS_IR_CONFIG_IT(ir_priority));  
    
    stc_irq_set_cfg_t  irq_ir_set_cfg;
    irq_ir_set_cfg.irq_number = IR_IRQ;
    irq_ir_set_cfg.irq_func_pointer = IR_irqhandler;
    irq_ir_set_cfg.irq_priority = ir_priority;
    set_irq(&irq_ir_set_cfg);
    start_irq_x(irq_ir_set_cfg.irq_number);
}

/**
 * @brief  IR de-initialize.
 * @note   The IR will not react to the remoter any more.
 * @param  none.
 * @retval none.
 */
void ir_deinit(void)
{
     stop_irq_x(IR_IRQ);
}
uint8_t ir_flag = 0;
IR_mc_t irdata;

__attribute__ ((section ("INT"))) void IR_irqhandler(void)
{
    ir_flag = 1;
    return;
}

void ir_test(void)
{
    if (ir_flag) {
        ir_read_code(&irdata, IR);

        int i = 4;
        while (i) {
            //putchar( (irdata.ir_code >> (8 * (i - 1) ) ) & 0xff);
            i--;
        }
        ir_flag = 0;
        ir_clr_int(IR);
    }
}


