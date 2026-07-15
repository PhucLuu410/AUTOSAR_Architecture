#ifndef NvM_H__
#define NvM_H__

#include "Std_GeneralTypes.h"
#include "Fee.h"

Std_ReturnType MemIf_Write(uint16 DeviceIndex, uint16 BlockNumber, const uint8 *DataBufferPtr);

#endif