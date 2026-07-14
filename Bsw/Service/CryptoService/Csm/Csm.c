#include "Csm.h"
#include "CryIf.h"

Std_ReturnType Csm_MacGenerate(uint32 jobId,
                               Crypto_OperationModeType mode,
                               const uint8 *dataPtr,
                               uint32 dataLength,
                               uint8 *macPtr,
                               uint32 *macLengthPtr)
{
    Crypto_JobConfigType JobConfigType = {
        .algorithm = CRYPTO_ALGOFAM_AES_128,
        .service = CRYPTO_SERVICE_MAC_GEN,
        .keyId = 0,
        .jobId = jobId,
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

    CryIf_ProcessJob(0, &JobType);
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

    uint8 MacData[macLength];
    for (uint8 i = 0; i < macLength; i++)
    {
        MacData[i] = macPtr[i];
    }

    Crypto_JobConfigType JobConfigType = {
        .algorithm = CRYPTO_ALGOFAM_AES_128,
        .service = CRYPTO_SERVICE_MAC_VER,
        .keyId = 0,
        .jobId = jobId,
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

    CryIf_ProcessJob(0, &JobType);
    return E_OK;
}