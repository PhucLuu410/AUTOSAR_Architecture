#ifndef CRYPTO_H
#define CRYPTO_H

#include "Crypto_GeneralTypes.h"
#include "Std_GeneralTypes.h"
// #include "Rte_Csm_Types.h"
// #include "Rte_NvM_Type.h"

typedef struct
{
    uint8 KeyId;
    uint8 *KeyData;
    uint8 KeyLength;
} KeyIdConfig;

typedef struct
{
    uint8 Crypto_DriverObjectId;
} Crypto_DriverObjectType;

typedef struct
{
    uint8 Crypto_DriverObjectCount;
    Crypto_DriverObjectType *Crypto_DriverObject;
    KeyIdConfig *KeyConfig;
} Crypto_ConfigType;

void Crypto_Init(const Crypto_ConfigType *configPtr);
Std_ReturnType Crypto_ProcessJob(uint32 objectId, Crypto_JobType *job);
Std_ReturnType Crypto_CancelJob(uint32 objectId, Crypto_JobType *job);
Std_ReturnType Crypto_KeyElementSet(uint32 cryptoKeyId, uint32 keyElementId, const uint8 *keyPtr, uint32 keyLength);
Std_ReturnType Crypto_KeySetValid(uint32 cryptoKeyId);
Std_ReturnType Crypto_KeyElementGet(uint32 cryptoKeyId, uint32 keyElementId, uint8 *resultPtr, uint32 *resultLengthPtr);

#endif