#ifndef __PHO_COMMON_H__
#define __PHO_COMMON_H__

#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#if defined(XBR820)
#include "xbr820.h"
#endif
#if defined(PHM320)
#include "phm320.h"
#endif

#define     __I     volatile const       /*!< Defines 'read only' permissions */
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

typedef void (*func_ptr_t)(void);

typedef enum em_functional_state
{
    DISABLE = 0u,
    ENABLE  = 1u,
} em_functional_state_t;

typedef enum em_flag_status
{
    RESET = 0u,
    SET   = 1u,
} em_flag_status_t, em_int_status_t;

typedef enum em_result
{
    Ok                       = 0u,   ///< No error
    ERROR                    = 1u,   ///< Non-specific error code
    ERRORADDRESSALIGNMENT    = 2u,   ///< Address alignment does not match
    ERRORACCESSRIGHTS        = 3u,   ///< Wrong mode (e.g. user/system) mode is set
    ERRORINVALIDPARAMETER    = 4u,   ///< Provided parameter is not valid
    ERROROPERATIONINPROGRESS = 5u,   ///< A conflicting or requested operation is still in progress
    ERRORINVALIDMODE         = 6u,   ///< Operation not allowed in current mode
    ERRORUNINITIALIZED       = 7u,   ///< Module (or part of it) was not initialized properly
    ERRORBUFFERFULL          = 8u,   ///< Circular buffer can not be written because the buffer is full
    ERRORTIMEOUT             = 9u,   ///< Time Out error occurred (e.g. I2C arbitration lost, Flash time-out, etc.)
    ERRORNOTREADY            = 10u,  ///< A requested final state is not reached
    OPERATIONINPROGRESS      = 11u,  ///< Indicator for operation in progress (e.g. ADC conversion not finished, DMA channel used, etc.)
} em_result_t;


/*! Memory clear */
#define clear_mem_struct(x)             do {                                  \
                                        memset((void*)&(x), 0, (sizeof(x)));  \
                                        }while(0)

#endif