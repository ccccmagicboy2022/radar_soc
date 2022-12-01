#include "delay.h"
#include "stm32f1xx_hal.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

static u8  fac_us = 0;
static u16 fac_ms = 0;

void delay_init(void)
{
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK_DIV8);

    fac_us = SystemCoreClock / 8000000;
    fac_ms = (u16)fac_us * 1000;
}

void delay_us(u32 num)
{
    u32 temp;

    SysTick->LOAD = num * fac_us;
    SysTick->VAL = 0x00;
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

    do {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16)));

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0X00;
}

void delay_ms(u32 num)
{
    u32 temp;

    SysTick->LOAD = (u32)num * fac_ms;
    SysTick->VAL = 0x00;
    SysTick->CTRL|= SysTick_CTRL_ENABLE_Msk;
    do {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16)));

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
    SysTick->VAL = 0X00;
}
