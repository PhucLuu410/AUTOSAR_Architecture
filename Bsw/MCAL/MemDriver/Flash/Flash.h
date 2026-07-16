#ifndef FLASH_H__
#define FLASH_H__

#include "Std_GeneralTypes.h"
#include "MemAcc_GeneralTypes.h"

typedef uint8 Mem_DataType;
typedef uint32 Mem_InstanceIdType;
typedef uint32 Mem_LengthType;
typedef uint32 Mem_HwServiceIdType;
typedef MemAcc_AddressType Mem_AddressType;

typedef struct
{

} Mem_ConfigType;

void Mem_Init(const Mem_ConfigType *configPtr);

Std_ReturnType Mem_Write(Mem_InstanceIdType instanceId,
                         Mem_AddressType targetAddress,
                         const Mem_DataType *sourceDataPtr,
                         Mem_LengthType length);

Std_ReturnType Mem_Read(Mem_InstanceIdType instanceId,
                        Mem_AddressType sourceAddress,
                        Mem_DataType *destinationDataPtr,
                        Mem_LengthType length);

Std_ReturnType Mem_Erase(Mem_InstanceIdType instanceId,
                         Mem_AddressType targetAddress,
                         Mem_LengthType length);

Std_ReturnType Mem_BlankCheck(Mem_InstanceIdType instanceId,
                              Mem_AddressType targetAddress,
                              Mem_LengthType length);

#endif