#include "flash.h"
#include "flash_bin.h"

#define DDC_MEMORY                          (0x1000)
#define BIN_LEN                             (1056)

#define FUNC_ADDR                           (0x162c)
#define DST_ADDR                            (0x1620)
#define LENGTH_ADDR                         (0x1624)
#define CHECK_SUM_ADDR                      (0x1628)
#define BUFFER_ADDR                         (0x1420)
#define ERROR_ADDR                          (0x1634)
#define FLASH_ID_ADDR                       (0x1630)

#define ERASE_FUNC                          (0x04)
#define FLASH_FUNC                          (0x01)
#define CHECKSUM_FUNC                       (0x06)

extern uint8_t test_data[];
#define TEST_DATA_LEN                       (2736)
#define MAX_TXDATA_LEN                      (0x200)
#define BOOT_ADDR                           (0x13de)
#define EXEC_ADDR                           (0x1004)


void flash_init(void)
{
    jtag2_init();
}

void try_to_debug(void)
{
    uint32_t result;

    while(1) {
        jtag2_write_had(WR_HCR, 8, EN_DEBUG);
        jtag2_read_had(RD_HSR, 8, &result);
        if (result != 0xffffffff) {
            if ((result & 0x03) != 0)
                break;
        }
    }
}


int download_run_algorithm(uint32_t dst, uint32_t *src, uint32_t len)
{
    int ret = 0;
    uint32_t result;

    reset_mcu();
    /* download flash algorithm to RAM */
    jtag2_ddc_download(dst, src, len);
    /* run flash algorithm from SRAM */
    reset_mcu();
    jtag2_write_had(WR_PC, 8, BOOT_ADDR);
    jtag2_exit_debug();

    ret = wait_mcu_idle();
    if (ret)
        goto exit;
    result = jtag2_read_word(ERROR_ADDR);
    if (result != 0)
        ret = -1;
exit:
    return ret;
}

int erase_flash(void)
{
    int ret = 0;
    uint32_t result;

    jtag2_write_word(FUNC_ADDR, ERASE_FUNC);
    jtag2_write_had(WR_PC, 8, EXEC_ADDR);
    jtag2_exit_debug();
    ret = wait_mcu_idle();
    if (ret)
        goto exit;
    result = jtag2_read_word(ERROR_ADDR);
    if (result != 0)
        ret = -1;
exit:
    return ret;
}

int program_flash(uint32_t dst, uint32_t src, uint32_t length)
{
    int len, i, ret = 0;
    uint32_t result;

    jtag2_write_word(FUNC_ADDR, FLASH_FUNC);
    for (i = 0; i < length;) {
        if ((i + MAX_TXDATA_LEN) < length)
            len = MAX_TXDATA_LEN;
        else
            len = length - i;
        jtag2_write_word(DST_ADDR, dst);
        jtag2_write_word(LENGTH_ADDR, len);
        jtag2_ddc_download(BUFFER_ADDR, (uint32_t *)src, len);

        dst += len;
        src += len;
        i += len;
        jtag2_write_had(WR_PC, 8, EXEC_ADDR);
        jtag2_exit_debug();
        ret = wait_mcu_idle();
    }

    if (ret)
        goto exit;
    result = jtag2_read_word(ERROR_ADDR);
    if (result != 0)
        ret = -1;
exit:
    return ret;
}

int verfiy_flash_checksum(uint32_t length, uint32_t check_sum)
{
    int ret = 0;
    uint32_t result;

    jtag2_write_word(DST_ADDR, 0);
    jtag2_write_word(LENGTH_ADDR, length);
    jtag2_write_word(CHECK_SUM_ADDR, check_sum);
    jtag2_write_word(FUNC_ADDR, CHECKSUM_FUNC);
    jtag2_write_had(WR_PC, 8, EXEC_ADDR);
    jtag2_exit_debug();
    ret = wait_mcu_idle();
    if (ret)
        goto exit;
    result = jtag2_read_word(ERROR_ADDR);
    if (result != 0)
        ret = -1;

exit:
    return ret;
}

int program_verify_flash(uint32_t *buffer, uint32_t len, uint32_t check_sum)
{
    int ret;

    ret = download_run_algorithm(DDC_MEMORY, (uint32_t *)bin_code, BIN_LEN);
    if (ret)
        goto exit;
    /* Erase flash */
    ret = erase_flash();
    if (ret)
        goto exit;
    /* program flash */
    ret = program_flash(0, (uint32_t)buffer, len);
    if (ret)
        goto exit;
    /* checksum */
    ret = verfiy_flash_checksum(len, check_sum);
    if (ret)
        goto exit;

exit:
    return ret;
}
