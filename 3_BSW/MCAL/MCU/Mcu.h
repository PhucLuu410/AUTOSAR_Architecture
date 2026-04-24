#ifndef __MCU_H__
#define __MCU_H__

#include "Std_Types.h"

#define MCU_HSI_CLOCK 0
#define MCU_HSE_CLOCK 1
#define MCU_PLL_CLOCK 2

#define MCU_CALIB_OFF 0
#define MCU_CALIB_ON 1

#define MCU_WDT_DISABLE 0
#define MCU_WDT_ENABLE 1

#define MCU_MASTER_CLOCK_OUTPUT_DISABLE 0
#define MCU_MASTER_CLOCK_OUTPUT_ENABLE 1

#define MCU_RTC_CLOCK_OFF 0
#define MCU_RTC_CLOCK_LSE 1
#define MCU_RTC_CLOCK_LSI 2

#define MCU_CSS_DISABLE 0
#define MCU_CSS_ENABLE 1

#define MCU_PLL_DISABLE 0
#define MCU_PLL_ENABLE 1

typedef uint8_t Mcu_ClockType;
typedef uint8_t Mcu_RawResetType;
typedef uint8_t Mcu_ModeType;
typedef uint8_t Mcu_RamSectionType;

typedef enum
{
    MCU_PLL_LOCKED,
    MCU_PLL_UNLOCKED,
    MCU_PLL_STATUS_UNDEFINED
} Mcu_PllStatusType;

typedef enum
{
    MCU_POWER_ON_RESET,
    MCU_WATCHDOG_RESET,
    MCU_SW_RESET,
    MCU_RESET_UNDEFINED

} Mcu_ResetType;

typedef enum
{
    MCU_RAMSTATE_INVALID,
    MCU_RAMSTATE_VALID
} Mcu_RamStateType;

typedef enum
{
    HSE_Crystal_External_Clock,
    HSE_User_External_Clock,
} Mcu_HSEClockSourceType;

typedef struct
{
    Mcu_ClockType ClockType;
} Mcu_ConfigHSIType;

typedef struct
{
    Mcu_ClockType ClockType;
    Mcu_HSEClockSourceType HSESource;
    Mcu_ClockType CSSType;
} Mcu_ConfigHSEType;

typedef struct
{
    Mcu_ConfigHSIType *HSIClockType;
    Mcu_ConfigHSEType *HSEClockType;
    Mcu_ClockType PLLChoose;
    Mcu_ClockType PLLSrc;
    Mcu_ClockType PLLMulti;
    Mcu_ClockType McuMCO;
    Mcu_ClockType SystemClock;
    Mcu_ClockType McuAHBPrescale;
    Mcu_ClockType McuAPB2Prescale;
    Mcu_ClockType McuAPB1Prescale;
} Mcu_ConfigType;

void Mcu_Init(const Mcu_ConfigType *ConfigPtr);
Std_ReturnType Mcu_InitRamSection(Mcu_RamSectionType RamSection);
Std_ReturnType Mcu_InitClock(Mcu_ClockType ClockSetting);
Std_ReturnType Mcu_DistributePllClock(void);
Mcu_PllStatusType Mcu_GetPllStatus(void);
Mcu_ResetType Mcu_GetResetReason(void);
Mcu_RawResetType Mcu_GetResetRawValue(void);
void Mcu_PerformReset(void);
void Mcu_SetMode(Mcu_ModeType McuMode);
void Mcu_GetVersionInfo(Std_VersionInfoType *versioninfo);
Mcu_RamStateType Mcu_GetRamState(void);

#endif