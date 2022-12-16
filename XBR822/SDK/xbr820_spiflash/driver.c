/*******************************************************************************
 * Copyright (c) 2012-2019 Hangzhou C-SKY Microsystems Co., Ltd.
 *
 * All rights reserved. This software is proprietary and confidential to
 * Hangzhou C-SKY Microsystems Co., Ltd. and its licensors.
 *
 * Contributors:
 *     Hangzhou C-SKY Microsystems Co., Ltd.
 *
 * 2019.6.18   Jiang Long(long_jiang@c-sky.com)
 *     Initial API and implementation
 *******************************************************************************/
#include "xbr820.h"
#include "flash_config.h"

#define XBR820_PMU_BASE     (0x1f010000UL)
#define XBR820_STC_BASE     (0x1f020000UL)
#define XBR820_SPI_BASEADDR    (0x1f090000UL)

#define SPI_CMMD_LEN        11
#define SPI_READ_LEN        4
#define SPI_BURST_LEN        4

 /* XBR820 serial FLASH registers, loop mapping each 16B */
#define SPI_CR                (XBR820_SPI_BASEADDR + 0)
#define SPI_CM                (XBR820_SPI_BASEADDR + 4)
#define SPI_CM1                (XBR820_SPI_BASEADDR + 8)
#define SPI_CM2                (XBR820_SPI_BASEADDR + 12)

/* XBR820 serial FLASH CR bits */
#define SPI_CR_CLKPH        0x01    /* SPI clock phase when working */
#define SPI_CR_CLKPO        0x02    /* SPI clock active porlarity */
#define SPI_CR_SPIEN        0x04    /* SPI controller enable or not */
#define SPI_CR_STOP            0x08    /* SPI sequency stop */
#define SPI_CR_HOLD            0x10    /* SPI HOLD pin control */
#define SPI_CR_DUAL            0x20    /* SPI FLASH dual read mode */
#define SPI_CR_SPI2            0x40    /* SPI CS2 for second SPI FLASH */

/* XBR820 serial FLASH CM0 bits */
#define SPI_CM_CMLEN        0x04
#define SPI_CM_RXLEN        0x70
#define SPI_CM_RXEN            0x80


#define send_cmd(cmd)        do { reg32_write(SPI_CM, 0x01 | (cmd << 8)); } while(0)

#ifdef CONFIG_TICK_DELAY
#define STC_CTL                (XBR820_STC_BASE + 0x00)
#define TICK_INIT            (XBR820_STC_BASE + 0x08)
#define TICK_CNT            (XBR820_STC_BASE + 0x40)
#define TICK_ENABLE            (0x10)
#define TICK_CNT_MS            (SYSTEM_CLOCK / 1000)
#define TICK_CNT_MAX        (-1UL)

static inline void tick_init(void) {
    reg32_write(TICK_INIT, TICK_CNT_MAX);
    reg32_write(STC_CTL, TICK_ENABLE);
}
static inline uint32_t tick_count(void) {
    return reg32_read(TICK_CNT);
}
static inline uint32_t tick_diff(uint32_t start) {
    uint32_t diff;
    uint32_t cnt = tick_count();
    if (cnt > start)
        diff = start + (TICK_CNT_MAX - cnt);
    else
        diff = start - cnt;
    return diff;
}
static void delay_ms(uint32_t ms) {
    uint32_t start = tick_count();
    uint32_t period = ms * TICK_CNT_MS;
    while (tick_diff(start) < period);
}
#else
 #define delay_ms(ms)    do {} while(0)
 #define tick_init()    do {} while(0)
#endif

/**
 * Driver for flash program.
 */

 /**
  * ERROR TYPE. MUST NOT BE MODIFIED
  */
#define ERROR_INIT      -200
#define ERROR_READID    -201
#define ERROR_PROGRAM   -202
#define ERROR_READ      -203
#define ERROR_ERASE     -204
#define ERROR_CHIPERASE -205
#define ERROR_UNINIT    -206
#define ERROR_CHECKSUM  -207

uint32_t sf_size;
uint32_t sf_id;
#ifdef CONFIG_AUTO_PROGRAM
uint32_t block_erased;
#endif
#ifdef CONFIG_LOG_NUMS
uint32_t log_data[CONFIG_LOG_NUMS] = {0};
uint8_t log_i = 0;
#endif

int flashErase(uint32_t dst, uint32_t length);
int flashChipErase();

#if 0
static inline void wait_status(uint32_t mask, uint32_t val)
{
    while (1) {
        /* Set RDSR instruction: TX command length is 1, RX data length is 1, total 2 */
        reg32_write(SPI_CM, 0x92 | (COMMON_INS_RDSR << 8));
        if ((reg32_read(SPI_CR) & mask) == val)
            break;
    }
}

static void wait_ready(void)
{
    /* Read from any address of serial flash to check device free. */
    return wait_status(1, 0);
}

static void write_protect(int en)
{
    send_cmd(COMMON_INS_WREN);
    if (en) {
        /* Set WRSR instruction: TX command length is 2 (SR=0x7F), RX data length is 0, total 2 */
        reg32_write(SPI_CM, 0x02 | (COMMON_INS_WRSR << 8) | (0x7F << 16));
        wait_status(0x05, 0x04);
    }
    else {
        reg32_write(SPI_CR, SPI_CR_SPIEN | SPI_CR_STOP);
        /* Set WRSR instruction: TX command length is 2 (SR=0x00), RX data length is 0, total 2 */
        reg32_write(SPI_CM, 0x02 | (COMMON_INS_WRSR << 8));
        wait_status(0x05, 0);
    }
}
#else
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
#endif

static uint32_t get_id(void)
{
    BHW_t id = { .w = 0 };

#ifdef CONFIG_SF_JEDEC_ID
    /* Read Identification JEDEC ID */
    /* TX command length is 1, RX data length is 3, total is 4 */
    reg32_write(SPI_CM, 0x000000B4 | (COMMON_INS_JEDEC << 8));
    id.w = reg32_read(SPI_CR);
    swap(id.b[0], id.b[2], id.b[3]);
    id.w &= 0x00FFFFFF;
#else
    /* Read Electronic Manufacturer ID & Device ID */
    /* TX command length is 4, RX data length is 2, total is 6 */
    reg32_write(SPI_CM1, 0);
    reg32_write(SPI_CM, 0x000000A6 | (COMMON_INS_RDID << 8));
    id.w = reg32_read(SPI_CR);
    swap(id.b[0], id.b[1], id.b[3]);
    id.w &= 0x0000FFFF;
#endif
    reg32_write(SPI_CR, 0);
    return id.w;
}

static void block_erase(uint32_t offset)
{
#ifdef CONFIG_AUTO_PROGRAM
    uint32_t blk_mask = 1 << (offset >> SF_BLOCK_SHIFT);
    if (blk_mask & block_erased)
        return;
#endif
    if (offset & (SF_BLOCK_SIZE - 1))
        return;
#if 0
    reg32_write(SPI_CR, 0x0c);
    reg32_write(SPI_CM, 0x601);
    reg32_write(SPI_CM, 0x102);
    delay_ms(200);
    reg32_write(SPI_CM, 0x601);
    reg32_write(SPI_CM1, 0);
    reg32_write(SPI_CM, 0xc704);
    reg32_write(SPI_CM, 0x601);
    reg32_write(SPI_CM, 0x7f0102);
#else
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
#endif
#ifdef CONFIG_AUTO_PROGRAM
    block_erased |= blk_mask;
#endif
}


/**
 * Customize this method to perform any initialization
 * needed to access your flash device.
 *
 * @return: if this method returns an error,MUST RUTURN ERROR_INIT,
 * Otherwise return 0.
 */
int  flashInit() {
    sf_size = 0;
    tick_init();
    //reg32_write(XBR820_PMU_BOOT_RST, 0x13); // Not boot from SPINorFlash
    /* Enable SFLASH module */
    reg32_write(SPI_CR, 0);
    reg32_write(SPI_CR, SPI_CR_SPIEN | SPI_CR_STOP);
    write_protect(1);
    sf_id = get_id();
    reg32_write(SPI_CR, 0);
    if (!sf_id)
        return ERROR_INIT;
    sf_size = SF_BLOCK_SIZE << (sf_id & 0x0F);
#ifdef CONFIG_AUTO_PROGRAM
    block_erased = 0;
#endif
    return 0;
}

/**
 * Customize this method to read flash ID
 *
 * @param flashID: returns for flash ID
 *
 * @return: if this method returns an error,MUST RUTURN ERROR_READID,
 * Otherwise return 0.
 */
int  flashID(uint32_t* flashID) {
#if 0
    uint32_t id;

    reg32_write(SPI_CR, SPI_CR_SPIEN | SPI_CR_STOP);
    id = get_id();
    if (!id)
        return ERROR_READID;
    if (flashID)
        *flashID = id;
#else
    if (!sf_id)
        return ERROR_READID;
    if (flashID)
#ifdef SF_CHIP_ALL
        * flashID = SF_CHIP_ID;
#else
        * flashID = sf_id;
#endif
#endif
    return 0;
}

/**
 * This method takes the data pointed to by the src parameter
 * and writes it to the flash blocks indicated by the
 * dst parameter.
 *
 * @param dst : destination address where flash program
 * @param src : address of data
 * @param length : data length
 *
 * @return : if this method returns an error,MUST RUTURN ERROR_PROGRAM,
 * Otherwise return 0.
 */
int flashProgram(uint32_t dst, const uint8_t* src, uint32_t length) {
    uint8_t buffer[12];
    uint32_t first;

    if (dst >= sf_size)
        return ERROR_PROGRAM;
#ifdef CONFIG_AUTO_PROGRAM
    flashErase(dst, length);
#endif
    if (dst + length > sf_size)
        length = sf_size - dst;

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

/**
 * Customize this method to read data from a group of flash blocks into a buffer
 *
 * @param dst : reads the contents of those flash blocks into the address pointed to by
 * the dst parameter.
 * @param src : a pointer to a single flash.
 * @param length : data length
 *
 *  @return: if this method returns an error,MUST RUTURN ERROR_READ,
 * Otherwise return 0.
 */
int flashRead(uint8_t* dst, uint32_t src, uint32_t length) {
    uint8_t cmd = SF_CMD_READ;
    uint8_t dmlen = (cmd == COMMON_INS_READ) ? 0 : 1;
    uint8_t crmsk = (cmd == COMMON_INS_FARDD) ? SPI_CR_DUAL : 0;
    uint8_t buffer[5] = { 0 };
    int first = 1;

    if (src >= sf_size)
        return ERROR_READ;
    if (src + length > sf_size)
        length = sf_size - src;

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

/**
 * Customize this method to erase a group of flash blocks.
 *
 * @param dst : a pointer to the base of the flash device.
 * NOTE: dst will always be sector aligned, the sector size is stored in FlashDev.c#FlashDevices#Devs#PageSize
 * @param length : erase length
 * NOTE: length will always be sector aligned, the sector size is stored in FlashDev.c#FlashDevices#Devs#PageSize
 *
 * @return : if this method returns an error,MUST RUTURN ERROR_ERASE,
 * Otherwise return 0
 */
int flashErase(uint32_t dst, uint32_t length) {
    if (!dst && -1UL == length)
        return flashChipErase();

    if (dst >= sf_size)
        return ERROR_ERASE;
    if (dst + length > sf_size)
        length = sf_size - dst;

    uint32_t offs = dst;
    uint32_t end = dst + length;
    while (dst < end) {
        block_erase(offs);
        offs &= ~(SF_BLOCK_SIZE - 1);
        offs += SF_BLOCK_SIZE;
        dst += SF_BLOCK_SIZE;
    }
    return 0;
}

int flashSectErase(uint32_t offs) {
    if (offs >= sf_size)
        return ERROR_ERASE;
    block_erase(offs);
    return 0;
}

/**
 * Customize this method to erase the whole flash.
 *
 * @return : if this method returns an error,MUST RUTURN ERROR_CHIPERASE,
 * Otherwise return 0.
 */
int flashChipErase() {
    if (!sf_size)
        return ERROR_CHIPERASE;
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
#ifdef CONFIG_AUTO_PROGRAM
    block_erased = -1UL;
#endif
    return 0;
}
