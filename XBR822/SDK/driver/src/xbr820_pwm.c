/**
 * @file phm320_pwm.c
 * @author Phosense Software Team
 * @brief pwm C source file
 * @version 1.0.0.0
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022, Phosense-tech, All rights reserved.
 * 
 */

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "phm320_gpio.h"
#include "phm320_pwm.h"

/** @{*/

/**
  * @brief  PWMx enabled.
  * @param  pwm: which is a defined structure, include pwmid, frequency and duty ratio.
  * @retval 0 for success. -1 for wrong input param.
  */
int pwm_enable(PWM_Config_t* pwm)
{
    if ( (pwm == NULL) ||
        ((pwm->freq == 0) && ( pwm->duty == 0)))
        return -1;
    PWM_reg_t *PWM_reg = ((PWM_reg_t*)(PHM320_STC_BASE));

    __IO uint32_t *pwm_Freq = &(PWM_reg->pwm_freq_ctrl1);
    __IO uint32_t *pwm_Duty = &(PWM_reg->pwm_freq_duty1);

    pwm_Freq[pwm->idx] = SYSTEM_CLOCK / pwm->freq;/* the freq register's value is the result of SYSTEM CLOCK devided by the frequence wanted */
    pwm_Duty[pwm->idx] = (pwm_Freq[pwm->idx] * pwm->duty) / 100;/* the duty register's value is the ratio of frequence */
    PWM_reg->enable.encfg |= (1 << (12 + pwm->idx));
    return 0;
}

/**
  * @brief  PWMx disabled.
  * @param  pwm: which is a defined structure, include pwmid, frequency and duty ratio.
  * @retval 0 for success. -1 for wrong input param.
  */
int pwm_disable(PWM_Config_t* pwm)
{
    if (pwm == NULL)
        return -1;

    PWM_reg_t *PWM_reg = ((PWM_reg_t*)(PHM320_STC_BASE));
    
    PWM_reg->enable.encfg &= ~(1 << (12 + pwm->idx));

    return 0;
}

/**  @} pwm_group*/
