#ifndef FLASH_H__
#define FLASH_H__

#include "Std_GeneralTypes.h"
#include "MemAcc_GeneralTypes.h"

Std_ReturnType Mem_Write(uint8 instanceId,
                         uint8 *targetAddress,
                         const uint8 *sourceDataPtr,
                         uint8 length);

#endif