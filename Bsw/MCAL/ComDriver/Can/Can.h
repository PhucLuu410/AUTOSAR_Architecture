#ifndef CAN_H
#define CAN_H

#include "ComStack_Types.h"
#include "Icu.h"
#include "Std_Types.h"
#include "EcuM.h"
#include "Os.h"

typedef struct
{
    bool FilterStatus;
    bool FilterIdType;
    bool FilterMode;
    bool FilterScale;
    uint32 FilterId1;
    uint32 FilterId2;
    uint32 FilterId3;
    uint32 FilterId4;
    uint32 FilterMask1;
    uint32 FilterMask2;
    uint8 FilterAssignToFifo;
} Can_Filter;

typedef struct
{
    uint32 Clock;
    uint32 BaudRate;
    uint32 PropSeg;
    uint8 Seg1;
    uint8 Seg2;
    uint8 SyncJumpWidth;
    uint16 Brp;
} Can_Baudrate;

typedef struct
{
    bool CanSleepIsr;
    bool CanWakeupIsr;
    bool ErrorIsr;
    bool LastErrorCodeIsr;
    bool BusOffIsr;
    bool ErrorPassiveIsr;
    bool ErrorWarningIsr;
    bool Fifo1OverrunIsr;
    bool Fifo1OFullIsr;
    bool Fifo1MessagePendingIsr;
    bool Fifo0OverrunIsr;
    bool Fifo0OFullIsr;
    bool Fifo0MessagePendingIsr;
    bool TransmitMailboxEmptyIsr;
} Can_Isr;

typedef struct
{
    uint8 CanControllerNumber;
    bool CanDebugMode;
    bool CanTimerTriggerCommunicationMode;
    bool CanAutoBusOffMode;
    bool CanAutoWakeupMode;
    bool CanAutoRetransmission;
    bool CanReceiveFifoLockedMode;
    bool CanTransmitFifoPriority;
} Can_Controller;

typedef struct
{
} Can_HwUnit;

typedef struct
{
    Can_Baudrate *CanBaudrate;
    Can_Filter *CanFilter;
    Can_HwUnit *CanHwUnit;
    Can_Controller *CanController;
    Can_Isr *CanIsr;
} Can_ConfigType;

void Can_Init(const Can_ConfigType *Config);
Std_ReturnType Can_SetControllerMode(uint8 Controller, Can_ControllerStateType Transition);
void Can_DisableControllerInterrupts(uint8 Controller);
void Can_EnableControllerInterrupts(uint8 Controller);
Std_ReturnType Can_SetBaudrate(uint8 Controller, uint16 BaudRateConfigID);
Std_ReturnType Can_Write(Can_HwHandleType Hth, const Can_PduType *PduInfo);
void Can_MainFunction_Wakeup(void);
void Can_MainFunction_BusOff(void);
void Can_MainFunction_Write(void);
void Can_MainFunction_Mode(void);
void Can_MainFunction_Read(void);

#endif