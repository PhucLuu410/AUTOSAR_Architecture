#include "Std_GeneralTypes.h"
#include "Crypto_GeneralTypes.h"
Std_ReturnType Csm_MacGenerate(uint32 jobId,
                               Crypto_OperationModeType mode,
                               const uint8 *dataPtr,
                               uint32 dataLength,
                               uint8 *macPtr,
                               uint32 *macLengthPtr);

Std_ReturnType Csm_MacVerify(uint32 jobId,
                             Crypto_OperationModeType mode,
                             const uint8 *dataPtr,
                             uint32 dataLength,
                             const uint8 *macPtr,
                             uint32 macLength,
                             Crypto_VerifyResultType *verifyPtr);

Std_ReturnType Csm_KeyElementSet(uint32 keyId,
                                 uint32 keyElementId,
                                 const uint8 *keyElementPtr,
                                 uint32 keyElementLength);
