#include "Crypto.h"
#include "Crypto_Cfg.h"
#include "Det.h"
#include "Crypto_Logic.h"

static const Crypto_ConfigType *Crypto_LocalConfig = NULL;
uint8 Key[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

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
            if (job->jobConfig->service == CRYPTO_SERVICE_MAC_GEN)
            {
                switch (job->jobConfig->algorithm)
                {
                case CRYPTO_ALGOFAM_AES_128:
                    AES128_CBC_MAC_Generate(job->jobData.inputPtr,
                                            job->jobData.inputLength,
                                            Key,
                                            job->jobData.outputPtr);
                    break;
                default:
                    break;
                }
            }
            if (job->jobConfig->service == CRYPTO_SERVICE_MAC_VER)
            {
                switch (job->jobConfig->algorithm)
                {
                case CRYPTO_ALGOFAM_AES_128:
                    break;
                default:
                    break;
                }
            }
            break;
        }
    }
    return E_NOT_OK;
}