#ifndef __PHO_COMMON_H__
#define __PHO_COMMON_H__

#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#if defined(XBR820)
#include "xbr820.h"
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
    OK                       = 0u,   ///< No error
    ERROR                    = 1u,   ///< error
} em_result_t;


/*! Memory clear */
#define clear_mem_struct(x)             do {                                  \
                                        memset((void*)&(x), 0, (sizeof(x)));  \
                                        }while(0)

#endif
