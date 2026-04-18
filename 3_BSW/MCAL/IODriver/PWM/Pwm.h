// Target : Xuất PWM ra 1 chân
#ifndef PWM_H
#define PWM_H

#include "Std_Types.h"
#include "stm32f103xb.h"
#include "stdint.h"

typedef uint16_t Pwm_ChannelType;
typedef uint16_t Pwm_PeriodType;
typedef uint16_t Pwm_DutyCycleType;
typedef uint8_t Pwm_PowerStateType;
typedef uint8_t Pwm_ModeType;
typedef uint8_t Pwm_AlignModeType;
typedef uint16_t Pwm_FrequencyType;
typedef enum
{
    PWM_HIGH,
    PWM_LOW
} Pwm_OutputStateType;

typedef enum
{
    PWM_RISING_EDGE,
    PWM_FALLING_EDGE,
    PWM_BOTH_EDGES
} Pwm_EdgeNotificationType;

typedef enum
{
    PWM_VARIABLE_PERIOD,
    PWM_FIXED_PERIOD,
    PWM_FIXED_PERIOD_SHIFTED
} Pwm_ChannelClassType;

typedef struct
{
    Pwm_ChannelType ChannelNumber;
    Pwm_ModeType ChannelMode;
    Pwm_AlignModeType AlignMode;
    Pwm_PeriodType Period;
    Pwm_FrequencyType Frequency;
} Pwm_ConfigType;

typedef enum
{
    PWM_SERVICE_ACCEPTED,
    PWM_NOT_INIT,
    PWM_SEQUENCE_ERROR,
    PWM_HW_FAILURE,
    PWM_POWER_STATE_NOT_SUPP,
    PWM_TRANS_NOT_POSSIBLE
} Pwm_PowerStateRequestResultType;

void Pwm_Init(const Pwm_ConfigType *ConfigPtr);
void Pwm_DeInit(void);
void Pwm_SetDutyCycle(Pwm_ChannelType ChannelNumber, uint16 DutyCycle);
void Pwm_SetPeriodAndDuty(Pwm_ChannelType ChannelNumber, Pwm_PeriodType Period, uint16 DutyCycle);
void Pwm_SetOutputToIdle(Pwm_ChannelType ChannelNumber);
Pwm_OutputStateType Pwm_GetOutputState(Pwm_ChannelType ChannelNumber);
void Pwm_DisableNotification(Pwm_ChannelType ChannelNumber);
void Pwm_EnableNotification(Pwm_ChannelType ChannelNumber, Pwm_EdgeNotificationType Notification);
Std_ReturnType Pwm_SetPowerState(Pwm_PowerStateRequestResultType *Result);
Std_ReturnType Pwm_GetCurrentPowerState(Pwm_PowerStateType *CurrentPowerState, Pwm_PowerStateRequestResultType *Result);
Std_ReturnType Pwm_GetTargetPowerState(Pwm_PowerStateType *TargetPowerState, Pwm_PowerStateRequestResultType *Result);
Std_ReturnType Pwm_PreparePowerState(Pwm_PowerStateType PowerState, Pwm_PowerStateRequestResultType *Result);
void Pwm_GetVersionInfo(Std_VersionInfoType *versioninfo);
void Pwm_Main_PowerTransitionManager(void);

#endif