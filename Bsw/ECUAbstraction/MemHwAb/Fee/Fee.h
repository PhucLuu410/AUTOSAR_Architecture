#ifndef FEE_H__
#define FEE_H__

#include "Std_GeneralTypes.h"
#include "Flash.h"

Std_ReturnType Fee_Write(uint16 BlockNumber, const uint8 *DataBufferPtr);
Std_ReturnType Fee_Read(uint16 BlockNumber,
                        uint16 BlockOffset,
                        uint8 *DataBufferPtr,
                        uint16 Length);
Std_ReturnType Fee_EraseImmediateBlock(uint16 BlockNumber);
#endif