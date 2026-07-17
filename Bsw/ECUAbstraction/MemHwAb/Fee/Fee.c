#include "Fee.h"
#include "Flash.h"
#include "Flash_Cfg.h"

Std_ReturnType Fee_Write(uint16 BlockNumber, const uint8 *DataBufferPtr)
{

    Mem_Write(0, DYNAMIC_FLASH_ADDRESS + (BlockNumber * 2), DataBufferPtr, 0);
    return E_OK;
}

Std_ReturnType Fee_Read(uint16 BlockNumber,
                        uint16 BlockOffset,
                        uint8 *DataBufferPtr,
                        uint16 Length)
{
    Mem_Read(0, ((DYNAMIC_FLASH_ADDRESS + BlockOffset) + (BlockNumber * 2)), DataBufferPtr, Length);
    return E_OK;
}

Std_ReturnType Fee_EraseImmediateBlock(uint16 BlockNumber)
{
    Mem_Erase(0, DYNAMIC_FLASH_ADDRESS + BlockNumber, 0);
}