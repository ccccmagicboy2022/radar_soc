#include "main.h"
#include "dma.h"
#include "fatfs.h"
#include "sdio.h"
#include "gpio.h"

int read_sd_data(uint8_t *buf, uint32_t *len)
{
    FATFS fs;
    FIL file;
    FRESULT f_res;
    UINT fnum;
    int ret = 0;

    f_res = f_mount(&fs, "0:", 1);
    if (FR_OK != f_res)
        return -1;

    f_res = f_open(&file, "BE2022L.bin", FA_OPEN_EXISTING | FA_READ);
    if (FR_OK != f_res) {
        ret = -1;
        goto exit;
    }

    f_res = f_read(&file, buf, *len, &fnum);
    *len = fnum;

    f_close(&file);

exit:
    f_mount(NULL, "0:", 1);

    return ret;
}
