#ifndef __PHM320_PWM_H__
#define __PHM320_PWM_H__

#include "typdef.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ================================================================================ */
/* ================                PWM declaration                ================ */
/* ================================================================================ */

#define CONFIG_PWM_NUM  5

#define PWM_1   0
#define PWM_2   1
#define PWM_3   2
#define PWM_4   3
#define PWM_5   4

/** 
  * @brief   PWM Init structure definition  
  */ 
typedef struct{
	uint32_t idx;	 /*!< Specifies the PWM index to be configured. 
	  							This parameter can be any value of 0~5 */
	uint32_t freq;	/*!< Specifies the PWM frequency to be configured. 
							This parameter can be any value of 0~16,000,000 */
	uint32_t duty;	/*!< Specifies the PWM duty ration to be configured. 
							This parameter can be any value of 0~100  */
}PWM_Config_t;

/**
  * @brief  PWMx enabled.
  * @param  pwm: which is a defined structure, include pwmid, frequency and duty ratio.
  * @retval 0 for success. -1 for wrong input param.
  */
int pwm_enable(PWM_Config_t* pwm);

/**
  * @brief  PWMx disabled.
  * @param  pwm: which is a defined structure, include pwmid, frequency and duty ratio.
  * @retval 0 for success. -1 for wrong input param.
  */
int pwm_disable(PWM_Config_t* pwm);

#ifdef __cplusplus
}
#endif


#endif // __DRV_PWM_H__