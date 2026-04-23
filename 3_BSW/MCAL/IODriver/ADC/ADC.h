#ifndef __ADC_H
#define __ADC_H

#include "stm32f103xb.h"
#include "Std_Types.h"

#define NUMBER_OF_CHANNELS 4

#define ADC_CHANNEL_0 0
#define ADC_CHANNEL_1 1
#define ADC_CHANNEL_2 2
#define ADC_CHANNEL_3 3
#define ADC_CHANNEL_4 4
#define ADC_CHANNEL_5 5
#define ADC_CHANNEL_6 6
#define ADC_CHANNEL_7 7
#define ADC_CHANNEL_8 8
#define ADC_CHANNEL_9 9
#define ADC_CHANNEL_10 10
#define ADC_CHANNEL_11 11
#define ADC_CHANNEL_12 12
#define ADC_CHANNEL_13 13
#define ADC_CHANNEL_14 14
#define ADC_CHANNEL_15 15

#define ADC_SAMPLING_TIME_1_5_CYCLES 0
#define ADC_SAMPLING_TIME_7_5_CYCLES 1
#define ADC_SAMPLING_TIME_13_5_CYCLES 2
#define ADC_SAMPLING_TIME_28_5_CYCLES 3
#define ADC_SAMPLING_TIME_41_5_CYCLES 4
#define ADC_SAMPLING_TIME_55_5_CYCLES 5
#define ADC_SAMPLING_TIME_71_5_CYCLES 6
#define ADC_SAMPLING_TIME_239_5_CYCLES 7

#define ADC_RESOLUTION_12_BIT 0

#define ADC_REFERENCE_0 0
#define ADC_REFERENCE_1 1
#define ADC_REFERENCE_2 2
#define ADC_REFERENCE_3 3
#define ADC_REFERENCE_4 4
#define ADC_REFERENCE_5 5
#define ADC_REFERENCE_6 6
#define ADC_REFERENCE_7 7
#define ADC_REFERENCE_8 8
#define ADC_REFERENCE_9 9
#define ADC_REFERENCE_10 10
#define ADC_REFERENCE_11 11
#define ADC_REFERENCE_12 12
#define ADC_REFERENCE_13 13
#define ADC_REFERENCE_14 14
#define ADC_REFERENCE_15 15

#define ADC_CLOCK_DIV_1 0
#define ADC_CLOCK_DIV_2 4
#define ADC_CLOCK_DIV_4 5
#define ADC_CLOCK_DIV_8 6
#define ADC_CLOCK_DIV_16 7

#define ADC_GROUP_0 0
#define ADC_GROUP_1 1
#define ADC_GROUP_2 2
#define ADC_GROUP_3 3
#define ADC_GROUP_4 4
#define ADC_GROUP_5 5
#define ADC_GROUP_6 6
#define ADC_GROUP_7 7

#define ADC_HWTRIGGER_TIM1_CC1 0
#define ADC_HWTRIGGER_TIM1_CC2 1
#define ADC_HWTRIGGER_TIM1_CC3 2
#define ADC_HWTRIGGER_TIM2_CC2 3
#define ADC_HWTRIGGER_TIM3_TRGO 4
#define ADC_HWTRIGGER_TIM4_CC4 5
#define ADC_HWTRIGGER_TIM4_CC4 5
#define ADC_HWTRIGGER_EXTI_TIM8_TRGO 6
#define ADC_SWTRIGGER_SWS 7

typedef uint8_t Adc_GroupPriorityType;
typedef uint8_t Adc_GroupDefType;
typedef uint8_t Adc_StreamNumSampleType;
typedef uint8_t Adc_ChannelType;
typedef uint8_t Adc_GroupType;
typedef uint16_t Adc_ValueGroupType;
typedef uint8_t Adc_PrescaleType;
typedef uint8_t Adc_ConversionTimeType;
typedef uint8_t Adc_SamplingTimeType;
typedef uint8_t Adc_ResolutionType;
typedef uint8_t Adc_ReferenceType;
typedef uint8_t Adc_ClockSourceType;
typedef uint8_t Adc_HwTriggerTimerType;

typedef enum
{
    ADC_IDLE,
    ADC_BUSY,
    ADC_COMPLETED,
    ADC_STREAM_COMPLETED
} Adc_StatusType;

typedef enum
{
    ADC_MODE_INDEPENDENT,
    ADC_MODE_COMBINE,
} Adc_GroupModeType;
typedef enum
{
    ADC_CONV_MODE_ONESHOT,
    ADC_CONV_MODE_CONTINUOUS
} Adc_GroupConvModeType;
typedef enum
{
    ADC_STREAM_BUFFER_LINEAR,
    ADC_STREAM_BUFFER_CIRCULAR
} Adc_StreamBufferModeType;

typedef enum
{
    ADC_ACCESS_MODE_SINGLE,
    ADC_ACCESS_MODE_STREAMING
} Adc_GroupAccessModeType;

typedef enum
{
    ADC_HW_TRIG_RISING_EDGE,
    ADC_HW_TRIG_FALLING_EDGE,
    ADC_HW_TRIG_BOTH_EDGES
} Adc_HwTriggerSignalType;

typedef enum
{
    ADC_PRIORITY_NONE,
    ADC_PRIORITY_HW,
    ADC_PRIORITY_HW_SW
} Adc_PriorityImplementationType;

typedef enum
{
    ADC_GROUP_REPL_ABORT_RESTART,
    ADC_GROUP_REPL_SUSPEND_RESUME
} Adc_GroupReplacementType;

typedef enum
{
    ADC_RANGE_UNDER_LOW,
    ADC_RANGE_BETWEEN,
    ADC_RANGE_OVER_HIGH,
    ADC_RANGE_ALWAYS,
    ADC_RANGE_NOT_UNDER_LOW,
    ADC_RANGE_NOT_BETWEEN,
    ADC_RANGE_NOT_OVER_HIGH,
} Adc_ChannelRangeSelectType;

typedef enum
{
    ADC_ALIGN_RIGHT,
    ADC_ALIGN_LEFT
} Adc_ResultAlignmentType;

typedef uint8_t Adc_PowerStateType;

typedef enum
{
    ADC_SERVICE_ACCEPTED,
    ADC_NOT_INIT,
    ADC_SEQUENCE_ERROR,
    ADC_HW_FAILURE,
    ADC_POWER_STATE_NOT_SUPP,
    ADC_TRANS_NOT_POSSIBLE
} Adc_PowerStateRequestResultType;

typedef struct
{
    const Adc_GroupModeType GroupMode;
    const Adc_GroupDefType GroupNums;
    const Adc_GroupConvModeType GroupConvMode;
    const Adc_ChannelType ChannelId;
    const Adc_ResultAlignmentType ResultAlignment;
    const Adc_SamplingTimeType SamplingTime;
    const Adc_ResolutionType Resolution;
    const Adc_ReferenceType Reference;
    const Adc_ClockSourceType ClockSource;
} Adc_ConfigType;

void Adc_Init(const Adc_ConfigType *ConfigPtr);
Std_ReturnType Adc_SetupResultBuffer(Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr);
void Adc_DeInit(void);
void Adc_StartGroupConversion(Adc_GroupType Group);
void Adc_StopGroupConversion(Adc_GroupType Group);
Std_ReturnType Adc_ReadGroup(Adc_GroupType Group, Adc_ValueGroupType *DataBufferPtr);
void Adc_EnableHardwareTrigger(Adc_GroupType Group);
void Adc_DisableHardwareTrigger(Adc_GroupType Group);
void Adc_EnableGroupNotification(Adc_GroupType Group);
void Adc_DisableGroupNotification(Adc_GroupType Group);
Adc_StatusType Adc_GetGroupStatus(Adc_GroupType Group);
Adc_StreamNumSampleType Adc_GetStreamLastPointer(Adc_GroupType Group, Adc_ValueGroupType **PtrToSamplePtr);
Std_ReturnType Adc_SetPowerState(Adc_PowerStateRequestResultType *Result);
Std_ReturnType Adc_GetCurrentPowerState(Adc_PowerStateType *CurrentPowerState, Adc_PowerStateRequestResultType *Result);
Std_ReturnType Adc_GetTargetPowerState(Adc_PowerStateType *TargetPowerState, Adc_PowerStateRequestResultType *Result);
Std_ReturnType Adc_PreparePowerState(Adc_PowerStateType PowerState, Adc_PowerStateRequestResultType *Result);
void Adc_Main_PowerTransitionManager(void);

#endif