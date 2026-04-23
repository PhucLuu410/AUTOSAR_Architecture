#ifndef __ADC_H
#define __ADC_H

#include "Std_Types.h"
// #include "Adc_Cfg.h"

typedef uint8_t Adc_AdcNumberType;
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
typedef uint8_t Adc_ScanModeType;
typedef uint8_t Adc_DMAEnableType;
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
    Adc_AdcNumberType AdcNumber;
    Adc_PrescaleType Prescale;
    Adc_ResolutionType Resolution;
    Adc_ResultAlignmentType Adc_ResultAlignment;
    Adc_ScanModeType ScanDMA;
    Adc_DMAEnableType DMAEnable;
} Adc_CommonConfigType;
typedef struct
{
    Adc_CommonConfigType *CommonConfig;
    Adc_GroupDefType GroupNums;
    Adc_GroupModeType GroupMode;
    Adc_GroupConvModeType GroupConvMode;
    Adc_ChannelType *ChannelId;
    Adc_ReferenceType *Reference;
    Adc_SamplingTimeType SamplingTime;
    Adc_HwTriggerTimerType HwTriggerTimer;
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

#endif