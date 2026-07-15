#ifndef CSM_H__
#define CSM_H__

#include "Std_GeneralTypes.h"
#include "Crypto_GeneralTypes.h"

typedef struct
{
    uint8 KeyId;
    uint8 JobId;
    uint8 ChannelId;
} Csm_JobConfigType;
typedef struct
{
    Csm_JobConfigType *Csm_JobConfig;
} Csm_ConfigType;

void Csm_Init(const Csm_ConfigType *configPtr);

Std_ReturnType Csm_MacGenerate(uint32 jobId,
                               Crypto_OperationModeType mode,
                               const uint8 *dataPtr,
                               uint32 dataLength,
                               uint8 *macPtr,
                               uint32 *macLengthPtr);

Std_ReturnType Csm_MacVerify(uint32 jobId,
                             Crypto_OperationModeType mode,
                             const uint8 *dataPtr,
                             uint32 dataLength,
                             const uint8 *macPtr,
                             uint32 macLength,
                             Crypto_VerifyResultType *verifyPtr);

Std_ReturnType Csm_KeyElementSet(uint32 keyId,
                                 uint32 keyElementId,
                                 const uint8 *keyElementPtr,
                                 uint32 keyElementLength);

#endif