#ifndef __LIN_H
#define __LIN_H

#include "ComStack_Types.h"
// #include "Rte_Dem_Type.h"
#include "EcuM.h"
#include "Icu.h"
#include "Std_Types.h"

typedef struct
{
    uint8 LinUartEn;
    uint8 LinTx;
    uint8 LinRx;
    uint8 LinEn;
} Lin_HardwareConfig;

typedef struct
{
    uint8 LinChannel;
    uint8 LinBreakDetect;
    uint32 LinBaud;
    uint8 LinIsr;
    uint8 LinMasterSlave;
} Lin_ChannelConfig;

typedef struct
{
    const Lin_HardwareConfig *LinHardware;
    const Lin_ChannelConfig *LinChannel;
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