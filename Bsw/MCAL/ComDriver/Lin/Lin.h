#ifndef __LIN_H
#define __LIN_H

#include "Std_GeneralTypes.h"
#include "ComStack_Types.h"
#include "Lin_GeneralTypes.h"

typedef struct
{
    uint32 LinChannelBaudRate;
    uint32 LinChannelId;
    bool LinChannelWakeupSupport;
    bool LinNodeType;
    uint32 LinClockRef;
} LinChannel;

typedef struct
{
    LinChannel *LinChannel_0;
} LinGobalConfig;

typedef struct
{
    bool LinDevErrorDetect;
    uint8 LinIndex;
    uint32 LinTimeoutDuration;
    bool LinVersionInfoApi;
} LinGeneral;

typedef struct
{
    LinGeneral *LinGeneral_0;
    LinGobalConfig *LinGlobalConfig_0;
} Lin_ConfigType;

void Lin_Init(const Lin_ConfigType *Config);
Std_ReturnType Lin_CheckWakeup(uint8 Channel);
Std_ReturnType Lin_SendFrame(uint8 Channel, const Lin_PduType *PduInfoPtr);
Std_ReturnType Lin_GoToSleep(uint8 Channel);
Std_ReturnType Lin_GoToSleepInternal(uint8 Channel);
Std_ReturnType Lin_Wakeup(uint8 Channel);
Std_ReturnType Lin_WakeupInternal(uint8 Channel);
Lin_StatusType Lin_GetStatus(uint8 Channel, const uint8 **Lin_SduPtr);
void Lin_MainFunction_Read(void);

#endif