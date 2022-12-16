/*******************************************************************************
 * Copyright (c) 2012-2019 Hangzhou C-SKY Microsystems Co., Ltd.
 * 
 * All rights reserved. This software is proprietary and confidential to
 * Hangzhou C-SKY Microsystems Co., Ltd. and its licensors.
 *
 * Contributors:
 *     Hangzhou C-SKY Microsystems Co., Ltd.
 *
 * 2009.12.1   Jing Qing(qing_jing@c-sky.com)
 * 2014.06.30  Fan Rundong(rundong_fan@c-sky.com)
 * 2019.6.18   Jiang Long(long_jiang@c-sky.com)
 *     Initial API and implementation
 *******************************************************************************/

#include "xbr820.h"
#include "flash_config.h"

/*
 * NOTING : this file read only.
 */
 
/*
 * set the version of flash driver
 */
#define VERS      2
const uint32_t fd_version = 0x0000 + VERS;

int flashInit();
int flashID(uint32_t* flashID);
int flashProgram(uint32_t dst, const uint8_t *src, uint32_t length);
int flashRead(uint8_t* dst, uint32_t src, uint32_t length);
int flashErase(uint32_t dst, uint32_t length);
int flashChipErase();
int flashSectErase(uint32_t sect);

void __bkpt_label();
uint32_t g_rwBuffer[SF_BUF_SIZE/sizeof(uint32_t)];
uint32_t g_dstAddress = 0;
uint32_t g_length = 0;
uint32_t g_checksum = 0;
uint32_t g_runmode = 0;

/**
 * The definition of functional options,
 * 0 corresponds to check id,1 corresponds
 * to program,2 corresponds to read,3 corresponds
 * to erase,4 corresponds to chip erase.
 */
int g_func = 0;
uint32_t g_flashID = 0;

#ifdef CONFIG_LOG_NUMS	
extern uint32_t log_data[];
extern uint8_t log_i;
#endif

/**
 * The engineering-driven operation error return
 */
int g_error;
int main() {
	// call nor flash drivers to program
	g_error = flashInit();
#ifdef CONFIG_SE_TEST
	g_func = 3;
	g_length = SF_SECT_SIZE;
#endif
#ifdef CONFIG_READ_TEST
	g_func = 2;
	//g_dstAddress = 0;
	g_length = SF_BUF_SIZE;
#endif
	do {
#ifndef CONFIG_DEBUG_TEST
		__bkpt_label();
#endif
#ifdef CONFIG_LOG_NUMS
		if (log_i < CONFIG_LOG_NUMS) {
			log_data[log_i++] = (g_func << 28) | ((g_dstAddress >> 8) << 12) | g_length;
		}
#endif
		switch (g_func) {
		case 0:
			g_error = flashID(&g_flashID);
			break;
		case 1:
			g_error = flashProgram(g_dstAddress, (const uint8_t *)g_rwBuffer, g_length);
			break;
		case 2:
			g_error = flashRead((uint8_t *)g_rwBuffer, g_dstAddress, g_length);
			break;
		case 3:
			g_error = flashErase(g_dstAddress, g_length);
			break;
		case 4:
			g_error = flashChipErase();
			break;
#if 0
		case 5:
			g_error = flashSectErase(g_dstAddress);
			break;
#endif
		}
#ifdef CONFIG_SE_TEST
		g_func = 0;
#endif
	} while (1);
}
