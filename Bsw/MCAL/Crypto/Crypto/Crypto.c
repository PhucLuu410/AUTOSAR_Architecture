#include "Crypto.h"
#include "Crypto_Cfg.h"
#include "Det.h"
static const Crypto_ConfigType *Crypto_LocalConfig = NULL;

void Crypto_Init(const Crypto_ConfigType *configPtr)
{
    if (configPtr != NULL)
    {
        Crypto_LocalConfig = configPtr;
    }
    else
    {
        Det_ReportError(0, 0, 0, 0);
    }
}

Std_ReturnType Crypto_ProcessJob(uint32 objectId, Crypto_JobType *job)
{
    if (Crypto_LocalConfig == NULL || job == NULL || job->jobConfig == NULL)
    {
        Det_ReportError(0, 0, 0, 0);
        return E_NOT_OK;
    }

    for (int i = 0; i < Crypto_LocalConfig->Crypto_DriverObjectCount; i++)
    {
        if (Crypto_LocalConfig->Crypto_DriverObject[i].Crypto_DriverObjectId == objectId)
        {
            switch (job->jobConfig->service)
            {
            case CRYPTO_SERVICE_HASH:

                switch (job->jobConfig->algorithm)
                {
                case CRYPTO_ALGOFAM_SHA2_256:
                    return E_OK;
                case CRYPTO_ALGOFAM_ECCNIST_P256:
                    return E_OK;
                default:
                    Det_ReportError(0, 0, 0, 0);
                    return E_NOT_OK;
                }

                return E_OK;

            case CRYPTO_SERVICE_SIGNATURE_GEN:
                return E_OK;

            default:
                Det_ReportError(0, 0, 0, 0);
                return E_NOT_OK;
            }
        }
    }
    return E_NOT_OK;
}