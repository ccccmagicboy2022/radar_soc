#ifndef __JTAG2_H__
#define __JTAG2_H__

#include "stdint.h"

#define CLK                             (GPIO_PIN_1)
#define TMS                             (GPIO_PIN_5)
#define DIR1                            (GPIO_PIN_7)
#define OE0                             (GPIO_PIN_6)
#define DIR0                            (GPIO_PIN_7)
#define OE1                             (GPIO_PIN_13)

#define TRST                            (GPIO_PIN_0)
#define NRST                            (GPIO_PIN_8)

/* Jtag2 */
#define RS_HACR                         (0x02)
#define RS_CSR                          (0x15)
#define RS_DATA                         (0x03)

/* HACR */
#define WR_WBBR                         (0x11)
#define RD_WBBR                         (0x91)

#define RD_ID                           (0x82)

#define WR_HCR                          (0x0D)
#define RD_HCR                          (0x8D)

#define WR_CSR                          (0x15)
#define RD_CSR                          (0x95)

#define WR_IR                           (0x54)

#define WR_DADDR                        (0x18)
#define WR_DDATA                        (0x19)

#define WR_PC_RUN                       (0x73)
#define WR_PC                           (0x13)
#define WR_RUN                          (0x6C)
#define RD_PC                           (0x93)

/* HCR */
#define EN_DEBUG                        (0x8000)
#define EN_DDC                          (0x100000)
#define EN_ONLY_DDC                     (0x100000)
#define CLR_DEBUG                       (0x0)

/* HSR */
#define RD_HSR                          (0x8E)

/* CSR */
#define EN_FFY                          (0x100)
#define EN_FDB                          (0x80)

/* IR */
#define IR_X1                           (0x8086)
#define IR_X2                           (0x810a)
#define IR_LB_X2_X1                     (0x00008103)
#define IR_AUIPC                        (0x00000097)
#define IR_SW_X2_X1                     (0x0020a023)


void jtag2_init(void);
void jtag2_read_had(uint32_t cmd, uint8_t len, uint32_t *data);
void jtag2_write_had(uint32_t cmd, uint8_t len, uint32_t data);
void jtag2_write_gpr(uint32_t IR, uint32_t data);
void jtag2_read_gpr(uint32_t IR, uint32_t *data);
void jtag2_ddc_download(uint32_t addr, uint32_t *data, uint32_t len);
void jtag2_read_memory(uint32_t addr, uint32_t *data);
void reset_mcu(void);
void jtag2_exit_debug(void);
int wait_mcu_idle(void);
void jtag2_write_word(uint32_t addr, uint32_t data);
uint32_t jtag2_read_word(uint32_t addr);
void disable_clk_data_output(void);
void enable_clk_data_output(void);
#endif
