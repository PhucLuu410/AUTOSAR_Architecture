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
            if (job->jobConfig->service == CRYPTO_SERVICE_MAC_GEN)
            {
                switch (job->jobConfig->algorithm)
                {
                case CRYPTO_ALGOFAM_AES_128:
                    for (int j = 0; j < NUMBER_OF_KEY; j++)
                    {
                        if (KeyId[i].KeyId == job->jobConfig->keyId)
                        {
                            AES128_MAC_Generate(job->jobData.inputPtr,
                                                job->jobData.inputLength,
                                                KeyId[j].KeyData,
                                                job->jobData.outputPtr);
                        }
                    }
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
                    for (int j = 0; j < NUMBER_OF_KEY; j++)
                    {
                        if (KeyId[i].KeyId == job->jobConfig->keyId)
                        {
                            if (AES128_MAC_Verify(job->jobData.inputPtr,
                                                  job->jobData.inputLength,
                                                  KeyId[j].KeyData,
                                                  job->jobData.outputPtr))
                            {
                                *job->jobData.verifyPtr = CRYPTO_E_VER_OK;
                            }
                            else
                            {
                                *job->jobData.verifyPtr = CRYPTO_E_VER_NOT_OK;
                            }
                        }
                    }
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