#ifndef KEY_MANAGER__
#define KEY_MANAGER__

#include "Std_GeneralTypes.h"
#include "Csm.h"
#include "NvM.h"

#define KEYM_START_OEM_PRODUCTIONMODE 1
#define KEYM_START_WORKSHOPMODE 2

typedef uint16 KeyM_CryptoKeyIdType;
typedef uint8 KeyM_StartType;
typedef uint8 *KeyM_CertDataPointerType;
typedef uint16 KeyM_CertElementIdType;
typedef uint16 KeyM_CertificateIdType;

typedef struct
{

} KeyM_ConfigType;

typedef enum
{
    KEYM_KH_UPDATE_KEY_UPDATE_REPEAT,
    KEYM_KH_UPDATE_FINISH,
} KeyM_KH_UpdateOperationType;

typedef struct
{

} KeyM_CertElementIteratorType;

void KeyM_Init(const KeyM_ConfigType *ConfigPtr);

void KeyM_Deinit(void);

Std_ReturnType KeyM_Start(KeyM_StartType StartType,
                          const uint8 *RequestData,
                          uint16 RequestDataLength,
                          uint8 *ResponseData,
                          uint16 *ResponseDataLength);

Std_ReturnType KeyM_Prepare(const uint8 *RequestData,
                            uint16 RequestDataLength,
                            uint8 *ResponseData,
                            uint16 *ResponseDataLength);

Std_ReturnType KeyM_Update(const uint8 *KeyNamePtr,
                           uint16 KeyNameLength,
                           const uint8 *RequestDataPtr,
                           uint16 RequestDataLength,
                           uint8 *ResultDataPtr,
                           uint16 ResultDataMaxLength);

Std_ReturnType KeyM_Finalize(const uint8 *RequestDataPtr,
                             uint16 RequestDataLength,
                             uint8 *ResponseDataPtr,
                             uint16 ResponseMaxDataLength);

Std_ReturnType KeyM_Verify(const uint8 *KeyNamePtr,
                           uint16 KeyNameLength,
                           const uint8 *RequestData,
                           uint16 RequestDataLength,
                           uint8 *ResponseData,
                           uint16 *ResponseDataLength);

// Std_ReturnType KeyM_ServiceCertificate(KeyM_ServiceCertificateType Service,
//                                        const uint8 *CertNamePtr,
//                                        uint32 CertNameLength,
//                                        const uint8 *RequestData,
//                                        uint32 RequestDataLength,
//                                        uint8 *ResponseData,
//                                        uint32 *ResponseDataLength);

// Std_ReturnType KeyM_ServiceCertificateByCertId(KeyM_CertificateIdType CertId,
//                                                KeyM_ServiceCertificateType Service,
//                                                const uint8 *RequestData,
//                                                uint32 RequestDataLength,
//                                                uint8 *ResponseData,
//                                                uint32 *ResponseDataLength);

// Std_ReturnType KeyM_SetCertificate(KeyM_CertificateIdType CertId,
//                                    const KeyM_CertDataType *CertificateDataPtr);

// Std_ReturnType KeyM_GetCertificate(KeyM_CertificateIdType CertId,
//                                    KeyM_CertDataType *CertificateDataPtr);

// Std_ReturnType KeyM_VerifyCertificates(KeyM_CertificateIdType CertId,
//                                        KeyM_CertificateIdType CertUpperId);

// Std_ReturnType KeyM_VerifyCertificate(KeyM_CertificateIdType CertId);

// Std_ReturnType KeyM_VerifyCertificateChain(KeyM_CertificateIdType CertId,
//                                            const KeyM_CertDataType[] certChainData,
//                                            uint8 NumberOfCertificates);

// Std_ReturnType KeyM_CertElementGet(KeyM_CertificateIdType CertId,
//                                    KeyM_CertElementIdType CertElementId,
//                                    uint8 *CertElementData,
//                                    uint32 *CertElementDataLength);

// Std_ReturnType KeyM_CertificateElementGetByIndex(KeyM_CertificateIdType CertId,
//                                                  KeyM_CertElementIdType CertElementId,
//                                                  uint16 Index,
//                                                  uint8 *CertElementDataPtr,
//                                                  uint32 *CertElementDataLengthPtr);

// Std_ReturnType KeyM_CertificateElementGetCount(KeyM_CertificateIdType CertId,
//                                                KeyM_CertElementIdType CertElementId,
//                                                uint16 *CountPtr);

// Std_ReturnType KeyM_CertElementGetFirst(KeyM_CertificateIdType CertId,
//                                         KeyM_CertElementIdType CertElementId,
//                                         KeyM_CertElementIteratorType *CertElementIterator,
//                                         uint8 *CertElementData,
//                                         uint32 *CertElementDataLength);

// Std_ReturnType KeyM_CertElementGetNext(KeyM_CertElementIteratorType *CertElementIterator,
//                                        uint8 *CertElementData,
//                                        uint32 *CertElementDataLength);

// Std_ReturnType KeyM_CertGetStatus(KeyM_CertificateIdType CertId,
//                                   KeyM_CertificateStatusType *Status);

void KeyM_MainFunction(void);

#endif