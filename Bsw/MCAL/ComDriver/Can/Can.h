#ifndef __CAN_H__
#define __CAN_H__

#include "Std_Types.h"
#include "Can_GeneralTypes.h"
#include "ComStack_Types.h"

typedef struct
{
    uint32 baudRate;
    uint8 mode;
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
Std_ReturnType Can_GetCurrentTime(uint8 ControllerId, Can_TimeStampType *timeStampPtr);
void Can_EnableEgressTimeStamp(Can_HwHandleType Hth);
Std_ReturnType Can_GetEgressTimeStamp(PduIdType TxPduId, Can_HwHandleType Hth, Can_TimeStampType *timeStampPtr);
Std_ReturnType Can_GetIngressTimeStamp(Can_HwHandleType Hrh, Can_TimeStampType *timeStampPtr);
Std_ReturnType Can_SetCanPnFrameDataMask(uint8 Controller, uint8 *DataMaskArrayPtr, uint8 Length);
Std_ReturnType Can_Write(Can_HwHandleType Hth, const Can_PduType *PduInfo);
boolean Appl_CanRxIndication(uint8 Hrh, Can_IdType CanId, uint8 CanDataLength, const uint8 *CanSduPtr);
void Can_MainFunction_Write(void);
void Can_MainFunction_Read(void);
void Can_MainFunction_BusOff(void);
void Can_MainFunction_Wakeup(void);
void Can_MainFunction_Mode(void);

#endif /* __CAN_H__ */