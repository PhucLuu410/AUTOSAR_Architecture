#ifndef CAN_H
#define CAN_H

#include "ComStack_Types.h"
#include "Icu.h"
#include "Std_Types.h"
#include "EcuM.h"
#include "Os.h"

typedef struct
{
    boolean FilterStatus;
    boolean FilterIdType;
    boolean FilterMode;
    boolean FilterScale;
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
    uint32 Brp;
    uint32 Baudrate;
    uint32 Clock;
} Can_Baudrate;

typedef struct
{
    boolean CanSleepIsr;
    boolean CanWakeupIsr;
    boolean ErrorIsr;
    boolean LastErrorCodeIsr;
    boolean BusOffIsr;
    boolean ErrorPassiveIsr;
    boolean ErrorWarningIsr;
    boolean Fifo1OverrunIsr;
    boolean Fifo1OFullIsr;
    boolean Fifo1MessagePendingIsr;
    boolean Fifo0OverrunIsr;
    boolean Fifo0OFullIsr;
    boolean Fifo0MessagePendingIsr;
    boolean TransmitMailboxEmptyIsr;
} Can_Isr;

typedef struct
{
    uint8 CanControllerNumber;
    boolean CanDebugMode;
    boolean CanTimerTriggerCommunicationMode;
    boolean CanAutoBusOffMode;
    boolean CanAutoWakeupMode;
    boolean CanAutoRetransmission;
    boolean CanReceiveFifoLockedMode;
    boolean CanTransmitFifoPriority;
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

#endif