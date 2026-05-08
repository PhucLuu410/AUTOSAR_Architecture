#ifndef __CAN_H
#define __CAN_H

#include "Std_Types.h"
#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"

typedef struct
{
    uint8 CanDebugMode;
    uint8 CanAutoBusOff;
    uint8 CanAutoWakeUp;
    uint8 CanAutoRetransmission;
    uint8 CanReceiveFifoLockedMode;
    uint8 CanTransmitFifoPriority;
} Can_HohHandlerConfigType;

typedef struct
{
    uint8 CanBaudrateId;
    uint8 CanTseg1;
    uint8 CanTseg2;
    uint8 CanBaudratePrescaler;
    uint8 CanSjw;
} Can_BaudrateConfigType;

typedef struct
{
    uint8 Fifo;
    uint8 Bank;
    uint32 Id;
    uint32 Mask;
} Can_FilterType;

typedef struct
{
    uint32 CanControllerId;
    uint8 CanIdType;
    uint8 CanIdMaskMode;
    Can_FilterType *CanFilter;
    Can_BaudrateConfigType *CanBaudrateConfig;
    uint8 CanTrigger;
    Can_HohHandlerConfigType *CanHohHandler;
    uint8 CanMultiplexTransmission;
    uint8 CanEventDetection;
    uint32 CanInterruptEnable;
    uint8 CanTxHardwareObject;
} Can_ConfigType;

void Can_Init(const Can_ConfigType *ConfigPtr);
void Can_DeInit(void);

Std_ReturnType Can_SetBaudrate(uint8 Controller, uint16 BaudRateConfigID);
Std_ReturnType Can_SetControllerMode(uint8 Controller, Can_ControllerStateType Transition);
void Can_DisableControllerInterrupts(uint8 Controller);
void Can_EnableControllerInterrupts(uint8 Controller);
Std_ReturnType Can_CheckWakeup(uint8 Controller);
Std_ReturnType Can_GetControllerErrorState(uint8 ControllerId, Can_ErrorStateType *ErrorStatePtr);
Std_ReturnType Can_GetControllerMode(uint8 Controller, Can_ControllerStateType *ControllerModePtr);
Std_ReturnType Can_GetControllerRxErrorCounter(uint8 ControllerId, uint8 *RxErrorCounterPtr);
Std_ReturnType Can_GetControllerTxErrorCounter(uint8 ControllerId, uint8 *TxErrorCounterPtr);
Std_ReturnType Can_SetCanPnFrameDataMask(uint8 Controller, uint8 *DataMaskArrayPtr, uint8 Length);
Std_ReturnType Can_Write(Can_HwHandleType Hth, const Can_PduType *PduInfo);
void Can_MainFunction_Read(void);
#endif