#ifndef __MCU_H__
#define __MCU_H__

#include "Std_Types.h"

typedef uint32_t Mcu_ClockPrehiralType;
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
    Mcu_ClockPrehiralType AhbEnable;
    Mcu_ClockPrehiralType Apb2Enable;
    Mcu_ClockPrehiralType Apb1Enable;
} MCU_PrehiralConfigType;
typedef struct
{
    Mcu_ClockType ClockSrc;
    Mcu_ClockType AhbPrescale;
    Mcu_ClockType Apb2Prescale;
    Mcu_ClockType Apb1Prescale;
    MCU_PrehiralConfigType *PrehiralConfig;
} Mcu_ClockConfigType;

typedef struct
{
    Mcu_ModeType Mode;
} Mcu_PowerModeConfigType;

typedef struct
{

} Mcu_RamSectionConfigType;
typedef struct
{
    Mcu_ClockConfigType *ClockConfig;
    Mcu_RamSectionConfigType *RamSectionConfig;
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