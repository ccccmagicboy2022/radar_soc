#ifndef __GLOBAL_CONFIG_H__
#define __GLOBAL_CONFIG_H__

//#define __NO_ICACHE
//#define __NO_BSS_INIT
//#define CONFIG_SBUS_LOAD

#ifndef CONFIG_HAVE_VIC
 #define CONFIG_HAVE_VIC	1
#endif

#ifdef CONFIG_CONSOLE_HANDLE
 #ifndef CONFIG_CONSOLE_RXSIZE
  #if CONFIG_HAVE_VIC
   #define CONFIG_CONSOLE_RXSIZE	64
  #endif
 #endif
 #ifndef CONFIG_CONSOLE_RXSIZE
  #if CONFIG_HAVE_VIC
   #define CONFIG_CONSOLE_TXSIZE	32
  #endif
 #endif
#endif

#ifndef CONFIG_ARCH_INTERRUPTSTACK
 #ifdef CONFIG_ROM
  #ifdef CONFIG_PRINTF
   #define CONFIG_ARCH_INTERRUPTSTACK	512
  #else
   #define CONFIG_ARCH_INTERRUPTSTACK	384
  #endif
 #else
  #define CONFIG_ARCH_INTERRUPTSTACK	192
 #endif
#endif

#ifndef CONFIG_ARCH_TRAPSTACK
 #if CONFIG_HAVE_VIC
  #ifdef CONFIG_ROM
   #define CONFIG_ARCH_TRAPSTACK	128
  #else
   #define CONFIG_ARCH_TRAPSTACK	96
  #endif
 #endif
#endif

#ifdef CONFIG_ROM
 #define __NO_ICACHE
#endif

#endif
