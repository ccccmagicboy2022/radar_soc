/**
  ************************************* Copyright ******************************
  *                 (C) Copyright 2022,--,China, PHO.
  *                            All Rights Reserved
  *
  *                     By(--)
  *                     https://--
  *
  * FileName   : xbr820_flash.h
  * Version    : v1.0
  * Author     : cccc
  * Date       : 2022-12-19
  * Description:
  * Function List:
      1. ....
         <version>:
  <modify staff>:
            <data>:
   <description>:
      2. ...
  ******************************************************************************
 */


/*include----------------------------------------------------------------------*/
#include "pho_common.h"

/*define-----------------------------------------------------------------------*/
#define XBR820_SPI_BASEADDR    (0x1f070000UL)
#define SPI_CMMD_LEN        11
#define SPI_READ_LEN        4
#define SPI_BURST_LEN        4
#ifndef SF_CMD_READ
 #define SF_CMD_READ        COMMON_INS_FARD
#endif
/* XBR820 serial FLASH registers, loop mapping each 16B */
#define SPI_CR                (XBR820_SPI_BASEADDR + 0)
#define SPI_CM                (XBR820_SPI_BASEADDR + 4)
#define SPI_CM1               (XBR820_SPI_BASEADDR + 8)
#define SPI_CM2               (XBR820_SPI_BASEADDR + 12)
/* XBR820 serial FLASH CR bits */
#define SPI_CR_CLKPH           0x01    /* SPI clock phase when working */
#define SPI_CR_CLKPO           0x02    /* SPI clock active porlarity */
#define SPI_CR_SPIEN           0x04    /* SPI controller enable or not */
#define SPI_CR_STOP            0x08    /* SPI sequency stop */

#define SPI_CR_HOLD            0x10    /* SPI HOLD pin control */
#define SPI_CR_DUAL            0x20    /* SPI FLASH dual read mode */

#define COMMON_INS_WRSR        0x01    /* Common write status instruction */
#define COMMON_INS_PP        0x02    /* Common page program instruction */
#define COMMON_INS_READ        0x03    /* Common read instruction */
#define COMMON_INS_WRDI        0x04    /* Common write disable instruction */
#define COMMON_INS_RDSR        0x05    /* Common read status instruction */
#define COMMON_INS_WREN        0x06    /* Common write enable instruction */
#define COMMON_INS_FARD        0x0B    /* Common fast read instruction */
#define COMMON_INS_RES        0xAB    /* Common release from deep power-down & read device id instruction */
#define COMMON_INS_DP        0xB9    /* Common deep power-down instruction */
#define COMMON_INS_BE        0xC7    /* Common bulk erase instruction */
#define COMMON_INS_SE        0xD8    /* Common sector erase instruction */
#define COMMON_INS_FARDD    0x3B    /* Common fast read dual-output instruction */
#define COMMON_INS_RDID        0x90    /* Common read ID instruction */
#define COMMON_INS_JEDEC    0x9F    /* Common read JEDEC ID instruction */

#define COMMON_INS_EN4B        0xB7    /* Common enter 4byte mode instruction */
#define COMMON_INS_EX4B        0xE9    /* Common exit 4byte mode instruction */

#define SF_PAGE_SIZE        (1 << 8)

/*variate statement------------------------------------------------------------*/


/*function statement-----------------------------------------------------------*/

#ifndef __XBR820_FLASH_H_
#define __XBR820_FLASH_H_

#ifdef __cplusplus
extern "C"
{
#endif

int flashProgram(uint32_t dst, const uint8_t *src, uint32_t length);
int flashRead(uint8_t* dst, uint32_t src, uint32_t length);
int flashChipErase(void);
int flashSectErase(uint32_t sect);

#ifdef __cplusplus
}
#endif

#endif




