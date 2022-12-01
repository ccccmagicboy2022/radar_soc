#include "bsp_ir.h"
#include "phm320_gpio.h"
#include "phm320_ir.h"
#include "phm320_gpio.h"
#include "phm320_interrupts.h"
#include <string.h>



/**
 * @brief  IR initialize.
 * @note   The IR will react to the remoter from now on.
 * @param  ir_priority config.
 * @retval none.
 */
void ir_init(uint8_t ir_priority)
{
    pin_set_func(P1_5, FUNC_IR);
    str_irq_set_cfg_t  irq_ir_set_cfg;
    irq_ir_set_cfg.irq_number = INT_001;
    irq_ir_set_cfg.irq_func_pointer = IR_irqhandler;
    irq_ir_set_cfg.irq_priority = ir_priority;
    irq_init(&irq_ir_set_cfg);
    irq_start_x(irq_ir_set_cfg.irq_number);
}

/**
 * @brief  IR de-initialize.
 * @note   The IR will not react to the remoter any more.
 * @param  none.
 * @retval none.
 */
void ir_deinit(void)
{
    irq_stop_x(INT_001);
}

void led_init(void)
{
    pin_set_func(P1_2, FUNC_GPIO);
    str_gpio_init_cfg_t gpio_cfg;
    gpio_cfg.gpio_mode   = GPIO_OUT;
    gpio_init(P1_2, &gpio_cfg);
}
uint8_t ir_flag = 0;
IR_mc_t irdata;

__attribute__ ((section ("INT"))) void IR_irqhandler(void) {
    ir_flag = 1;
    gpio_toggle(P1_2);
    return;
}

void ir_test(void) {
    if (ir_flag) {
        ir_read_code(&irdata);

        int i = 4;
        while (i) {
        //putchar( (irdata.ir_code >> (8 * (i - 1) ) ) & 0xff);
            i--;
        }
        ir_flag = 0;
        ir_clr_int();
    }
}





