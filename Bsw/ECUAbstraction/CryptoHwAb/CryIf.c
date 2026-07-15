#include "CryIf.h"
#include "Crypto.h"

Std_ReturnType CryIf_ProcessJob(uint32 channelId, Crypto_JobType *job)
{
    Crypto_ProcessJob(0, job);
    return E_OK;
}

Std_ReturnType CryIf_KeyElementSet(uint32 cryIfKeyId,
                                   uint32 keyElementId,
                                   const uint8 *keyPtr,
                                   uint32 keyLength)
{
    Crypto_KeyElementSet(cryIfKeyId, keyElementId, keyPtr, keyLength);
    return E_OK;
}