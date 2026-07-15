#include "NvM.h"

Std_ReturnType MemIf_Write(uint16 DeviceIndex, uint16 BlockNumber, const uint8 *DataBufferPtr)
{
    Fee_Write(BlockNumber, DataBufferPtr);
    return E_OK;
}