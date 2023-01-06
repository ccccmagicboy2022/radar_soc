#ifndef __PHM320_TIMER_H__
#define __PHM320_TIMER_H__

#include "typdef.h"

#ifdef __cplusplus
extern "C" {
#endif

enum timer_num
{
    TIMER0,
    TIMER1,
    TIMER2,
    TIMER3,
};



#define CONFIG_TIMER_NUM    4
/** 
  * @brief  TIM Timer config structure definition  
  * @note   This structure is used with all timer, timer0 ~ timer3.  
  */
typedef struct
{
	uint8_t id;	         /*!< Specifies the timer's ID used to identify a special timer.
                                       This parameter can be a number between 0 ~ 3 */
								
	uint32_t counter;/*!< Specifies the couter value used to be the timer's length.
                                       This parameter can be a number between 0 and 0xFFFFFFFF.
									    The deault value is 0xFFF00000.
										In brief, the number, 16,000,000, equals to one second.*/
}Timer_Cfg_t;

typedef struct{
	uint32_t	enable;
	uint32_t	reset_enable;
	uint32_t	counter;
}WDGCfg;

/**
  * @brief  Start the timer. The timer should be set a initial value, or use the default value 0xFFF00000.
  * @param  timer: which is a defined structure, include timerID, counter.
  * @retval 0 for success, -1 for wrong input param.
  */
int timer_enable(Timer_Cfg_t* timer);

/**
  * @brief  Stop the timer.
  * @param  timer: which is a defined structure, include timerID, counter.
  * @retval 0 for success, -1 for wrong input param.
  */
int timer_disable(Timer_Cfg_t* timer);

/**
  * @brief  Reset the timer according to the param id.
  * 				Reset means counting from the init value again.
  * @param  timer: which is a defined structure, include timerID, counter.
  * @retval 0 for success, -1 for wrong input param.
  */
int timer_reset(Timer_Cfg_t* timer);

/**
  * @brief  Restart the timer according to the param id.
  * 				That means counting from the init value again.
  * @param  timer: which is a defined structure, include timerID, counter.
  * @retval 0 for success, -1 for wrong input param.
  */
int timer_restart(Timer_Cfg_t* timer);

/**
  * @brief  Set the timer's initial value.
  * @param  timer: which is a defined structure, include timerID, counter.
  * @retval 0 for success, -1 for wrong input param.
  */
int timer_set_initvalue(Timer_Cfg_t* timer);

/**
  * @brief  Get the timer's initial value.
  * @param  timer: which is a defined structure, include timerID, counter.
  * @retval To return the timer's initial value for success. -1 for wrong input param.
  */
int timer_get_initvalue(Timer_Cfg_t* timer);

/**
  * @brief  Get the timer's current value.
  * @param  timer: which is a defined structure, include timerID, counter.
  * @retval  the timer's current value; -1 for wrong timer id.
  */
int timer_get_currentval(Timer_Cfg_t* timer);

/**
  * @brief  Enable the WatchDog timer. This is a cpu watchdog, only reset cpu not system.
  * @param  wdg: which is a defined structure, include watchdog counter, enable and reset enable settings.
  * @retval 0 for success, -1 for wrong input param.
  */
int wdg_config(WDGCfg* wdg);

void feed_dog(void);
#ifdef __cplusplus
}
#endif

#endif // __FIFO_H__


