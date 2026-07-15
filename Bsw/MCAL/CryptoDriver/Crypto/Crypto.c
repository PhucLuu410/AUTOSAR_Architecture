#include "Crypto.h"
#include "Crypto_Cfg.h"
#include "Det.h"
#include "Crypto_Logic.h"
#include "NvM.h"

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
                        if (Crypto_LocalConfig->KeyConfig[i].KeyId == job->jobConfig->keyId)
                        {
                            AES128_MAC_Generate(job->jobData.inputPtr,
                                                job->jobData.inputLength,
                                                Crypto_LocalConfig->KeyConfig[i].KeyData,
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
                        if (Crypto_LocalConfig->KeyConfig[i].KeyId == job->jobConfig->keyId)
                        {
                            if (AES128_MAC_Verify(job->jobData.inputPtr,
                                                  job->jobData.inputLength,
                                                  Crypto_LocalConfig->KeyConfig[i].KeyData,
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
            if (job->jobConfig->service == CRYPTO_SERVICE_HASH)
            {
                switch (job->jobConfig->algorithm)
                {
                case CRYPTO_ALGOFAM_SHA2_256:
                    for (int j = 0; j < NUMBER_OF_KEY; j++)
                    {
                        if (Crypto_LocalConfig->KeyConfig[i].KeyId == job->jobConfig->keyId)
                        {
                        }
                    }
                    break;

                default:
                    break;
                }
            }
            if (job->jobConfig->service == CRYPTO_SERVICE_SIGNATURE_GEN)
            {
                switch (job->jobConfig->algorithm)
                {
                case CRYPTO_ALGOFAM_ECCNIST_P256:
                    for (int j = 0; j < NUMBER_OF_KEY; j++)
                    {
                        if (Crypto_LocalConfig->KeyConfig[i].KeyId == job->jobConfig->keyId)
                        {
                        }
                    }
                    break;

                default:
                    break;
                }
            }
            if (job->jobConfig->service == CRYPTO_SERVICE_SIGNATURE_VER)
            {
                switch (job->jobConfig->algorithm)
                {
                case CRYPTO_ALGOFAM_ECCNIST_P256:
                    for (int j = 0; j < NUMBER_OF_KEY; j++)
                    {
                        if (Crypto_LocalConfig->KeyConfig[i].KeyId == job->jobConfig->keyId)
                        {
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

Std_ReturnType Crypto_KeyElementSet(uint32 cryptoKeyId,
                                    uint32 keyElementId,
                                    const uint8 *keyPtr,
                                    uint32 keyLength)
{
    if (keyPtr == NULL_PTR || keyLength == 0 || keyElementId > NUMBER_OF_KEY)
    {
        Det_ReportError(0, 0, 0, 0);
        return E_NOT_OK;
    }
    for (int i = 0; i < NUMBER_OF_KEY; i++)
    {
        if (Crypto_LocalConfig->KeyConfig[i].KeyId == keyElementId)
        {
            for (int KeyElement = 0; KeyElement < keyLength; KeyElement++)
            {
                Crypto_LocalConfig->KeyConfig[i].KeyData[KeyElement] = keyPtr[KeyElement];
            }
            break;
        }
    }
    return E_OK;
}