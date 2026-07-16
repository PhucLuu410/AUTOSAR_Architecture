#include "Flash.h"
#include "stm32f103xb.h"

void Mem_Init(const Mem_ConfigType *configPtr)
{
    FLASH->KEYR = 0x45670123;
    FLASH->KEYR = 0xCDEF89AB;
}

Std_ReturnType Mem_Write(Mem_InstanceIdType instanceId,
                         Mem_AddressType targetAddress,
                         const Mem_DataType *sourceDataPtr,
                         Mem_LengthType length)
{
    if (FLASH->CR & (1 << 7))
    {
        return E_NOT_OK;
    }
    uint16 DataWrite = (*sourceDataPtr);
    FLASH->CR |= (1 << 0);
    while (FLASH->SR & (1 << 0))
        ;
    *(volatile uint16 *)targetAddress = DataWrite;
    while ((FLASH->SR & (1 << 0)))
        ;

    FLASH->CR &= ~(1 << 0);

    return E_OK;
}

Std_ReturnType Mem_Read(Mem_InstanceIdType instanceId,
                        Mem_AddressType sourceAddress,
                        Mem_DataType *destinationDataPtr,
                        Mem_LengthType length)
{
    *destinationDataPtr = *((volatile uint32 *)sourceAddress);
    return E_OK;
}

Std_ReturnType Mem_Erase(Mem_InstanceIdType instanceId,
                         Mem_AddressType targetAddress,
                         Mem_LengthType length)
{
    if (FLASH->CR & (1 << 7))
    {
        return E_NOT_OK;
    }
    FLASH->CR |= (1 << 1);
    FLASH->AR |= targetAddress;
    FLASH->CR |= (1 << 6);
    while (FLASH->SR & (1 << 0))
        ;
    FLASH->CR &= ~(1 << 1);
    return E_OK;
}

Std_ReturnType Mem_BlankCheck(Mem_InstanceIdType instanceId,
                              Mem_AddressType targetAddress,
                              Mem_LengthType length)
{
    if (*(volatile uint8 *)(targetAddress) != 0xFF)
    {
        return E_NOT_OK;
    }
    return E_OK;
}
