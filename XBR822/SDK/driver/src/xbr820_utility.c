#include "xbr820_utility.h"

/**
 *******************************************************************************
 ** @brief assert error handle function
 **
 ** @param file: point to the current the wrong file
 ** @param line: error line source number
 **
 ******************************************************************************/
#ifdef __DEBUG
__WEAK void assert_failed(uint8_t *file, int16_t line)
{
    (void)file;
    (void)line;
    for (;;)
        ;
}
#endif /* __DEBUG */

/************************ (C) COPYRIGHT Phosense-tech *****END OF FILE****/
