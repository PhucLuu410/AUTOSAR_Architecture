#ifndef __COMHWAB_H
#define __COMHWAB_H

#include "Std_Types.h "
#include "Can_GeneralTypes.h"
#include "ComStack_Types.h "
#include "EcuM.h"

typedef struct
{
    PduIdType RxPduId;
    Can_IdType CanId;
    uint8 Length;
    uint8 *data;
} CanIfPduRxTableType;

typedef struct
{
    uint8 CanChannel;
    uint8 CanIf_LocalId;
    uint16 CanIf_CanId;
} CanIf_PduTableConfig;

typedef struct
{
    CanIfPduRxTableType *RxTableConfig;
    CanIf_PduTableConfig *TxTableConfig;
} CanIf_ConfigType;

typedef enum
{
    CANIF_OFFLINE,
    CANIF_TX_OFFLINE,
    CANIF_TX_OFFLINE_ACTIVE,
    CANIF_ONLINE,
} CanIf_PduModeType;

typedef enum
{
    CANIF_NO_NOTIFICATION,
    CANIF_TX_RX_NOTIFICATION,
} CanIf_NotifStatusType;

void CanIf_Init(const CanIf_ConfigType *ConfigPtr);
void CanIf_DeInit(void);
Std_ReturnType CanIf_SetControllerMode(uint8 ControllerId, Can_ControllerStateType ControllerMode);
Std_ReturnType CanIf_GetControllerMode(uint8 ControllerId, Can_ControllerStateType *ControllerModePtr);
Std_ReturnType CanIf_GetControllerErrorState(uint8 ControllerId, Can_ErrorStateType *ErrorStatePtr);
Std_ReturnType CanIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr);
Std_ReturnType CanIf_ReadRxPduData(PduIdType CanIfRxSduId, PduInfoType *CanIfRxInfoPtr);
Std_ReturnType CanIf_SetPduMode(uint8 ControllerId, CanIf_PduModeType PduModeRequest);
Std_ReturnType CanIf_GetPduMode(uint8 ControllerId, CanIf_PduModeType *PduModePtr);
void CanIf_SetDynamicTxId(PduIdType CanIfTxSduId, Can_IdType CanId);
void CanIf_TxConfirmation(PduIdType CanTxPduId);
void CanIf_RxIndication(const Can_HwType *Mailbox, const PduInfoType *PduInfoPtr);

//----------------------STUB-------------------------------------------------//
// Std_ReturnType CanIf_CheckWakeup(EcuM_WakeupSourceType WakeupSource);
// Std_ReturnType CanIf_CheckValidation(EcuM_WakeupSourceType WakeupSource);
Std_ReturnType CanIf_ClearTrcvWufFlag(uint8 TransceiverId);
Std_ReturnType CanIf_CheckTrcvWakeFlag(uint8 TransceiverId);
Std_ReturnType CanIf_SetBaudrate(uint8 ControllerId, uint16 BaudRateConfigID);
Std_ReturnType CanIf_EnableBusMirroring(uint8 ControllerId, boolean MirroringActive);
Std_ReturnType CanIf_GetCurrentTime(uint8 Controller, Can_TimeStampType *timeStampPtr);
void CanIf_EnableEgressTimeStamp(PduIdType TxPduId);
Std_ReturnType CanIf_GetEgressTimeStamp(PduIdType TxPduId, Can_TimeStampType *timeStampPtr);
Std_ReturnType CanIf_GetIngressTimeStamp(PduIdType RxPduId, Can_TimeStampType timeStampPtr);
Std_ReturnType CanIf_TriggerTransmit(PduIdType TxPduId, PduInfoType *PduInfoPtr);
Std_ReturnType CanIf_XLReportErrorState(uint8 Transceiver, Can_ErrorStateType ErrorState);
void CanIf_ConfirmPnAvailability(uint8 TransceiverId);
void CanIf_ConfirmCtrlPnAvailability(uint8 ControllerId);
void CanIf_ClearTrcvWufFlagIndication(uint8 TransceiverId);
void CanIf_CheckTrcvWakeFlagIndication(uint8 TransceiverId);
void CanIf_ControllerModeIndication(uint8 ControllerId, Can_ControllerStateType ControllerMode);
void CanIf_ControllerErrorStatePassive(uint8 ControllerId, uint16 RxErrorCounter, uint16 TxErrorCounter);
CanIf_NotifStatusType CanIf_ReadTxNotifStatus(PduIdType CanIfTxSduId);
CanIf_NotifStatusType CanIf_ReadRxNotifStatus(PduIdType CanIfRxSduId);
CanIf_NotifStatusType CanIf_GetTxConfirmationState(uint8 ControllerId);
void CanIf_ErrorNotification(uint8 ControllerId, Can_ErrorType Can_ErrorType);
void CanIf_ControllerBusOff(uint8 ControllerId);
Std_ReturnType CanIf_GetControllerRxErrorCounter(uint8 ControllerId, uint8 *RxErrorCounterPtr);
Std_ReturnType CanIf_GetControllerTxErrorCounter(uint8 ControllerId, uint8 *TxErrorCounterPtr);
#endif
