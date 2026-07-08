/*******************************************************************************
 * @file    Crypto_Types.h
 * @brief   Crypto Stack - Type Definitions
 * @details Định nghĩa các kiểu dữ liệu, enum, và structure cho Crypto Stack
 *          Bao gồm: Operation modes, result types, key structures, job types
 *
 * @author  HALA Academy
 * @version 1.0.0
 * @date    2026-01-02
 *
 * @note    Tuân thủ AUTOSAR Classic Platform R22-11 Crypto Stack
 ******************************************************************************/

#ifndef CRYPTO_TYPES_H
#define CRYPTO_TYPES_H

/*===========================================================================*/
/*                              INCLUDES                                      */
/*===========================================================================*/
#include "Std_GeneralTypes.h"

/*===========================================================================*/
/*                    HẰNG SỐ KÍCH THƯỚC SHA-256                              */
/*===========================================================================*/
/**
 * @brief Kích thước digest SHA-256 (32 bytes = 256 bits)
 */
#define CRYPTO_SHA256_DIGEST_SIZE 32u

/**
 * @brief Kích thước block SHA-256 (64 bytes = 512 bits)
 */
#define CRYPTO_SHA256_BLOCK_SIZE 64u

/*===========================================================================*/
/*                    HẰNG SỐ KÍCH THƯỚC ECDSA P-256                          */
/*===========================================================================*/
/**
 * @brief Kích thước private key ECDSA P-256 (32 bytes = 256 bits)
 */
#define CRYPTO_ECDSA_P256_KEY_SIZE 32u

/**
 * @brief Kích thước signature ECDSA (64 bytes = R(32) + S(32))
 */
#define CRYPTO_ECDSA_P256_SIG_SIZE 64u

/**
 * @brief Kích thước public key ECDSA (64 bytes = X(32) + Y(32))
 * @note  Đây là dạng uncompressed, không bao gồm prefix byte
 */
#define CRYPTO_ECDSA_P256_PUBKEY_SIZE 64u

/*===========================================================================*/
/*                    CHẾ ĐỘ HOẠT ĐỘNG (OPERATION MODE)                       */
/*===========================================================================*/
/**
 * @brief Chế độ hoạt động cho các API Crypto
 * @details Hỗ trợ xử lý streaming cho dữ liệu lớn
 *
 * Ví dụ streaming mode:
 * - START:  Khởi tạo context mới
 * - UPDATE: Thêm data chunks (có thể gọi nhiều lần)
 * - FINISH: Kết thúc và xuất kết quả
 *
 * Ví dụ single call:
 * - SINGLECALL = START + UPDATE + FINISH trong 1 lần gọi
 */
typedef enum
{
    CRYPTO_OPERATIONMODE_START = 0x01u,
    CRYPTO_OPERATIONMODE_UPDATE = 0x02u,
    CRYPTO_OPERATIONMODE_FINISH = 0x04u,
    CRYPTO_OPERATIONMODE_STREAMSTART = 0x03u,
    CRYPTO_OPERATIONMODE_SINGLECALL = 0x07u
} Crypto_OperationModeType;

/*===========================================================================*/
/*                    KẾT QUẢ XỬ LÝ CRYPTO                                    */
/*===========================================================================*/
/**
 * @brief Kết quả trả về từ các hàm Crypto
 */
typedef enum
{
    CRYPTO_E_OK = 0x00u,
    CRYPTO_E_BUSY = 0x01u,
    CRYPTO_E_SMALL_BUFFER = 0x02u,
    CRYPTO_E_KEY_NOT_VALID = 0x03u,
    CRYPTO_E_KEY_SIZE_MISMATCH = 0x04u,
    CRYPTO_E_NOT_OK = 0x05u

} Crypto_ResultType;

/*===========================================================================*/
/*                    KẾT QUẢ XÁC THỰC                                        */
/*===========================================================================*/
/**
 * @brief Kết quả xác thực cho Signature và MAC
 */
typedef enum
{
    CRYPTO_E_VER_OK = 0x00u,
    CRYPTO_E_VER_NOT_OK = 0x01u
} Crypto_VerifyResultType;

/*===========================================================================*/
/*                    ALGORITHM FAMILY                                        */
/*===========================================================================*/
/**
 * @brief Họ thuật toán crypto được hỗ trợ
 * @note  Theo AUTOSAR Crypto Stack, đây là các algorithm family tiêu chuẩn
 */
typedef enum
{
    CRYPTO_ALGOFAM_SHA2_256 = 0x01u,
    CRYPTO_ALGOFAM_ECCNIST_P256 = 0x02u,
    CRYPTO_ALGOFAM_AES_128 = 0x03u
} Crypto_AlgorithmFamilyType;

/*===========================================================================*/
/*                    SERVICE TYPE                                            */
/*===========================================================================*/
/**
 * @brief Loại dịch vụ crypto
 */
typedef enum
{
    CRYPTO_SERVICE_HASH = 0x01u,
    CRYPTO_SERVICE_SIGNATURE_GEN = 0x02u,
    CRYPTO_SERVICE_SIGNATURE_VER = 0x03u,
    CRYPTO_SERVICE_MAC_GEN = 0x04u,
    CRYPTO_SERVICE_MAC_VER = 0x05u,
    CRYPTO_SERVICE_ENCRYPT = 0x06u,
    CRYPTO_SERVICE_DECRYPT = 0x07u,
} Crypto_ServiceType;

/*===========================================================================*/
/*                    KEY ELEMENT IDs                                         */
/*===========================================================================*/
/**
 * @brief ID của phần tử key cho ECDSA signing (private key)
 */
#define CRYPTO_KE_SIGNATURE_KEY 1u

/**
 * @brief ID của phần tử key cho ECDSA verification (public key)
 */
#define CRYPTO_KE_VERIFY_KEY 2u

/*===========================================================================*/
/*                    KEY SLOT IDs cho Demo                                   */
/*===========================================================================*/
/**
 * @brief Số lượng key slots tối đa trong Crypto Driver
 */
#define CRYPTO_MAX_KEY_SLOTS 4u

/**
 * @brief Key slot ID cho signing
 */
#define KEY_SLOT_SIGN 0u

/**
 * @brief Key slot ID cho verification
 */
#define KEY_SLOT_VERIFY 1u

/*===========================================================================*/
/*                    JOB IDs cho Demo                                        */
/*===========================================================================*/
/**
 * @brief Job ID cho SHA-256 hash
 */
#define JOB_ID_HASH_SHA256 1u

/**
 * @brief Job ID cho ECDSA signature generation
 */
#define JOB_ID_SIGN 2u

/**
 * @brief Job ID cho ECDSA signature verification
 */
#define JOB_ID_VERIFY 3u

/*===========================================================================*/
/*                    ECDSA KEY PAIR STRUCTURE                                */
/*===========================================================================*/
/**
 * @brief Structure chứa cặp khóa ECDSA P-256
 *
 * @details
 * - Private key: Số bí mật dùng để KÝ, KHÔNG được chia sẻ
 * - Public key (X,Y): Tọa độ điểm trên curve, dùng để VERIFY, có thể chia sẻ
 *
 * Trong hệ thống thực:
 * - Private key nên được lưu trong HSM (Hardware Security Module)
 * - Public key có thể được nhúng trong certificate hoặc pre-provisioned
 */
typedef struct
{
    /**
     * @brief Private key (scalar d), 32 bytes
     * @warning PHẢI GIỮ BÍ MẬT! Không được log hoặc truyền qua mạng
     */
    uint8 privateKey[CRYPTO_ECDSA_P256_KEY_SIZE];

    /**
     * @brief Tọa độ X của public key, 32 bytes
     */
    uint8 publicKeyX[CRYPTO_ECDSA_P256_KEY_SIZE];

    /**
     * @brief Tọa độ Y của public key, 32 bytes
     */
    uint8 publicKeyY[CRYPTO_ECDSA_P256_KEY_SIZE];

    /**
     * @brief Cờ đánh dấu key đã được khởi tạo và hợp lệ
     */
    bool isValid;

} Crypto_ECDSA_KeyPairType;

/*===========================================================================*/
/*                    JOB CONFIGURATION STRUCTURE                             */
/*===========================================================================*/
/**
 * @brief Cấu hình cho một Crypto Job
 *
 * @details Job là đơn vị công việc trong Crypto Stack:
 * - Mỗi job có ID duy nhất
 * - Job được cấu hình với service type, algorithm, và key
 * - CSM dùng jobId để tra cứu cấu hình
 */
typedef struct
{
    uint32 jobId;
    Crypto_ServiceType service;
    Crypto_AlgorithmFamilyType algorithm;
    uint32 keyId;
} Crypto_JobConfigType;

/*===========================================================================*/
/*                    JOB RUNTIME DATA STRUCTURE                              */
/*===========================================================================*/
/**
 * @brief Dữ liệu runtime cho một Crypto Job
 *
 * @details Chứa các thông tin input/output khi thực hiện job:
 * - Input data pointer và length
 * - Output buffer pointer và length
 * - Secondary input (signature để verify)
 * - Kết quả verify
 */
typedef struct
{
    Crypto_OperationModeType mode;
    const uint8 *inputPtr;
    uint32 inputLength;
    uint8 *outputPtr;
    uint32 *outputLengthPtr;
    Crypto_VerifyResultType *verifyPtr;
    const uint8 *secondaryInputPtr;
    uint32 secondaryInputLength;
} Crypto_JobDataType;

/*===========================================================================*/
/*                    COMPLETE JOB STRUCTURE                                  */
/*===========================================================================*/
/**
 * @brief Structure hoàn chỉnh cho một Crypto Job
 *
 * @details Kết hợp:
 * - Cấu hình job (static, định nghĩa lúc config)
 * - Dữ liệu job (runtime, thay đổi mỗi lần gọi)
 */
typedef struct
{
    const Crypto_JobConfigType *jobConfig;
    Crypto_JobDataType jobData;
} Crypto_JobType;

#endif /* CRYPTO_TYPES_H */
