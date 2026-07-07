#ifndef CRYPTO_H
#define CRYPTO_H

#include "Crypto_GeneralTypes.h"
#include "Std_Types.h"
// #include "Rte_Csm_Types.h"
// #include "Rte_NvM_Type.h"

#define CRYPTO_MAX_KEY_ELEMENTS 2
#define CRYPTO_MAX_KEY_SIZE 16

typedef struct
{
    uint32 elementId;
    uint8 data[CRYPTO_MAX_KEY_SIZE];
    uint32 length;
} Crypto_KeyElementType;

typedef struct
{
    uint32 keyId;
    boolean isValid;
    Crypto_KeyElementType elements[CRYPTO_MAX_KEY_ELEMENTS];
} Crypto_KeyType;

typedef struct
{
    Crypto_KeyType *keyStorage;
    uint32 numberOfKeys;
} Crypto_ConfigType;

void Crypto_Init(const Crypto_ConfigType *configPtr);
Std_ReturnType Crypto_ProcessJob(uint32 objectId, Crypto_JobType *job);
Std_ReturnType Crypto_CancelJob(uint32 objectId, Crypto_JobType *job);
Std_ReturnType Crypto_KeyElementSet(uint32 cryptoKeyId, uint32 keyElementId, const uint8 *keyPtr, uint32 keyLength);
Std_ReturnType Crypto_KeySetValid(uint32 cryptoKeyId);
Std_ReturnType Crypto_KeyElementGet(uint32 cryptoKeyId, uint32 keyElementId, uint8 *resultPtr, uint32 *resultLengthPtr);

#endif