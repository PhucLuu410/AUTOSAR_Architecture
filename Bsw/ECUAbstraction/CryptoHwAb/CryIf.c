#include "CryIf.h"
#include "Crypto.h"
Std_ReturnType CryIf_ProcessJob(uint32 channelId, Crypto_JobType *job)
{
    Crypto_ProcessJob(0, job);
    return E_OK;
}