#include "phm320_gpio.h"
#include "phm320_pwm.h"
#include "phm320.h"

#define SYSTEM_CLOCK 16000000
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

	pwm_Freq[pwm->idx] = pwm->freq;	//按分频比设置
	pwm_Duty[pwm->idx] = pwm->duty;	//按实际占空比数值设置
	
//按频率设置	
    //pwm_Freq[pwm->idx] = SYSTEM_CLOCK / pwm->freq;/* the freq register's value is the result of SYSTEM CLOCK devided by the frequence wanted */
//按百分比计算	
   // pwm_Duty[pwm->idx] = (pwm_Freq[pwm->idx] * pwm->duty) / 100;/* the duty register's value is the ratio of frequence */	
   
	

    PWM_reg->enable.encfg |= (1 << (12 + pwm->idx));
    return 0;
}

/*
int pwm_enable(PWM_Config_t* pwm)
{
    if ( (pwm == NULL) ||
        ((pwm->freq == 0) && ( pwm->duty == 0)))
        return -1;
    PWM_reg_t *PWM_reg = ((PWM_reg_t*)(PHM320_STC_BASE));

    __IO uint32_t *pwm_Freq = &(PWM_reg->pwm_freq_ctrl1);
    __IO uint32_t *pwm_Duty = &(PWM_reg->pwm_freq_duty1);

	pwm_Freq[pwm->idx] = pwm->freq;	//按分频比设置
	pwm_Duty[pwm->idx] = pwm->duty;	//按实际占空比数值设置
	
//按频率设置	
    //pwm_Freq[pwm->idx] = SYSTEM_CLOCK / pwm->freq; // the freq register's value is the result of SYSTEM CLOCK devided by the frequence wanted 
//按百分比计算	
   // pwm_Duty[pwm->idx] = (pwm_Freq[pwm->idx] * pwm->duty) / 100; //the duty register's value is the ratio of frequence 
   
    PWM_reg->enable.encfg |= (1 << (12 + pwm->idx));
    return 0;
}
*/

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
