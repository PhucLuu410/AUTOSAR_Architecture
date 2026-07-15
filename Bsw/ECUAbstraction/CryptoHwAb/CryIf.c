#include "CryIf.h"
#include "Crypto.h"
#include "CryIf_Cfg.h"
#include "Det.h"

static const CryIf_ConfigType *CryIf_LocalConfigType = NULL_PTR;

void CryIf_Init(const CryIf_ConfigType *configPtr)
{
    if (configPtr == NULL_PTR)
    {
        Det_ReportError(0, 0, 0, 0);
    }
    CryIf_LocalConfigType = configPtr;
}

Std_ReturnType CryIf_ProcessJob(uint32 channelId, Crypto_JobType *job)
{
    if (job == NULL_PTR)
    {
        Det_ReportError(0, 0, 0, 0);
        return E_NOT_OK;
    }

    for (int i = 0; i < NUMBER_OF_CRYIF_CHANNEL; i++)
    {
        if (CryIf_LocalConfigType->CryIfChannel[i].CryIfChannelId == channelId)
        {
            Crypto_ProcessJob(CryIf_LocalConfigType->CryIfChannel[i].CryIfObjectId, job);
        }
    }
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