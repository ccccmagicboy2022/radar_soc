#include "phm320_gpio.h"
#include "phm320_ir.h"
#include "bsp_ir.h"
#include "phm320_interrupts.h"


/*
 * 测试说明：
 * 1、添加中断服务函数内容验证IR的正确性
 * 2、本测试用例中中断服务函数实现LED翻转
 * 3、通过红外按键验证IR的正确性
 * */
int main()
{
    irq_enable_all();
    led_init();
    ir_init(IRQ_PRIORITY_DEFAULT);   
    
    while (1) {
        ir_test();
    }
    return 0;
}
