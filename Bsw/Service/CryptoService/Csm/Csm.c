#include "Csm.h"
#include "CryIf.h"
#include "Det.h"
#include "Csm_Cfg.h"

static const Csm_ConfigType *Csm_LocalConfig = NULL_PTR;

void Csm_Init(const Csm_ConfigType *configPtr)
{
    if (configPtr == NULL_PTR)
    {
        Det_ReportError(0, 0, 0, 0);
    }
    Csm_LocalConfig = configPtr;
}

Std_ReturnType Csm_MacGenerate(uint32 jobId,
                               Crypto_OperationModeType mode,
                               const uint8 *dataPtr,
                               uint32 dataLength,
                               uint8 *macPtr,
                               uint32 *macLengthPtr)
{
    if (Csm_LocalConfig == NULL_PTR)
    {
        Det_ReportError(0, 0, 0, 0);
        return E_NOT_OK;
    }

    for (int i = 0; i < NUMBER_OF_CSM_JOB; i++)
    {
        if (Csm_LocalConfig->Csm_JobConfig[i].JobId == jobId)
        {
            Crypto_JobConfigType JobConfigType = {
                .algorithm = CRYPTO_ALGOFAM_AES_128,
                .service = CRYPTO_SERVICE_MAC_GEN,
                .keyId = Csm_LocalConfig->Csm_JobConfig[i].KeyId,
                .jobId = Csm_LocalConfig->Csm_JobConfig->JobId,
            };

            Crypto_JobDataType JobDataType = {
                .inputPtr = dataPtr,
                .inputLength = dataLength,
                .outputPtr = macPtr,
                .outputLengthPtr = macLengthPtr,
                .verifyPtr = CRYPTO_E_VER_OK,
                .secondaryInputPtr = NULL_PTR,
                .secondaryInputLength = 0,
            };

            Crypto_JobType JobType = {
                .jobConfig = &JobConfigType,
                .jobData = JobDataType,
            };

            CryIf_ProcessJob(Csm_LocalConfig->Csm_JobConfig[i].ChannelId, &JobType);
        }
    }
    return E_OK;
}

Std_ReturnType Csm_MacVerify(uint32 jobId,
                             Crypto_OperationModeType mode,
                             const uint8 *dataPtr,
                             uint32 dataLength,
                             const uint8 *macPtr,
                             uint32 macLength,
                             Crypto_VerifyResultType *verifyPtr)
{
    for (int i = 0; i < NUMBER_OF_CSM_JOB; i++)
    {
        if (Csm_LocalConfig->Csm_JobConfig[i].JobId == jobId)
        {
            uint8 MacData[macLength];
            for (uint8 i = 0; i < macLength; i++)
            {
                MacData[i] = macPtr[i];
            }

            Crypto_JobConfigType JobConfigType = {
                .algorithm = CRYPTO_ALGOFAM_AES_128,
                .service = CRYPTO_SERVICE_MAC_VER,
                .keyId = Csm_LocalConfig->Csm_JobConfig[i].KeyId,
                .jobId = Csm_LocalConfig->Csm_JobConfig[i].JobId,
            };

            Crypto_JobDataType JobDataType = {
                .inputPtr = dataPtr,
                .inputLength = dataLength,
                .outputPtr = MacData,
                .outputLengthPtr = &macLength,
                .verifyPtr = verifyPtr,
                .secondaryInputPtr = NULL_PTR,
                .secondaryInputLength = 0,
            };

            Crypto_JobType JobType = {
                .jobConfig = &JobConfigType,
                .jobData = JobDataType,
            };
            CryIf_ProcessJob(Csm_LocalConfig->Csm_JobConfig[i].ChannelId, &JobType);
        }
    }
    return E_OK;
}

Std_ReturnType Csm_KeyElementSet(uint32 keyId,
                                 uint32 keyElementId,
                                 const uint8 *keyElementPtr,
                                 uint32 keyElementLength)
{
    CryIf_KeyElementSet(keyId, keyElementId, keyElementPtr, keyElementLength);
    return E_OK;
}