#include "phm320_mtpc.h"

int __attribute__ ((section (".data"))) main()
{
	str_mtpc_run_t mtpc_config;
    clear_mem_struct(mtpc_config);
	
	mtpc_config.mode = SECTOR_ERASE_XB;
	mtpc_config.address = 0x000;
    mtpc_run(&mtpc_config);	
	
	mtpc_config.mode = PROGRAM_XB;
	mtpc_config.address = 0x08;
	mtpc_config.data = 0x12345678;
	mtpc_run(&mtpc_config);
	
//	mtpc_config.mode = PROGRAM_XB;
//	mtpc_config.address = 0x09;
//	mtpc_config.data = 0x12345678;
//	mtpc_run(&mtpc_config);
	
//	mtpc_config.mode = SECTOR_ERASE_XB;
//	mtpc_config.address = 0x020;
//    mtpc_run(&mtpc_config);	
	
	mtpc_config.mode = AHB_READX;
	mtpc_run(&mtpc_config);
	
	mtpc_config.mode = AHB_READX;
	mtpc_run(&mtpc_config);	
	
	
//	mtpc_config.mode = SECTOR_EARSE_MB;
//	mtpc_config.address = 0x3F0;
//    mtpc_run(&mtpc_config);
//
//	mtpc_config.mode = PROGRAM_MB;
//	mtpc_config.address = 0x3F0;
//	mtpc_config.data = 0x87654321;
//	mtpc_run(&mtpc_config);	
//
//    mtpc_config.mode = AHB_READ;
//    mtpc_run(&mtpc_config);
	
    return 0;
}