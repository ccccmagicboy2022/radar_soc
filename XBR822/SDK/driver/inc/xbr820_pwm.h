/**
 * @file xbr820_pwm.h
 * @author Phosense Software Team
 * @brief pwm C head file
 * @version 1.0.0.0
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022, Phosense-tech, All rights reserved.
 * 
 */

#ifndef __XBR820_PWM_H__
#define __XBR820_PWM_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "pho_common.h"

enum timer_num
{
    PWM0,
    PWM1,
    PWM2,
    PWM3,
    PWM4,
};

/**
 * @defgroup pwm_group Pulse Width Modulation(PWM)
 * @{
 */

#define CONFIG_PWM_NUM  5

/** 
  * @brief   PWM Init structure definition  
  */ 
typedef struct{
	uint32_t idx;	 /*!< Specifies the PWM index to be configured. 
	  							This parameter can be any value of 0~4 */
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

/**  @} pwm_group*/

#endif // __DRV_PWM_H__