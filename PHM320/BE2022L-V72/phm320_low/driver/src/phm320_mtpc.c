#include "phm320_mtpc.h"

em_result_t  __attribute__ ((section (".mtp_run_ram")))  mtpc_run(const str_mtpc_run_t *mtpc_config)
{
    if (mtpc_config->mode > 3 \
        && mtpc_config->mode < 10) {
        PHM320_MTPC->ADDR = mtpc_config->address;
        PHM320_MTPC->DATA = mtpc_config->data;
    }
    PHM320_MTPC->MTPC_CTL_BITS.MODE = mtpc_config->mode;
    while (!PHM320_MTPC->FINISH) {}
    return Ok;
}

void  __attribute__ ((section (".mtp_run_ram"))) mtp_erase(uint32_t address)
{	
	str_mtpc_run_t mtpc_config;
    clear_mem_struct(mtpc_config);

	if(address<0x400)
	{
		mtpc_config.mode = SECTOR_ERASE_MB;		
		mtpc_config.address = address;
	}
	else
	{
		mtpc_config.mode = SECTOR_ERASE_XB;
		mtpc_config.address = address-0X400;		
	}	
	mtpc_run(&mtpc_config);
		
	mtpc_config.mode = AHB_READ;
	mtpc_run(&mtpc_config);
		
}

void  __attribute__ ((section (".mtp_run_ram"))) mtp_write(uint32_t address, uint32_t data)
//void mtp_write(uint32_t address, uint32_t data)
{	
	str_mtpc_run_t mtpc_config;
    clear_mem_struct(mtpc_config);
	
	if(address<0x400)
	{
		mtpc_config.mode = PROGRAM_MB;		
		mtpc_config.address = address;
	}
	else
	{
		mtpc_config.mode = PROGRAM_XB;		
		mtpc_config.address = address-0X400;		
	}
	mtpc_config.data = data;
	mtpc_run(&mtpc_config);
	
	mtpc_config.mode = AHB_READ;
	mtpc_run(&mtpc_config);
	
}
