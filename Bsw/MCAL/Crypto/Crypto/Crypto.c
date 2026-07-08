#include "Crypto.h"
#include "Crypto_Cfg.h"
#include "Det.h"
#include "Crypto_Logic.h"

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
                    SHA256_Compute(job->jobData.inputPtr, job->jobData.inputLength, (uint32 *)job->jobData.outputPtr);
                    break;
                default:
                    Det_ReportError(0, 0, 0, 0);
                    break;
                }
                break;
            case CRYPTO_SERVICE_SIGNATURE_GEN:
                switch (job->jobConfig->algorithm)
                {
                case CRYPTO_ALGOFAM_ECCNIST_P256:
                    break;
                default:
                    Det_ReportError(0, 0, 0, 0);
                    break;
                }
                break;
            case CRYPTO_SERVICE_SIGNATURE_VER:
                switch (job->jobConfig->algorithm)
                {
                case CRYPTO_ALGOFAM_ECCNIST_P256:
                    break;
                default:
                    break;
                }
                break;
            case CRYPTO_SERVICE_MAC_GEN:
            case CRYPTO_SERVICE_MAC_VER:
            case CRYPTO_SERVICE_ENCRYPT:
                switch (job->jobConfig->algorithm)
                {
                case CRYPTO_ALGOFAM_AES_128:
                    break;
                default:
                    break;
                }
            case CRYPTO_SERVICE_DECRYPT:
                switch (job->jobConfig->algorithm)
                {
                case CRYPTO_ALGOFAM_AES_128:
                    break;
                default:
                    break;
                }
                break;
            default:
                Det_ReportError(0, 0, 0, 0);
                return E_NOT_OK;
            }
            return E_OK;
        }
    }
    return E_NOT_OK;
}