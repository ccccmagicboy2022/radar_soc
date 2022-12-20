/**
  ************************************* Copyright ******************************
  *
  *                 (C) Copyright 2022,--,China, PHO.
  *                            All Rights Reserved
  *
  *                     By(--)
  *                     https://--
  *
  * FileName   : xbr820_flash.c
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
#include "xbr820_flash.h"

/*define-----------------------------------------------------------------------*/
typedef volatile uint8_t    reg8_t;
typedef volatile uint16_t    reg16_t;
typedef volatile uint32_t    reg32_t;

#define reg8_read(r)        (*(reg8_t *)(r))
#define reg8_write(r, v)    do { *(reg8_t *)(r) = (uint8_t)(v); } while(0)
#define reg16_read(r)        (*(reg16_t *)(r))
#define reg16_write(r, v)    do { *(reg16_t *)(r) = (uint16_t)(v); } while(0)
#define reg32_read(r)        (*(reg32_t *)(r))
#define reg32_write(r, v)    do { *(reg32_t *)(r) = (uint32_t)(v); } while(0)
#define reg32_set(r, m)        reg32_write(r, reg32_read(r) | (m))
#define reg32_clr(r, m)        reg32_write(r, reg32_read(r) & ~(m))

#define send_cmd(cmd)        do { reg32_write(SPI_CM, 0x01 | (cmd << 8)); } while(0)

/*variate----------------------------------------------------------------------*/


/*statement--------------------------------------------------------------------*/
static void write_protect(int en);
static void wait_ready(void);
static void block_erase(uint32_t offset);

/*Function prototype Begin*****************************************************/
static void wait_ready(void)
{
    /* Read from any address of serial flash to check device free. */
    while (1) {
        /* Set RDSR instruction: TX command length is 1, RX data length is 1, total 2 */
        reg32_write(SPI_CM, 0x92 | (COMMON_INS_RDSR << 8));
        if ((reg32_read(SPI_CR) & 1) == 0)
            break;
    }
}

static void write_protect(int en)
{
    send_cmd(COMMON_INS_WREN);
    if (en) {
        /* Set WRSR instruction: TX command length is 2 (SR=0x7F), RX data length is 0, total 2 */
        reg32_write(SPI_CM, 0x02 | (COMMON_INS_WRSR << 8) | (0x7F << 16));
    }
    else {
        reg32_write(SPI_CR, SPI_CR_SPIEN | SPI_CR_STOP);
        /* Set WRSR instruction: TX command length is 2 (SR=0x00), RX data length is 0, total 2 */
        reg32_write(SPI_CM, 0x02 | (COMMON_INS_WRSR << 8));
    }
    wait_ready();
}

int flashChipErase()
{
    reg32_write(SPI_CR, SPI_CR_SPIEN | SPI_CR_STOP);
    write_protect(0);
    /* Enable write */
    send_cmd(COMMON_INS_WREN);
    /* Set errase instruction: TX command length is 1, RX data length is 0, total 1 */
    reg32_write(SPI_CM, 0x01 | (COMMON_INS_BE << 8));
    wait_ready();
    /* Protect chip */
    write_protect(1);
    reg32_write(SPI_CR, 0);
    return 0;
}

int flashSectErase(uint32_t sect)
{
    block_erase(sect);
    return 0;
}

static void block_erase(uint32_t offset)
{
    reg32_write(SPI_CR, SPI_CR_SPIEN | SPI_CR_STOP);
    write_protect(0);
    /* Enable write */
    send_cmd(COMMON_INS_WREN);
    /* Set errase instruction: TX command length is 4, RX data length is 0, total 4 */
    reg32_write(SPI_CM1, offset & 0xFF);
    reg32_write(SPI_CM, 0x04 | (COMMON_INS_SE << 8) | (offset & 0xFF0000) | ((offset & 0xFF00) << 16));
    wait_ready();
    /* Protect chip */
    write_protect(1);
    reg32_write(SPI_CR, 0);
}

int flashProgram(uint32_t dst, const uint8_t* src, uint32_t length) {
    uint8_t buffer[12];
    uint32_t first;

    reg32_write(SPI_CR, SPI_CR_SPIEN | SPI_CR_STOP);
    write_protect(0);
    while (length > 0) {
        uint32_t block_len = ((dst + SF_PAGE_SIZE) & ~(SF_PAGE_SIZE - 1)) - dst;  /* Num to align */
        if (block_len > length)
            block_len = length;
        length -= block_len;
        first = 1;
        send_cmd(COMMON_INS_WREN);
        while (block_len > 0) {
            uint32_t pos, current_len;
            if (first) {
                first = 0;
                buffer[1] = COMMON_INS_PP;
                current_len = (block_len + 4 > SPI_CMMD_LEN) ? SPI_CMMD_LEN - 4 : block_len;
                /* TX command length is current_len + 4, RX data length is 0, total is current_len + 4 */
                buffer[0] = current_len + 4;
                buffer[2] = (uint8_t)(dst >> 16);
                buffer[3] = (uint8_t)(dst >> 8);
                buffer[4] = (uint8_t)(dst);
                pos = 5;
                dst += block_len;
            }
            else {
                current_len = (block_len > SPI_CMMD_LEN) ? SPI_CMMD_LEN : block_len;
                /* TX command length is current_len, RX data length is 0, total is current_len */
                buffer[0] = current_len;
                pos = 1;
            }
            block_len -= current_len;
            /* Set WR instruction */
            for (uint32_t i = 0; i < current_len; i++)
                buffer[pos++] = *src++;

            if (block_len) {
                /* If we need next read action, set transfer keeping */
                reg32_write(SPI_CR, SPI_CR_SPIEN);
            }
            else {
                reg32_write(SPI_CR, SPI_CR_SPIEN | SPI_CR_STOP);
            }
            /* Set page program instruction */
            reg32_write(SPI_CM2, (buffer[11] << 24) | (buffer[10] << 16) | (buffer[9] << 8) | buffer[8]);
            reg32_write(SPI_CM1, (buffer[7] << 24) | (buffer[6] << 16) | (buffer[5] << 8) | buffer[4]);
            reg32_write(SPI_CM, (buffer[3] << 24) | (buffer[2] << 16) | (buffer[1] << 8) | buffer[0]);
        }
        wait_ready();
    }
    /* Protect chip */
    write_protect(1);
    reg32_write(SPI_CR, 0);
    return 0;
}

int flashRead(uint8_t* dst, uint32_t src, uint32_t length)
{
    uint8_t cmd = SF_CMD_READ;
    uint8_t dmlen = (cmd == COMMON_INS_READ) ? 0 : 1;
    uint8_t crmsk = (cmd == COMMON_INS_FARDD) ? SPI_CR_DUAL : 0;
    uint8_t buffer[5] = { 0 };
    int first = 1;

    while (length) {
        uint32_t current_len = length > SPI_READ_LEN ? SPI_READ_LEN : length;
        length -= current_len;
        if (length) {
            /* If we need next read action, set transfer keeping */
            reg32_write(SPI_CR, crmsk | SPI_CR_SPIEN);
        }
        else {
            reg32_write(SPI_CR, crmsk | SPI_CR_SPIEN | SPI_CR_STOP);
        }
        /* Set RD instruction */
        if (first) {
            first = 0;
            buffer[1] = cmd;
            /* TX command length is 5, RX data length is current_len, total is current_len + 5 */
            buffer[0] = 0x80 | (current_len << 4) | (current_len + dmlen + 4);
            buffer[2] = (uint8_t)(src >> 16);
            buffer[3] = (uint8_t)(src >> 8);
            buffer[4] = (uint8_t)(src);
        }
        else {
            /* TX command length is 0, RX data length is current_len, total is current_len */
            buffer[0] = 0x80 | (current_len << 4) | current_len;
        }
        reg32_write(SPI_CM1, buffer[4]);
        reg32_write(SPI_CM, (buffer[3] << 24) | (buffer[2] << 16) | (buffer[1] << 8) | buffer[0]);
        /* Read data */
        for (uint32_t burst_len = current_len > SPI_BURST_LEN ?
            SPI_BURST_LEN : current_len; current_len > 0; current_len -= burst_len) {
            uint32_t dw = reg32_read(SPI_CR);
            for (uint32_t i = 0; i < burst_len; i++) {
                *dst++ = ((dw >> (8 * i)) & 0xFF);
            }
        }
    }
    reg32_write(SPI_CR, 0);
    return 0;
}

/*Function prototype End*******************************************************/

