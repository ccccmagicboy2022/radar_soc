#ifndef __PHM320_MTPC_H___
#define __PHM320_MTPC_H___

#include "pho_common.h"

typedef enum em_mtpc_mode
{
    AHB_READ         = 0u,
    AHB_READX        = 1u,
    CHIP_EARSE_MB    = 2u,
    CHIP_EARSE_XB    = 3u,
    SECTOR_ERASE_MB  = 4u,
    SECTOR_ERASE_XB  = 5u,
    PROGRAM_MB       = 6u,
    PROGRAM_XB       = 7u,
    PROGRAM_MB_TEST  = 8u,
    PROGRAM_XB_TEST  = 9u,
    PROGRAM_REF_MB   = 10u,
    PROGRAM_REF_XB   = 11u,
    POWER_ON         = 12u,
    POWER_DOWN       = 13u,
} em_mtpc_mode_t;

typedef struct str_mtpc_run
{
    em_mtpc_mode_t        mode;
    uint32_t              address;
    uint32_t              data;
} str_mtpc_run_t;

em_result_t __attribute__ ((section (".mtp_run_ram"))) mtpc_run(const str_mtpc_run_t *mtpc_config);
void  __attribute__ ((section (".mtp_run_ram"))) mtp_erase(uint32_t address);
void  __attribute__ ((section (".mtp_run_ram"))) mtp_write(uint32_t address, uint32_t data);

#endif