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
#include "FlashOS.h"

/**
 * structure to describe flash device
 */
struct FlashDevice const FlashDevices  INDEVSECTION =  {
    6,                      // Reserved version description, do not modify!!!
    "xbr820_spiflash_downlload",              // Flash name
    "e902",              // CPU name, must in low case
    0x22030301,               // Flash ID
    "spiflash",             // type
    512*1024,               // Reserved
    1,                      // Access directly
    1,                      // RangeNumbers
	// {start address, the flash size, sector size}
    {{0x0, 0x1000000, 0x2000}}
};
