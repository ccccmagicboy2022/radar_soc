#ifndef __XBR820_UTILITY_H__
#define __XBR820_UTILITY_H__

#define __WEAK                          __attribute__((weak))


/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  x: If x is false, it calls assert_failed function. If expr is true, it returns no value.
  * @retval None
  */
#ifdef __DEBUG
    #define assert_param(x) ((x) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
    void assert_failed(uint8_t* file, uint32_t line);
#else
#define assert_param(x) ((void)0)
#endif /* __DEBUG */

#endif

/************************ (C) COPYRIGHT Phosense-tech *****END OF FILE****/
