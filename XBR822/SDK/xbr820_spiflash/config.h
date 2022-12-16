#ifndef __SF_CONFIG_H__
#define __SF_CONFIG_H__

#define CONFIG_HAVE_VIC 0
#define __NO_ICACHE
#define CONFIG_ARCH_INTERRUPTSTACK    0x100

#define CONFIG_LOG_NUMS    16
//#define CONFIG_DEBUG_TEST
#ifdef CONFIG_DEBUG_TEST
//#define CONFIG_SE_TEST
//#define CONFIG_READ_TEST
#endif

#define CONFIG_SF_JEDEC_ID
#define CONFIG_SF_CHIP_ALL
#define CONFIG_AUTO_PROGRAM

//#define CONFIG_TICK_DELAY

#include <gconfig.h>
#endif    // __SF_CONFIG_H__
