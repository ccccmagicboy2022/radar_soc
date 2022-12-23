#ifndef __XBR820_H__
#define __XBR820_H__

#include "csi_core.h"

typedef enum irq_number
{
    UART_RX_IRQ             = 1,
    UART_TX_IRQ             = 2,
    TIMER1_IRQ              = 3,
    TIMER2_IRQ              = 4,
    TIMER3_IRQ              = 5,
    TIMER4_IRQ              = 6,
    ADC_DONE_IRQ            = 7,
    IR_IRQ                  = 9,
    WDG_IRQ                 = 10,
    GPIO_PA0_IRQ            = 11,
    GPIO_PA1_IRQ            = 12,
    GPIO_PA2_IRQ            = 13,
    GPIO_PA3_IRQ            = 14,
    LIGHT_SENSOR_IRQ        = 17,
    FREQ_DET_IRQ            = 18,
    I2C_MASTER_IRQ          = 19,
    I2C_SLAVE_IRQ           = 20,
}irq_number_e;


typedef struct
{
    __IO uint32_t TX_ENABLE                 : 1;
    __IO uint32_t TX_INT_CLEAR              : 1;
    __IO uint32_t RX_ENABLE                 : 1;
    __IO uint32_t RX_INT_CLEAR              : 1;
    __IO uint32_t FIFO_RD                   : 1;
    __IO uint32_t FIFO_CLR                  : 1;
    uint32_t                                : 26;
} str_usart_ctl_field_t;

typedef struct
{
    __IO uint32_t BAUD_RATE                 : 16;
    uint32_t                                : 16;
} str_usart_br_field_t;

typedef struct
{
    __IO uint32_t TX_DATA                   : 8;
    uint32_t                                : 24;
} str_usart_td_field_t;

typedef struct
{
    __IO uint32_t RX_DATA                   : 8;
    uint32_t                                : 24;
} str_usart_rd_field_t;

typedef struct
{
    __IO uint32_t TI                        : 1;
    __I  uint32_t TX_STATE                  : 3;
    __IO uint32_t RI                        : 1;
    __IO uint32_t RX_STATE                  : 3;
    __IO uint32_t RX_ERROR                  : 2;
    __IO uint32_t RDATA_CNT                 : 4;
    uint32_t                                : 18;
} str_usart_st_field_t;

typedef struct
{
    __IO uint32_t VALUE                      : 8;
    __IO uint32_t INOUT                      : 8;
    uint32_t                                 : 8;
    uint32_t                                 : 8;
} str_gpio_ctl_field_t;

typedef struct
{
    __IO uint32_t PX_0                       : 4;
    __IO uint32_t PX_1                       : 4;
    __IO uint32_t PX_2                       : 4;
    __IO uint32_t PX_3                       : 4;
    __IO uint32_t PX_4                       : 4;
    __IO uint32_t PX_5                       : 4;
    __IO uint32_t PX_6                       : 4;
    __IO uint32_t PX_7                       : 4;
} str_gpio_ps_field_t;

typedef struct
{
    __IO uint32_t ADC_DIV                    : 12;
    __IO uint32_t TRI_MODE                   : 1;
    __IO uint32_t TRI_SRC                    : 1;
    uint32_t                                 : 18;
} str_adc_ctl_field_t;

typedef struct
{
    __IO uint32_t ADC_DELAY                  : 12;
    uint32_t                                 : 20;
} str_adc_delay_field_t;

typedef struct
{
    __IO uint32_t ADC_BEGIN                  : 11;
    uint32_t                                 : 5;
    __IO uint32_t ADC_END                    : 11;
    uint32_t                                 : 5;
} str_adc_range_field_t;

typedef struct {
    __IO uint32_t WDG_RST_EN                                      :1;
    __IO uint32_t WDG_INT_EN                                      :1;
    uint32_t                                                      :30;
} str_wdg_en_filed_t;

typedef struct {
    __IO uint32_t TIMER_EN                                        :1;
    __IO uint32_t TIMER_STA                                       :1;
    uint32_t                                                      :30;
} str_timer_ctrl_filed_t;

typedef struct {
    __IO uint32_t FREQ_DET_EN                                      :1;
    __IO uint32_t FREQ_DET_INT_EN                                  :1;
    __IO uint32_t FREQ_DET_STATUS                                  :1;
    uint32_t                                                       :29;
} str_freq_detect_ctrl_filed_t;

typedef struct {
    __IO uint32_t FREQ_DET_INTERVAL                                :24;
    uint32_t                                                       :8;
} str_freq_detect_cfg_filed_t;

typedef struct {
    __IO uint32_t FREQ_DET_VAL                                     :24;
    uint32_t                                                       :8;
} str_freq_detect_value_filed_t;

typedef struct {
    __IO uint32_t IR_INT_STA                                       :1;
    __IO uint32_t IR_CMP_ERR                                       :1;
    __I uint32_t IR_REPEAT                                        :1;
    uint32_t                                                      :29;
} str_ir_int_filed_t;

typedef struct {
    __IO uint32_t RF_IR_PHASE                                     :1;
    __IO uint32_t RF_ADDR_CMP_EN                                  :1;
    __IO uint32_t RF_DATA_CMP_EN                                  :1;
    __IO uint32_t IR_INT_EN                                       :1;
    uint32_t                                                      :28;
} str_ir_rf_filed_t;

typedef struct {
    __IO uint32_t RF_NOISE_TH                                     :8;
    uint32_t                                                      :8;
    __IO uint32_t RF_EDGE_TH                                      :13;
    uint32_t                                                      :3;
} str_ir_rf2_filed_t;


typedef struct
{
    union
    {
        __IO uint32_t CTL;
        str_usart_ctl_field_t CTL_f;
    };
    union
    {
        __IO uint32_t BR;
        str_usart_br_field_t BR_f;
    };
    union
    {
        __IO uint32_t TD;
        str_usart_td_field_t TD_f;
    };
    union
    {
        __IO uint32_t RD;
        str_usart_rd_field_t RD_f;
    };
    union
    {
        __IO uint32_t ST;
        str_usart_st_field_t ST_f;
    };
} brx820_uart_regdef;

typedef struct
{
    union
    {
        __IO uint32_t CTL;
        str_gpio_ctl_field_t CTL_f;
    };
    union
    {
        __IO uint32_t PS;
        str_gpio_ps_field_t PS_f;
    };
} brx820_gpio_regdef;

typedef struct
{
    union
    {
        __IO uint32_t CTL;
        str_adc_ctl_field_t CTL_f;
    };
    union
    {
        __IO uint32_t DELAY;
        str_adc_delay_field_t DELAY_f;
    };
    union
    {
        __IO uint32_t RANGE;
        str_adc_range_field_t RANGE_f;
    };
} brx820_adc_regdef;

/**
 * @brief WFG
 *
 */
typedef struct {
    union
    {
        __IO uint32_t WDG_CFG;
        str_wdg_en_filed_t WDG_CFG_f;
    };
    __IO uint32_t STC_WDG_CNT_REG;
} brx820_wdg_regdef;

typedef struct {
    union
    {
        __IO uint32_t TIMER_CTRL;
        str_timer_ctrl_filed_t TIMER_CTRL_f;
    };
    __IO uint32_t TIMER_INIT;
    __IO uint32_t TIMER_CNT;
} brx820_timer_regdef;

typedef struct {
    __IO uint32_t PWM_EN;
    __IO uint32_t PWM_CTR;
    __IO uint32_t PWM_DUTY;
} brx820_pwm_regdef;

typedef struct {
    union
    {
        __IO uint32_t FREQ_DETECT_CTRL;
        str_freq_detect_ctrl_filed_t FREQ_DETECT_CTRL_f;
    };
    union
    {
        __IO uint32_t FREQ_DETECT_CFG;
        str_freq_detect_cfg_filed_t FREQ_DETECT_CFG_f;
    };
    union
    {
        __IO uint32_t FREQ_DETECT_VALUE;
        str_freq_detect_value_filed_t FREQ_DETECT_VALUE_f;
    };
} brx820_freq_detect_regdef;

/**
 * @brief IR
 *
 */
typedef struct {
    union
    {
        __IO uint32_t IR_CMD;
        str_ir_int_filed_t IR_CMD_f;
    };
    __IO uint32_t IR_READ_DATA;
    union
    {
        __IO uint32_t IR_CMP;
        str_ir_rf_filed_t IR_CMP_f;
    };
    union
    {
        __IO uint32_t IR_RF2;
        str_ir_rf2_filed_t IR_RF2_f;
    };
    __IO uint32_t IR_9MS_COUNT :18;
    uint32_t                   :14;
    __IO uint32_t IR_4P5_COUNT :18;
    uint32_t                   :14;
    __IO uint32_t IR_1P69_COUNT:18;
    uint32_t                   :14;
    __IO uint32_t IR_2P25_COUNT:18;
    uint32_t                   :14;
} brx820_ir_regdef;

typedef struct {
    __IOM uint32_t NACK              :1;
    __IOM uint32_t FINISH            :1;
    __IOM uint32_t TIME_OUT          :1;
    __IOM uint32_t ONE_BYTE_FINISH   :1;
    __IOM uint32_t                     :28;
} I2C_INT;

typedef struct {
    __IM uint32_t NACK             :1;
    __IM uint32_t FINISH           :1;
    __IM uint32_t TIME_OUT         :1;
    __IM uint32_t IDLE             :1;
    __IM uint32_t ONE_BYTE_FINISH  :1;
    uint32_t                       :3;
    __IM uint32_t DATA_NUM         :8;
    uint32_t                      :16;
} I2C_status_t;

typedef struct {
    __IOM uint32_t SLAVE_ADDR       :8;
    uint32_t                       :24;

    __IOM uint32_t DATA_LENTH       :8;
    uint32_t                       :24;

    __IOM uint32_t CMD              :4;
    __IOM uint32_t CMD_W            :1;
    uint32_t                       :27;

    __IOM uint32_t WAIT_TIME       :16;
    uint16_t                       :16;

    __IOM uint32_t CPU_CLK_STR_EN   :1;
    __IOM uint32_t CPU_LAST_ACK_EN  :1;
    uint32_t                       :30;

    __IOM uint32_t REG_ADDR        :16;
    uint32_t                       :16;

    __IOM uint32_t T_DATA0_SLOT0	:8;
	__IOM uint32_t T_DATA0_SLOT1	:8;
	__IOM uint32_t T_DATA0_SLOT2	:8;
	__IOM uint32_t T_DATA0_SLOT3	:8;
    __IOM uint32_t T_DATA1_SLOT4	:8;
	__IOM uint32_t T_DATA1_SLOT5	:8;
	__IOM uint32_t T_DATA1_SLOT6	:8;
	__IOM uint32_t T_DATA1_SLOT7	:8;

    __IOM uint32_t R_DATA0;
    __IOM uint32_t R_DATA1;

    union {
        __IM uint32_t STATUS;
        I2C_status_t STATUS_f;
    };

    union
    {
        __IO uint32_t INT_EN;
        I2C_INT INT_EN_f;
    };

	union
	{
		__IO uint32_t INT_CLEAR;
		I2C_INT INT_CLEAR_f;
	};

    __IOM uint32_t CLK_DIV        :16;
    uint32_t                       :16;

    __IOM uint32_t CLK_EN          :1;
    uint32_t                      :31;
} brx820_i2c_master_regdef;

typedef struct {
    __IO uint32_t SLAVE_ADDR                                       :8;
    uint32_t                                                      :24;
} i2c_slave_addr_field_t;

typedef struct {
    __IO uint32_t EN_SLAVE                                         :1;
    uint32_t                                                      :31;
} i2c_slave_en_slave_field_t;

typedef struct {
    __I uint32_t RECV_DATA                                         :8;
    __I uint32_t RECV_ADDR                                         :8;
    uint32_t                                                      :16;
} i2c_slave_recv_data_field_t;

typedef struct
{
    __IO uint32_t SEND_DATA                                        :8;
    uint32_t                                                      :24;
} i2c_slave_send_data_field_t;

typedef struct
{
    __I uint32_t RW                                               :1;
    __I uint32_t NACK                                             :1;
    __I uint32_t STOP                                             :1;
    __I uint32_t ADDR                                             :1;
    __I uint32_t RW_DONE                                          :1;
    uint32_t                                                     :27;
} i2c_slave_sr_field_t;

typedef struct
{
    __IO uint32_t CLR_RW                                          :1;
    __IO uint32_t CLR_NACK                                        :1;
    __IO uint32_t CLR_STOP                                        :1;
    __IO uint32_t CLR_ADDR                                        :1;
    __IO uint32_t CLR_INT                                         :1;
    uint32_t                                                      :3;
    __IO uint32_t RW_MASK                                         :1;
    __IO uint32_t NACK_MASK                                       :1;
    __IO uint32_t STOP_MASK                                       :1;
    __IO uint32_t ADDR_MASK                                       :1;
    uint32_t                                                     :20;
} i2c_slave_cr_field_t;

typedef struct
{
    __IO uint32_t RESETN                                          :1;
    __IO uint32_t TRIM                                            :2;
    uint32_t                                                      :29;	
}light_sensor_cr1_field_t;

typedef struct
{
	__IO uint32_t INT_EN                                          :1;
	__IO uint32_t INT_STA                                         :1;
	__I	 uint32_t FLAG											  :1;
	uint32_t                                                      :1;
	__IO uint32_t INTERVAL_SELECT							      :3;
	uint32_t                                                      :1;
	__IO uint32_t DELAY											  :7;
	uint32_t                                                      :17;
}light_sensor_cr2_field_t;

typedef struct
{
    __IO uint32_t SEL                                             :5;
    uint32_t                                                      :3;
	__IO uint32_t START_WAIT									  :8;
	__IO uint32_t IO_TRIGGER									  :1;
	__IO uint32_t LATCH_EN										  :1;
	uint32_t                                                      :14;
}frame_cr1_field_t;

typedef struct
{
    __IO uint32_t T1_VALUE                                        :27;
    uint32_t                                                      :5;	
}frame_t1_field_t;

typedef struct
{
    __IO uint32_t T2_VALUE                                        :24;
    uint32_t                                                      :8;	
}frame_t2_field_t;

/**
 * @brief I2C slave
 *
 */
typedef struct {
    union
    {
        __IO uint32_t SLAVE_ADDR;
        i2c_slave_addr_field_t SLAVE_ADDR_f;
    };
    union
    {
        __IO uint32_t EN_SLAVE;
        i2c_slave_en_slave_field_t EN_SLAVE_f;
    };
    union
    {
        __IO uint32_t RECV_DATA;
        i2c_slave_recv_data_field_t RECV_DATA_f;
    };
    union
    {
        __IO uint32_t SEND_DATA;
        i2c_slave_send_data_field_t SEND_DATA_f;
    };
    union
    {
        __I uint32_t SR;
        i2c_slave_sr_field_t SR_f;
    };
    union
    {
        __IO uint32_t CR;
        i2c_slave_cr_field_t CR_f;
    };
} brx820_i2c_slave_regdef;

typedef struct {
    union
    {
        __IO uint32_t CR1;
        light_sensor_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t CR2;
        light_sensor_cr2_field_t CR2_f;
    };
} brx820_light_sensor_regdef;

typedef struct {
    union
    {
        __IO uint32_t CR1;
        frame_cr1_field_t CR1_f;
    };
    union
    {
        __IO uint32_t T1;
		frame_t1_field_t T1_f;
    };
    union
    {
        __IO uint32_t T2;
		frame_t2_field_t T2_f;
    };
} brx820_frame_regdef;

#define SYSTEM_CLOCK 40000000

#define BRX820_UART        ((brx820_uart_regdef *)(0x1f040000UL))
#define BRX820_GPIO_PA     ((brx820_gpio_regdef *)(0x1f000100UL))
#define BRX820_GPIO_PB     ((brx820_gpio_regdef *)(0x1f000120UL))
#define BRX820_DSP_ADC     ((brx820_adc_regdef *)(0x1f010000UL))
#define BRX820_WDG         ((brx820_wdg_regdef *)(0x1f020010UL))
#define BRX820_TIMER1      ((brx820_timer_regdef *)(0x1f020020UL))
#define BRX820_TIMER2      ((brx820_timer_regdef *)(0x1f020040UL))
#define BRX820_TIMER3      ((brx820_timer_regdef *)(0x1f020060UL))
#define BRX820_TIMER4      ((brx820_timer_regdef *)(0x1f020080UL))
#define BRX820_PWM1        ((brx820_pwm_regdef *)(0x1f020100UL))
#define BRX820_PWM2        ((brx820_pwm_regdef *)(0x1f020120UL))
#define BRX820_PWM3        ((brx820_pwm_regdef *)(0x1f020140UL))
#define BRX820_PWM4        ((brx820_pwm_regdef *)(0x1f020160UL))
#define BRX820_PWM5        ((brx820_pwm_regdef *)(0x1f020180UL))
#define BRX820_FREQ_DETECT ((brx820_freq_detect_regdef *)(0x1f020200UL))
#define BRX820_IR          ((brx820_ir_regdef *)(0x1f030000UL))
#define BRX820_I2C_MASTER  ((brx820_i2c_master_regdef *)(0x1f050000UL))
#define BRX820_I2C_SLAVE   ((brx820_i2c_slave_regdef *)(0x1f060000UL))
#define BRX820_LIGHT_SENSOR ((brx820_light_sensor_regdef *)(0x1f000090UL))
#define BRX820_FRAME		((brx820_frame_regdef *)(0x1f000200UL))

#endif
