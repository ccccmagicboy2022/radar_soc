/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include "jtag2.h"
#include "delay.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
void jtag2_output_clk(GPIO_PinState val);

/* Private macro -------------------------------------------------------------*/

#define CLK_H()                         (jtag2_output_clk(GPIO_PIN_SET))
#define CLK_L()                         (jtag2_output_clk(GPIO_PIN_RESET))
#define DAT_H()                         (jtag2_output_data(GPIO_PIN_SET))
#define DAT_L()                         (jtag2_output_data(GPIO_PIN_RESET))

//#define GET_DAT(a)                      (a = jtag2_input_data(), a)

#define DELAY()                         (delay_us(1))
#define MAX_WAIT_TIMEOUT                (100u)

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void enable_clk_output(void);
void enable_data_output(void);
void enable_data_input(void);

/* Private functions ---------------------------------------------------------*/
#if 0
void RCC_config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
}

/**
 * @brief PA1 CLK, PA5 TMS, PB6 OE0, PB7 DIR0
 *          DIR1 PA7, OE1 PB11
 * 
 */
void GPIO_config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* PA1 CLK */
    /* PA5 TMS */
    /* PA7 DIR1 */
    GPIO_InitStructure.GPIO_Pin = CLK | TMS | DIR1 | TRST;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* PB6 OE0 */
    /* PB7 DIR0 */
    /* PB11 OE1 */
    GPIO_InitStructure.GPIO_Pin = OE0 | DIR0 | OE1 | NRST;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}
#endif

void set_data_port_input(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.Pin = TMS;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void set_clk_port_input(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.Pin = CLK;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
}
void set_clk_port_output(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.Pin = CLK;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void set_data_port_output(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.Pin = TMS;
    GPIO_InitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void jtag2_init(void)
{
//    RCC_config();
//    GPIO_config();
    disable_clk_data_output();
    // enable_clk_output();
    // enable_data_output();
    HAL_GPIO_WritePin(GPIOB, NRST, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, TRST, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_15, GPIO_PIN_RESET);
}

void reset_mcu(void)
{
    HAL_GPIO_WritePin(GPIOB, NRST, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, TRST, GPIO_PIN_RESET);
    delay_ms(100);
    HAL_GPIO_WritePin(GPIOB, NRST, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA, TRST, GPIO_PIN_SET);
}

void enable_clk_output(void)
{
    HAL_GPIO_WritePin(GPIOB, OE0, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, DIR0, GPIO_PIN_SET);
    DELAY();
}

void enable_data_output(void)
{
    HAL_GPIO_WritePin(GPIOB, OE1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, DIR1, GPIO_PIN_SET);
    DELAY();
}

void enable_clk_input(void)
{
    HAL_GPIO_WritePin(GPIOB, OE0, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, DIR0, GPIO_PIN_RESET);
    DELAY();
}

void enable_data_input(void)
{
    HAL_GPIO_WritePin(GPIOB, OE1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, DIR1, GPIO_PIN_RESET);
    DELAY();
}

void disable_clk_data_output(void)
{
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);

    HAL_GPIO_WritePin(GPIOB, OE0, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, OE1, GPIO_PIN_SET);
    DELAY();

    // enable_clk_input();
    // enable_data_input();
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1|GPIO_PIN_5, GPIO_PIN_SET);
    set_clk_port_output();
    set_data_port_output();
}

void enable_clk_data_output(void)
{
    enable_clk_output();
    enable_data_output();
}

void jtag2_output_clk(GPIO_PinState val)
{
    HAL_GPIO_WritePin(GPIOA, CLK, val);
}

void jtag2_output_data(GPIO_PinState val)
{
    HAL_GPIO_WritePin(GPIOA, TMS, val);
}

uint8_t jtag2_input_data(void)
{
    uint8_t tmp;

    tmp = HAL_GPIO_ReadPin(GPIOA, TMS);

    return tmp;
}

void jtag2_send_data(uint32_t data, uint8_t len)
{
    int i;

    for (i = 0; i < len; i++) {
        CLK_H();
        DELAY();
        if (data & 0x01)
            DAT_H();
        else
            DAT_L();
        data >>= 1;
        CLK_L();
        DELAY();
    }
}

void jtag2_read_data(uint32_t *data, uint8_t len)
{
    int i;
    uint8_t tmp;
    uint32_t tmp_32 = 0;

    for (i = 0; i < len; i++) {
        CLK_H();
        DELAY();
        CLK_L();
        DELAY();
        CLK_H();
        DELAY();
        tmp = jtag2_input_data();
        tmp_32 |= ((uint32_t)tmp << i);
        DELAY();
    }

    *data = tmp_32;
}

int calc_parity(uint32_t data, uint8_t len)
{
    int i, num = 0;

    for (i = 0; i < len; i++) {
        if (data & 0x01)
            num++;
        data >>= 1;
    }

    if (num % 2)
        return 0;

    return 1;
}

void jtag2_write_cmd(uint8_t RS, uint32_t data, uint8_t len)
{
    int res;

    /* write */

    /* start 0 */
    jtag2_send_data(0, 1);
    /* R/W  0 */
    jtag2_send_data(0, 1);
    /* RS */
    jtag2_send_data(RS, 2);
    /* TRN */
    jtag2_send_data(1, 1);
    /* DATA */
    jtag2_send_data(data, len);
    /* PAR */
    res = calc_parity(data, len);
    jtag2_send_data(res, 1);
    /* TRN */
    jtag2_send_data(1, 1);
}

void jtag2_idle(void)
{
    int i;

    DAT_H();
    for (i = 0; i < 4; i++) {
        CLK_H();
        DELAY();
        CLK_L();
        DELAY();
    }
    DAT_H();
    CLK_H();
}

void jtag2_read_had_data(uint32_t *data)
{
    uint32_t tmp;

    /* start 0 */
    jtag2_send_data(0, 1);
    /* R/W  1 */
    jtag2_send_data(1, 1);
    /* RS */
    jtag2_send_data(RS_DATA, 2);
    /* TRN */
    jtag2_send_data(1, 1);

    // jtag2_send_data(0, 1);
    // jtag2_send_data(1, 1);

    enable_data_input();
    set_data_port_input();
    /* SYN */
    jtag2_read_data(&tmp, 1);
    /* DATA */
    jtag2_read_data(&tmp, 32);
    *data = tmp;
    /* PAR */
    jtag2_read_data(&tmp, 1);
    /* TRN */
    jtag2_read_data(&tmp, 1);
}

void jtag2_read_had(uint32_t cmd, uint8_t len, uint32_t *data)
{
    enable_clk_output();
    enable_data_output();

    jtag2_idle();
    jtag2_write_cmd(RS_HACR, cmd, len);

    /* read */
    jtag2_read_had_data(data);

    enable_data_output();
    set_data_port_output();

    jtag2_idle();
}

void jtag2_write_had(uint32_t cmd, uint8_t len, uint32_t data)
{

    enable_clk_output();
    enable_data_output();
    set_data_port_output();

    jtag2_write_cmd(RS_HACR, cmd, len);
    jtag2_write_cmd(RS_DATA, data, 32);
}

void jtag2_exit_debug(void)
{
    uint32_t result;

    jtag2_read_had(RD_CSR, 8, &result);
    result |= EN_FDB;
    jtag2_write_had(WR_CSR, 8, result);
    jtag2_read_had(RD_HCR, 8, &result);
    result &= 0xFFDF5FFF;
    jtag2_write_had(WR_HCR, 8, result);

    enable_clk_output();
    enable_data_output();
    set_data_port_output();

    jtag2_write_cmd(RS_HACR, WR_RUN, 8);
    jtag2_write_cmd(RS_DATA, result, 32);
}

void jtag2_read_gpr(uint32_t IR, uint32_t *data)
{
    uint32_t backup, result;

    jtag2_read_had(RD_HCR, 8, &result);
    result |= EN_DEBUG;
    jtag2_write_had(WR_HCR, 8, result);
    jtag2_read_had(RD_CSR, 8, &backup);
    result = backup & (~EN_FFY);
    jtag2_write_had(WR_CSR, 8, result);
    jtag2_write_had(WR_IR, 8, IR);
    jtag2_read_had(RD_WBBR, 8, data);
    jtag2_write_had(WR_CSR, 8, backup);
}

void jtag2_write_gpr(uint32_t IR, uint32_t data)
{
    uint32_t result, backup;

    jtag2_read_had(RD_HCR, 8, &result);
    result |= EN_DEBUG;
    jtag2_write_had(WR_HCR, 8, result);
    jtag2_read_had(RD_CSR, 8, &backup);
    result = backup | EN_FFY;
    jtag2_write_had(WR_CSR, 8, result);
    jtag2_write_had(WR_WBBR, 8, data);
    jtag2_write_had(WR_IR, 8, IR);
    jtag2_write_had(WR_CSR, 8, backup);
}

void jtag2_ddc_download(uint32_t addr, uint32_t *data, uint32_t len)
{
    int i;
    uint32_t result, CSR_backup, HCR_backup, X1, X2;

    jtag2_read_gpr(IR_X1, &X1);
    jtag2_read_gpr(IR_X2, &X2);
    jtag2_read_had(RD_CSR, 8, &CSR_backup);
    // jtag2_read_had(RD_HCR, 8, &HCR_backup);
    // HCR_backup &= 0xFFEFFFFF;
    // jtag2_write_had(WR_HCR, 8, HCR_backup);
    jtag2_read_had(RD_HCR, 8, &HCR_backup);
    result = HCR_backup | EN_DEBUG;
    jtag2_write_had(WR_HCR, 8, result);
    result |= EN_DDC;
    jtag2_write_had(WR_HCR, 8, result);
    jtag2_write_had(WR_DADDR, 8, addr);

    for (i = 0; i < len;) {
        result = *data++;
        jtag2_write_had(WR_DDATA, 8, result);
        i += 4;
    }
    jtag2_write_had(WR_HCR, 8, HCR_backup);
    jtag2_write_had(WR_CSR, 8, CSR_backup);
    jtag2_write_gpr(IR_X1, X1);
    jtag2_write_gpr(IR_X2, X2);
}

void jtag2_read_memory(uint32_t addr, uint32_t *data)
{
    uint32_t X1, X2, backup, result;

    jtag2_read_had(RD_HCR, 8, &result);
    result |= EN_DEBUG;
    jtag2_write_had(WR_HCR, 8, result);
    jtag2_read_had(RD_CSR, 8, &backup);
    jtag2_read_gpr(IR_X1, &X1);
    jtag2_read_gpr(IR_X2, &X2);
    jtag2_write_gpr(IR_X1, addr);
    result = backup & (~EN_FFY);
    jtag2_write_had(WR_CSR, 8, result);
    jtag2_write_had(WR_IR, 8, IR_LB_X2_X1);
    jtag2_read_gpr(IR_X2, data);
    jtag2_write_gpr(IR_X1, X1);
    jtag2_write_gpr(IR_X2, X2);
    jtag2_write_had(WR_CSR, 8, backup);
}

int wait_mcu_idle(void)
{
    uint32_t result;
    int i = 0, ret = 0;

    while (1) {
        jtag2_read_had(RD_HSR, 8, &result);
        if ((result & 0x03) != 0 || i >= MAX_WAIT_TIMEOUT)
            break;
        delay_ms(1);
        i++;
    }

    if (i >= MAX_WAIT_TIMEOUT)
        ret = -1;

    return ret;
}

void jtag2_write_word(uint32_t addr, uint32_t data)
{
    uint32_t backup, X1, X2, result, HCR_backup;

    jtag2_read_had(RD_HCR, 8, &HCR_backup);
    result = HCR_backup | EN_DEBUG;
    jtag2_write_had(WR_HCR, 8, result);
    jtag2_read_had(RD_CSR, 8, &backup);
    jtag2_read_gpr(IR_X1, &X1);
    jtag2_read_gpr(IR_X2, &X2);
    jtag2_write_gpr(IR_X1, addr);
    jtag2_write_gpr(IR_X2, data);
    result = backup & (~EN_FFY);
    jtag2_write_had(WR_CSR, 8, result);
    jtag2_write_had(WR_IR, 8, IR_SW_X2_X1);
    jtag2_write_gpr(IR_X1, X1);
    jtag2_write_gpr(IR_X2, X2);
    jtag2_write_had(WR_CSR, 8, backup);
    jtag2_write_had(WR_HCR, 8, HCR_backup);
}

uint32_t jtag2_read_word(uint32_t addr)
{
    int i;
    uint32_t result = 0, val;

    for (i = 0; i < 4; i++) {
        jtag2_read_memory(addr + i, &val);
        result |= (val & 0xff) << (i * 8);
    }

    return result;
}
