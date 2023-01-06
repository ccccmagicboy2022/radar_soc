#ifndef __PHM320_H__
#define __PHM320_H__

#include "csi_core.h"

typedef enum irq_number
{
    INT_SOFT                 = 3,
    INT_SYS_TIMER            = 7,
    INT_EXTERNAL            = 11,
    INT_000                 = 16,
    INT_001                 = 17,
    INT_002                 = 18,
    INT_003                 = 19,
    INT_004                 = 20,
    INT_005                 = 21,
    INT_006                 = 22,
    INT_007                 = 23,
}irq_number_e;

/*============================================================================
 * Description :
 */
typedef struct {
/*	
    __IO uint32_t                  :19;
    __IO uint32_t RF1_EN           :1;
    __IO uint32_t                  :3;
    __IO uint32_t RF2_EN           :1;
    __IO uint32_t                  :7;
    __IO uint32_t RF4_EN           :1;
*/	
	__IO uint32_t    RFLDO_OSC      :32;
}str_analog_a_t;

/*============================================================================
 * Description :
 */
typedef struct {
    __IO uint32_t RF1_DELAY        :7;
    __IO uint32_t RF_EN_SEL        :1;
    __IO uint32_t RF2_DELAY        :7;
    __IO uint32_t                  :9;
    __IO uint32_t PGA_DC_TRIM      :6;
    __IO uint32_t PGA_BYPASS       :1;
    __IO uint32_t PGA_EN           :1;
}str_analog_b_t;

/*============================================================================
 * Description :
 */
typedef struct {
    __IO uint32_t ADC_CH_MUX       :3;
    __IO uint32_t ADC_EN           :1;
    __IO uint32_t ADC_MODE         :1;
    __IO uint32_t ADC_DATA_CLRN    :1;
    __IO uint32_t ADC_CLK_DIV      :1;
    __IO uint32_t ADC_CLK_SEL      :1;
    __IO uint32_t ADC_VREF_SEL     :2;
    __IO uint32_t ADC_VCM_TRIM     :2;
    __IO uint32_t ADC_VREF_TRIM    :4;
    __IO uint32_t ADC_SAMPLE_CNT   :8;
    __IO uint32_t PGA_GAIN         :4;
	__IO uint32_t                  :4;
}str_adc_ctl_t;

/*============================================================================
 * Description :
 */
typedef struct {
    __IO uint32_t OSC16M_TRIM       :8;
    __IO uint32_t IREF_TRIM         :3;
    __IO uint32_t LDO_DIG_TRIM      :2;
    __IO uint32_t TEST_SEL          :2;
    __IO uint32_t TEST_EN           :1;
    __IO uint32_t RFLDO1_TRIM       :3;
    __IO uint32_t RF1_EN            :1;
    __IO uint32_t RFLDO2_TRIM       :3;
    __IO uint32_t RF2_EN            :1;
    __IO uint32_t RFLDO3_TRIM       :3;
    __IO uint32_t RF3_EN            :1;
    __IO uint32_t PGA_GAIN          :3;
    __IO uint32_t RF_EN_SEL         :1;
}str_a_t;

/*============================================================================
 * Description :
 */
typedef struct {
    __IO uint32_t RF1_DELAY       :7;
    __IO uint32_t                 :1;
    __IO uint32_t RF2_DELAY       :7;
    __IO uint32_t                 :1;
    __IO uint32_t RF3_DELAY       :7;
    __IO uint32_t                 :1;
    __IO uint32_t PGA_DC_TRIM     :6;
    __IO uint32_t PGA_BYPASS      :1;
    __IO uint32_t PGA_EN          :1;
}str_b_t;

/*============================================================================
 * Description :
 */
typedef struct {
    __IO uint32_t DIV       :12;
    __IO uint32_t RESET     :1;
    __IO uint32_t RESETALL  :1;
    __IO uint32_t           :2;
    __IO uint32_t MUX1      :1;
    __IO uint32_t MUX2      :1;
    __IO uint32_t MUX3      :1;
    __IO uint32_t MUX4      :1;
    __IO uint32_t MUX5      :1;
    __IO uint32_t MUX6      :2;
    __IO uint32_t MUX7      :1;
    __IO uint32_t           :8;
}str_top_ctla_t;

/*============================================================================
 * Description :
 */
typedef struct {
    __IO uint32_t          :1;
    __IO uint32_t          :3;
    __IO uint32_t MUX1     :2;
    __IO uint32_t MUX2     :2;
    __IO uint32_t MUX3     :2;
    __IO uint32_t MUX4     :2;
    __IO uint32_t MUX5     :2;
    __IO uint32_t          :2;
    __IO uint32_t ADC_TRG  :1;
    __IO uint32_t ADC_TRG_SEL  :1;
    __IO uint32_t          :14;
}str_top_ctlb_t;

/*============================================================================
 * Description :
 */
typedef struct {
    __IO uint32_t DIV      :8;
    __IO uint32_t SAMPLE   :3;
    __IO uint32_t BWSEL    :1;
    __IO uint32_t BWEN     :1;
    __IO uint32_t DCMODE   :1;
    __IO uint32_t BPEN     :1;
    __IO uint32_t DCTIME   :2;
    __IO uint32_t DCTIMES  :2;
    __IO uint32_t         :13;
}str_bb_ctl_t;

/*============================================================================
 * Description :
 */
typedef struct {
    __IO uint32_t GPIO1    :1;
    __IO uint32_t GPIO2    :1;
    __IO uint32_t GPIO3    :1;
    __IO uint32_t GPIO4    :1;
    __IO uint32_t GPIO5    :1;
    __IO uint32_t GPIO6    :1;
    __IO uint32_t GPIO7    :1;
    __IO uint32_t GPIO8    :1;
    __IO uint32_t         :24;
}str_gpio_val_t;

/*============================================================================
 * Description :
 */
typedef struct {
    __IO uint32_t GPIO1    :1;
    __IO uint32_t GPIO2    :1;
    __IO uint32_t GPIO3    :1;
    __IO uint32_t GPIO4    :1;
    __IO uint32_t GPIO5    :1;
    __IO uint32_t GPIO6    :1;
    __IO uint32_t GPIO7    :1;
    __IO uint32_t GPIO8    :1;
    __IO uint32_t         :24;
}str_gpio_mask_t;

/*============================================================================
 * Description :
 */
typedef struct {
    __IO uint32_t P0       :1;
    __IO uint32_t P1       :1;
    __IO uint32_t P2       :1;
    __IO uint32_t P3       :1;
    __IO uint32_t ADC      :1;
    __IO uint32_t BP       :1;
    __IO uint32_t         :26;
}str_top_int_mask_t;

/*============================================================================
 * Description :
 */
typedef struct {
    __IO uint32_t P0       :3;
    __IO uint32_t P1       :3;
    __IO uint32_t P2       :3;
    __IO uint32_t P3       :3;
    __IO uint32_t ADC      :3;
    __IO uint32_t BP       :3;
    __IO uint32_t         :14;
} str_top_int_mode_t;

/*============================================================================
 * Description :
 */
typedef struct {
    __IO uint32_t P0       :1;
    __IO uint32_t P1       :1;
    __IO uint32_t P2       :1;
    __IO uint32_t P3       :1;
    __IO uint32_t ADC      :1;
    __IO uint32_t BP       :1;
    __IO uint32_t OUT      :1;
    __IO uint32_t         :25;
} str_top_int_clean_t;

/*============================================================================
 * Description :
 */
typedef struct {
    __IO uint32_t P0       :1;
    __IO uint32_t P1       :1;
    __IO uint32_t P2       :1;
    __IO uint32_t P3       :1;
    __IO uint32_t ADC      :1;
    __IO uint32_t BP       :1;
    __IO uint32_t         :26;
} str_top_int_flag_t;

typedef struct {
    uint32_t RESERVED1[4];
    union {
        __IO uint32_t ANALOG_A;
        str_analog_a_t ANALOG_A_BITS;
    };
    union {
        __IO uint32_t ANALOG_B;
        str_analog_b_t ANALOG_B_BITS;
    };
    union {
        __IO uint32_t ADC_CTL;
        str_adc_ctl_t ADC_CTL_BITS;
    };
    union {
        __IO uint32_t TOP_CTLA;
        str_top_ctla_t TOP_CTLA_BITS;
    };
    union {
        __IO uint32_t TOP_CTLB;
        str_top_ctlb_t TOP_CTLB_BITS;
    };
    union {
        __IO uint32_t BB_CTL;
        str_bb_ctl_t BB_CTL_BITS;
    };
    __IO uint32_t DC_SET;
    __IO uint32_t DET_TH;
    __IO uint32_t AC_NOISE;
    __IO uint32_t ON_TIME;
    __IO uint32_t OFF_TIME;
    uint32_t RESERVED2[17];
    __I  uint32_t ADC_DATA;
    __I  uint32_t AC_SUM;
    __I  uint32_t DC_SUM;
    __I  uint16_t DC_AVG;
    __I  uint16_t DC_AVG_INIT;
    __I  uint16_t DC_AVG_USE;
    __I  uint16_t DC_AVG_TIMES;
    uint32_t RESERVED3[11];
    union {
        __IO uint32_t GPIO_VAL;
        str_gpio_val_t GPIO_VAL_BITS;
    };
    union {
        __IO uint32_t GPIO_OUT_EN;
        str_gpio_mask_t GPIO_OUT_EN_BITS;
    };
    union {
        __IO uint32_t TOP_INT_MASK;
        str_top_int_mask_t TOP_INT_MASK_BITS;
    };
    union {
        __IO uint32_t TOP_INT_MODE;
        str_top_int_mode_t TOP_INT_MODE_BITS;
    };
    union {
        __IO uint32_t TOP_INT_CLEAR;
        str_top_int_clean_t TOP_INT_CLEAR_BITS;
    };
    union {
        __IO uint32_t TOP_INT_FLAG;
        str_top_int_flag_t TOP_INT_FLAG_BITS;
    };
} phm320_top_regdef;

typedef struct {
    __IO uint32_t MODE     :4;
    __IO uint32_t         :28;
} str_mtpc_mode_t;

typedef struct {
    union {
        __IO uint32_t MTPC_CTL;
        str_mtpc_mode_t MTPC_CTL_BITS;
    };
    __O uint32_t ADDR;
    __O uint32_t DATA;
    __I uint32_t FINISH;
} phm320_mtpc_regdef;

/*============================================================================
 * IR Description :
 */
typedef struct {
    __IM uint32_t ir_int                 :1;
    __IM uint32_t ir_repeat              :1;
    __IM uint32_t ir_cmp_err             :1;
    __IM uint32_t                        :29;
    __IM uint32_t                        :32;
    __IOM uint32_t rf_int_clr            :1;
    __IOM uint32_t rf_cmp_clr            :1;
    __IM uint32_t                        :30;
    __IM  uint32_t ir_data;
} IR_reg_t;

/*============================================================================
 * STC Description :
 */
typedef union {
    __IOM uint32_t encfg;
    struct {
        __IOM uint32_t stc_cnt_en        :1;
        __IOM uint32_t wdg_en            :1;
        __IOM uint32_t wdg_rst_en        :1;
        __IM uint32_t                    :1;
        __IOM uint32_t tmr0_en           :1;
        __IOM uint32_t tmr1_en           :1;
        __IOM uint32_t tmr2_en           :1;
        __IOM uint32_t tmr3_en           :1;
        __IOM uint32_t tmr0_clr          :1;
        __IOM uint32_t tmr1_clr          :1;
        __IOM uint32_t tmr2_clr          :1;
        __IOM uint32_t tmr3_clr          :1;

        __IOM uint32_t pwm0_en           :1;
        __IOM uint32_t pwm1_en           :1;
        __IOM uint32_t pwm2_en           :1;
        __IOM uint32_t pwm3_en           :1;
        __IOM uint32_t pwm4_en           :1;
        __IM uint32_t                    :15;
    } bits;
} STC_enable_st;

typedef union {
    __IOM uint32_t encfg;
    struct {
        __IM uint32_t                    :12;
        __IOM uint32_t	pwm0_en          :1;
        __IOM uint32_t	pwm1_en          :1;
        __IOM uint32_t	pwm2_en          :1;
        __IOM uint32_t	pwm3_en          :1;
        __IOM uint32_t	pwm4_en          :1;
        __IM uint32_t                    :15;
    } bits;
} PWM_enable_st;

typedef struct {
    __IOM PWM_enable_st	enable;
    __IM uint32_t  RESERVED[15];
    __IOM uint32_t pwm_freq_ctrl1;
    __IOM uint32_t pwm_freq_ctrl2;
    __IOM uint32_t pwm_freq_ctrl3;
    __IOM uint32_t pwm_freq_ctrl4;
    __IOM uint32_t pwm_freq_ctrl5;
    __IOM uint32_t pwm_freq_duty1;
    __IOM uint32_t pwm_freq_duty2;
    __IOM uint32_t pwm_freq_duty3;
    __IOM uint32_t pwm_freq_duty4;
    __IOM uint32_t pwm_freq_duty5;
} PWM_reg_t;

typedef struct {
    //__IOM uint32_t	enable;
    __IOM STC_enable_st	enable;
    __IOM uint32_t	wdg_cnt;
    __IOM uint32_t	tmr0_init_val;
    __IOM uint32_t	tmr1_init_val;
    __IOM uint32_t	tmr2_init_val;
    __IOM uint32_t	tmr3_init_val;
    __IM uint32_t	RESERVED[10];
    __IM uint32_t	tmr0_cur_cnt;
    __IM uint32_t	tmr1_cur_cnt;
    __IM uint32_t	tmr2_cur_cnt;
    __IM uint32_t	tmr3_cur_cnt;
} STC_reg_st;

#define PHM320_TOP     ((phm320_top_regdef *)(0x1f000000UL))
#define PHM320_MTPC    ((phm320_mtpc_regdef *)(0x1f010000UL))
#define PHM320_STC_BASE        (0x1f020000UL)
#define PHM320_IR_BASE         (0x1f030000UL)
#endif  // __PHM320_H__
