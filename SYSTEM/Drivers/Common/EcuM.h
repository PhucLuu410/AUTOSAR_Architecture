#ifndef ECUM_H
#define ECUM_H

/* Chèn các thư viện tiêu chuẩn của AUTOSAR */
#include "Std_Types.h"

/* -------------------------------------------------------------------------- */
/*                                  Macros                                    */
/* -------------------------------------------------------------------------- */

/* Định nghĩa các trạng thái chính của ECU theo AUTOSAR */
typedef uint8 EcuM_StateType;

#define ECUM_STATE_STARTUP ((EcuM_StateType)0x10)
#define ECUM_STATE_RUN ((EcuM_StateType)0x30)
#define ECUM_STATE_POST_RUN ((EcuM_StateType)0x31)
#define ECUM_STATE_SLEEP ((EcuM_StateType)0x50)
#define ECUM_STATE_SHUTDOWN ((EcuM_StateType)0x90)
#define ECUM_STATE_OFF ((EcuM_StateType)0xFF)

/* -------------------------------------------------------------------------- */
/*                          Kiểu dữ liệu cấu hình                             */
/* -------------------------------------------------------------------------- */

typedef struct
{
    // Trong thực tế, đây là nơi chứa con trỏ tới cấu hình các Driver (MCU, PORT, CAN...)
    uint32 DefaultShutdownTarget;
} EcuM_ConfigType;

/* -------------------------------------------------------------------------- */
/*                          Nguyên mẫu hàm (Prototypes)                       */
/* -------------------------------------------------------------------------- */

/**
 * @brief Khởi tạo EcuM. Đây thường là hàm đầu tiên được gọi trong main().
 */
void EcuM_Init(void);

/**
 * @brief Hàm điều hướng chính để chuyển đổi giữa các trạng thái.
 */
void EcuM_MainFunction(void);

/**
 * @brief Yêu cầu chuyển sang một trạng thái nhất định (ví dụ từ Run sang PostRun).
 */
void EcuM_SetState(EcuM_StateType State);

/**
 * @brief Lấy trạng thái hiện tại của ECU.
 */
EcuM_StateType EcuM_GetState(void);

/**
 * @brief Các hàm Hook (Callouts) - Nơi người dùng thực hiện khởi tạo phần cứng cụ thể.
 */
void EcuM_AL_DriverInitOne(void); // Khởi tạo các Driver cơ bản (OS, MCU...)
void EcuM_AL_DriverInitTwo(void); // Khởi tạo các Driver phức tạp hơn (CAN, CANIF...)

#endif /* ECUM_H */