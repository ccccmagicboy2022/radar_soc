#ifndef __FLASH_H__
#define __FLASH_H__

#include "jtag2.h"

void flash_init(void);
int download_run_algorithm(uint32_t dst, uint32_t *src, uint32_t len);
int erase_flash(void);
int program_flash(uint32_t dst, uint32_t src, uint32_t length);
int verfiy_flash_checksum(uint32_t length, uint32_t check_sum);
void try_to_debug(void);
int program_verify_flash(uint32_t *buffer, uint32_t len, uint32_t check_sum);
#endif
