#include "Crypto_GeneralTypes.h"
#include "Std_GeneralTypes.h"

// void CryIf_Init(const CryIf_ConfigType *configPtr);
Std_ReturnType CryIf_ProcessJob(uint32 channelId, Crypto_JobType *job);
Std_ReturnType CryIf_KeyElementSet(uint32 cryIfKeyId,
                                   uint32 keyElementId,
                                   const uint8 *keyPtr,
                                   uint32 keyLength);
