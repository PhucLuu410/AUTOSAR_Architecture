#ifndef CRYIF_H__
#define CRYIF_H__

#include "Crypto_GeneralTypes.h"
#include "Std_GeneralTypes.h"
// #include "Rte_Csm_Type.h "

typedef struct
{
    uint8 CryIfChannelId;
    uint8 CryIfObjectId;
} CryIf_ChannelConfig;

typedef struct
{
    CryIf_ChannelConfig *CryIfChannel;
} CryIf_ConfigType;

void CryIf_Init(const CryIf_ConfigType *configPtr);
Std_ReturnType CryIf_ProcessJob(uint32 channelId, Crypto_JobType *job);
Std_ReturnType CryIf_KeyElementSet(uint32 cryIfKeyId,
                                   uint32 keyElementId,
                                   const uint8 *keyPtr,
                                   uint32 keyLength);

#endif