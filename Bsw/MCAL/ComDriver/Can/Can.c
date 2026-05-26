#include "Can.h"
#include "Can_Cfg.h"
#include "CanIf.h"
#include "Det.h"

static uint8 PduIdRecentSent = 0;
Can_ControllerStateType Can_ControllerState[CAN_MAX_CONTROLLER] = {[0] = CAN_CS_UNINIT};
static const Can_ConfigType *LocalCanConfig = NULL_PTR;
uint32 CanRetry = 0;

void Can_Init(const Can_ConfigType *ConfigPtr)
{
    if (ConfigPtr == NULL_PTR)
    {
        Det_ReportError(0, 0, 0, 1);
        return;
    }
    LocalCanConfig = ConfigPtr;
    Can_Controllers[LocalCanConfig->CanControllerId]->MCR = 0x00010002;
    Can_Controllers[LocalCanConfig->CanControllerId]->MCR |= LocalCanConfig->CanHohHandler->CanDebugMode << 16;
    Can_Controllers[LocalCanConfig->CanControllerId]->MCR |= LocalCanConfig->CanTrigger << 7;
    Can_Controllers[LocalCanConfig->CanControllerId]->MCR |= LocalCanConfig->CanHohHandler->CanAutoBusOff << 6;
    Can_Controllers[LocalCanConfig->CanControllerId]->MCR |= LocalCanConfig->CanHohHandler->CanAutoWakeUp << 5;
    Can_Controllers[LocalCanConfig->CanControllerId]->MCR |= LocalCanConfig->CanHohHandler->CanAutoRetransmission << 4;
    Can_Controllers[LocalCanConfig->CanControllerId]->MCR |= LocalCanConfig->CanHohHandler->CanReceiveFifoLockedMode << 3;
    Can_Controllers[LocalCanConfig->CanControllerId]->MCR |= LocalCanConfig->CanHohHandler->CanTransmitFifoPriority << 2;
    Can_Controllers[LocalCanConfig->CanControllerId]->FMR |= (1 << 0);
    for (int i = 0; i < CAN_NUMBER_OF_FILTER; i++)
    {
        Can_Controllers[LocalCanConfig->CanControllerId]->FS1R |= (LocalCanConfig->CanIdMaskMode >> 1) << i;
        Can_Controllers[LocalCanConfig->CanControllerId]->FM1R |= (LocalCanConfig->CanIdMaskMode & 0x01) << i;
        Can_Controllers[LocalCanConfig->CanControllerId]->FFA1R |= (LocalCanConfig->CanFilter[i].Fifo << i);
        Can_Controllers[LocalCanConfig->CanControllerId]->FA1R |= (1 << LocalCanConfig->CanFilter[i].Bank);
        if (LocalCanConfig->CanIdType == CAN_STANDARD_ID)
        {
            Can_Controllers[LocalCanConfig->CanControllerId]->sFilterRegister[i].FR1 = ((LocalCanConfig->CanFilter[i].Id) << 21);
            Can_Controllers[LocalCanConfig->CanControllerId]->sFilterRegister[i].FR2 = ((LocalCanConfig->CanFilter[i].Mask) << 21);
        }
        else
        {
            Can_Controllers[LocalCanConfig->CanControllerId]->sFilterRegister[i].FR1 = ((LocalCanConfig->CanFilter[i].Id) << 3) | (1 << 2);
            Can_Controllers[LocalCanConfig->CanControllerId]->sFilterRegister[i].FR2 = ((LocalCanConfig->CanFilter[i].Mask) << 3) | (1 << 2);
        }
    }
    Can_Controllers[LocalCanConfig->CanControllerId]->FMR &= ~(1 << 0);
    Can_ControllerState[LocalCanConfig->CanControllerId] = CAN_CS_STOPPED;
}

void Can_DeInit(void)
{
    for (int i = 0; i < CAN_MAX_CONTROLLER; i++)
    {
        Can_ControllerState[i] = CAN_CS_UNINIT;
    }
    LocalCanConfig = NULL_PTR;
}

Std_ReturnType Can_SetBaudrate(uint8 Controller, uint16 BaudRateConfigID)
{
    if (Can_ControllerState[Controller] == CAN_CS_UNINIT)
    {
        Det_ReportError(0, 0, 0, 1);
        return E_NOT_OK;
    }
    Can_Controllers[Controller]->MCR &= ~(1 << 1);
    while (Can_Controllers[Controller]->MSR & (1 << 1))
        ;
    Can_Controllers[Controller]->MCR |= (1 << 0);
    while (!(Can_Controllers[Controller]->MSR & (1 << 0)))
        ;
    Can_Controllers[Controller]->BTR = (LocalCanConfig->CanBaudrateConfig[BaudRateConfigID].CanBaudratePrescaler << 0) |
                                       (LocalCanConfig->CanBaudrateConfig[BaudRateConfigID].CanTseg1 << 16) |
                                       (LocalCanConfig->CanBaudrateConfig[BaudRateConfigID].CanTseg2 << 20) |
                                       (LocalCanConfig->CanBaudrateConfig[BaudRateConfigID].CanSjw << 24);
    // Loopback check
    // CAN1->BTR |= (1 << 30);
    // CAN1->BTR |= (1 << 31);
    return E_OK;
}

Std_ReturnType Can_SetControllerMode(uint8 Controller, Can_ControllerStateType Transition)
{
    switch (Transition)
    {
    case CAN_CS_STARTED:
        Can_Controllers[Controller]->MCR &= ~(1 << 0);
        CanRetry = 0xFFFF;
        while ((Can_Controllers[Controller]->MSR & (1 << 0)))
        {
            CanRetry--;
            if (CanRetry == 0)
            {
                Det_ReportError(0, 0, 0, 1);
                return E_NOT_OK;
            }
        };
        Can_ControllerState[Controller] = CAN_CS_STARTED;
        break;
    case CAN_CS_STOPPED:
        if (Can_ControllerState[Controller] != CAN_CS_UNINIT)
        {
            return E_NOT_OK;
        }
        Can_Controllers[Controller]->MCR |= (1 << 0);
        CanRetry = 0xFFFF;
        while (!(Can_Controllers[Controller]->MSR & (1 << 0)))
        {
            CanRetry--;
            if (CanRetry == 0)
            {
                Det_ReportError(0, 0, 0, 1);
                return E_NOT_OK;
            }
        }
        Can_ControllerState[Controller] = CAN_CS_STOPPED;
        break;
    case CAN_CS_SLEEP:
        if (Can_ControllerState[Controller] != CAN_CS_UNINIT)
        {
            return E_NOT_OK;
        }
        Can_Controllers[Controller]->MCR &= ~(1 << 0);
        Can_Controllers[Controller]->MCR |= (1 << 1);
        CanRetry = 0xFFFF;
        while (!(Can_Controllers[Controller]->MSR & (1 << 1)))
        {
            CanRetry--;
            if (CanRetry == 0)
            {
                Det_ReportError(0, 0, 0, 1);
                return E_NOT_OK;
            }
        }
        Can_ControllerState[Controller] = CAN_CS_SLEEP;
        break;
    default:
        Det_ReportError(0, 0, 0, 1);
        return E_NOT_OK;
    }
    return E_OK;
}

void Can_DisableControllerInterrupts(uint8 Controller)
{
    if (Controller >= CAN_MAX_CONTROLLER)
    {
        Det_ReportError(0, 0, 0, 1);
        return;
    }
    NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
    NVIC_DisableIRQ(USB_HP_CAN1_TX_IRQn);
    Can_Controllers[Controller]->IER = 0;
}

void Can_EnableControllerInterrupts(uint8 Controller)
{
    if (Controller >= CAN_MAX_CONTROLLER)
    {
        Det_ReportError(0, 0, 0, 1);
        return;
    }
    NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
    NVIC_EnableIRQ(USB_HP_CAN1_TX_IRQn);
    NVIC_SetPriority(USB_HP_CAN1_TX_IRQn, 1);
    Can_Controllers[Controller]->IER = LocalCanConfig->CanInterruptEnable;
}

Std_ReturnType Can_CheckWakeup(uint8 Controller)
{
    if (Controller >= CAN_MAX_CONTROLLER)
    {
        Det_ReportError(0, 0, 0, 1);
        return E_NOT_OK;
    }
    if (Can_Controllers[Controller]->MSR & (1 << 1))
    {
        return E_NOT_OK;
    }
    return E_OK;
}

Std_ReturnType Can_GetControllerErrorState(uint8 ControllerId, Can_ErrorStateType *ErrorStatePtr)
{
    if (ControllerId >= CAN_MAX_CONTROLLER || ErrorStatePtr == NULL_PTR)
    {
        Det_ReportError(0, 0, 0, 1);
        return E_NOT_OK;
    }

    if ((Can_Controllers[ControllerId]->ESR & (1 << 2)))
    {
        *ErrorStatePtr = CAN_ERRORSTATE_BUSOFF;
    }
    else if ((Can_Controllers[ControllerId]->ESR & (1 << 1)))
    {
        *ErrorStatePtr = CAN_ERRORSTATE_PASSIVE;
    }
    else
    {
        *ErrorStatePtr = CAN_ERRORSTATE_ACTIVE;
    }
    return E_OK;
}

Std_ReturnType Can_GetControllerMode(uint8 Controller, Can_ControllerStateType *ControllerModePtr)
{
    if (Controller >= CAN_MAX_CONTROLLER || ControllerModePtr == NULL_PTR)
    {
        Det_ReportError(0, 0, 0, 1);
        return E_NOT_OK;
    }
    *ControllerModePtr = Can_ControllerState[Controller];
    return E_OK;
}

Std_ReturnType Can_GetControllerRxErrorCounter(uint8 ControllerId, uint8 *RxErrorCounterPtr)
{
    if (ControllerId >= CAN_MAX_CONTROLLER || RxErrorCounterPtr == NULL_PTR)
    {
        Det_ReportError(0, 0, 0, 1);
        return E_NOT_OK;
    }
    *RxErrorCounterPtr = (Can_Controllers[ControllerId]->ESR >> 24) & 0xFF;
    return E_OK;
}

Std_ReturnType Can_GetControllerTxErrorCounter(uint8 ControllerId, uint8 *TxErrorCounterPtr)
{
    if (ControllerId >= CAN_MAX_CONTROLLER || TxErrorCounterPtr == NULL_PTR)
    {
        Det_ReportError(0, 0, 0, 1);
        return E_NOT_OK;
    }
    *TxErrorCounterPtr = (Can_Controllers[ControllerId]->ESR >> 16) & 0xFF;
    return E_OK;
}

Std_ReturnType Can_SetCanPnFrameDataMask(uint8 Controller, uint8 *DataMaskArrayPtr, uint8 Length)
{
    if (Controller >= CAN_MAX_CONTROLLER || DataMaskArrayPtr == NULL_PTR || Length > 8)
    {
        Det_ReportError(0, 0, 0, 1);
        return E_NOT_OK;
    }
    for (int i = 0; i < Length; i++)
    {
        Can_Controllers[Controller]->sTxMailBox[0].TDLR &= ~(DataMaskArrayPtr[i] << (i * 8));
    }
    return E_OK;
}

Std_ReturnType Can_Write(Can_HwHandleType Hth, const Can_PduType *PduInfo)
{
    if ((Can_Controllers[CAN_1]->TSR & (0x7 << 24)) == 0)
    {
        return CAN_BUSY;
    }
    PduIdRecentSent = PduInfo->swPduHandle;
    if (!(Can_Controllers[CAN_1]->TSR & (1 << (26 + Hth))))
    {
        return CAN_BUSY;
    }
    Can_Controllers[CAN_1]->sTxMailBox[Hth].TDTR = PduInfo->length;
    Can_Controllers[CAN_1]->sTxMailBox[Hth].TDLR = *((uint32 *)PduInfo->sdu);
    Can_Controllers[CAN_1]->sTxMailBox[Hth].TDHR = *((uint32 *)(PduInfo->sdu + 4));
    if (LocalCanConfig->CanIdType == CAN_STANDARD_ID)
    {
        Can_Controllers[CAN_1]->sTxMailBox[Hth].TIR = 0;
        Can_Controllers[CAN_1]->sTxMailBox[Hth].TIR |= (PduInfo->id << 21);
        Can_Controllers[CAN_1]->sTxMailBox[Hth].TIR &= ~(1 << 1);
        Can_Controllers[CAN_1]->sTxMailBox[Hth].TIR |= (1 << 0);
    }
    else if (LocalCanConfig->CanIdType == CAN_EXTENDED_ID)
    {
        Can_Controllers[CAN_1]->sTxMailBox[Hth].TIR = 0;
        Can_Controllers[CAN_1]->sTxMailBox[Hth].TIR |= (PduInfo->id << 3);
        Can_Controllers[CAN_1]->sTxMailBox[Hth].TIR |= (1 << 2);
        Can_Controllers[CAN_1]->sTxMailBox[Hth].TIR &= ~(1 << 1);
        Can_Controllers[CAN_1]->sTxMailBox[Hth].TIR |= (1 << 0);
    }
    else
    {
        return E_NOT_OK;
    }
    return E_OK;
}

void Can_MainFunction_Read(void)
{
    Can_HwType CanMailBox;
    PduInfoType CanRxPdu;
    uint32_t temp_data[2];

    CanMailBox.ControllerId = CAN_1;

    if ((Can_Controllers[CAN_1]->RF0R & 0x03) != 0)
    {
        if (Can_Controllers[CAN_1]->sFIFOMailBox[0].RIR & (1 << 2))
        {
            CanMailBox.CanId = Can_Controllers[CAN_1]->sFIFOMailBox[0].RIR >> 3;
        }
        else
        {
            CanMailBox.CanId = Can_Controllers[CAN_1]->sFIFOMailBox[0].RIR >> 21;
        }
        CanMailBox.Hoh = 0;
        CanRxPdu.SduLength = Can_Controllers[CAN_1]->sFIFOMailBox[0].RDTR & 0x0F;
        CanRxPdu.SduDataPtr = (uint8_t *)temp_data;
        temp_data[0] = Can_Controllers[CAN_1]->sFIFOMailBox[0].RDLR;
        temp_data[1] = Can_Controllers[CAN_1]->sFIFOMailBox[0].RDHR;
        CanIf_RxIndication(&CanMailBox, &CanRxPdu);
        Can_Controllers[CAN_1]->RF0R |= (1 << 5);
    }
    if ((Can_Controllers[CAN_1]->RF1R & 0x03) != 0)
    {
        if (Can_Controllers[CAN_1]->sFIFOMailBox[1].RIR & (1 << 2))
        {
            CanMailBox.CanId = Can_Controllers[CAN_1]->sFIFOMailBox[1].RIR >> 3;
        }
        else
        {
            CanMailBox.CanId = Can_Controllers[CAN_1]->sFIFOMailBox[1].RIR >> 21;
        }
        CanMailBox.Hoh = 1;
        CanRxPdu.SduLength = Can_Controllers[CAN_1]->sFIFOMailBox[1].RDTR & 0x0F;
        CanRxPdu.SduDataPtr = (uint8_t *)temp_data;
        temp_data[0] = Can_Controllers[CAN_1]->sFIFOMailBox[1].RDLR;
        temp_data[1] = Can_Controllers[CAN_1]->sFIFOMailBox[1].RDHR;
        CanIf_RxIndication(&CanMailBox, &CanRxPdu);
        Can_Controllers[CAN_1]->RF1R |= (1 << 5);
    }
}

void USB_LP_CAN1_RX0_IRQHandler(void)
{
    Can_HwType CanMailBox;
    PduInfoType CanRxPdu;
    uint32_t temp_data[2];

    CanMailBox.ControllerId = CAN_1;

    if ((Can_Controllers[CAN_1]->RF0R & 0x03) != 0)
    {
        if (Can_Controllers[CAN_1]->sFIFOMailBox[0].RIR & (1 << 2))
        {
            CanMailBox.CanId = Can_Controllers[CAN_1]->sFIFOMailBox[0].RIR >> 3;
        }
        else
        {
            CanMailBox.CanId = Can_Controllers[CAN_1]->sFIFOMailBox[0].RIR >> 21;
        }
        CanMailBox.Hoh = 0;
        CanRxPdu.SduLength = Can_Controllers[CAN_1]->sFIFOMailBox[0].RDTR & 0x0F;
        CanRxPdu.SduDataPtr = (uint8_t *)temp_data;
        temp_data[0] = Can_Controllers[CAN_1]->sFIFOMailBox[0].RDLR;
        temp_data[1] = Can_Controllers[CAN_1]->sFIFOMailBox[0].RDHR;
        CanIf_RxIndication(&CanMailBox, &CanRxPdu);
        Can_Controllers[CAN_1]->RF0R |= (1 << 5);
    }
    if ((Can_Controllers[CAN_1]->RF1R & 0x03) != 0)
    {
        if (Can_Controllers[CAN_1]->sFIFOMailBox[1].RIR & (1 << 2))
        {
            CanMailBox.CanId = Can_Controllers[CAN_1]->sFIFOMailBox[1].RIR >> 3;
        }
        else
        {
            CanMailBox.CanId = Can_Controllers[CAN_1]->sFIFOMailBox[1].RIR >> 21;
        }
        CanMailBox.Hoh = 1;
        CanRxPdu.SduLength = Can_Controllers[CAN_1]->sFIFOMailBox[1].RDTR & 0x0F;
        CanRxPdu.SduDataPtr = (uint8_t *)temp_data;
        temp_data[0] = Can_Controllers[CAN_1]->sFIFOMailBox[1].RDLR;
        temp_data[1] = Can_Controllers[CAN_1]->sFIFOMailBox[1].RDHR;
        CanIf_RxIndication(&CanMailBox, &CanRxPdu);
        Can_Controllers[CAN_1]->RF1R |= (1 << 5);
    }
}

void USB_HP_CAN1_TX_IRQHandler(void)
{
    CAN1->TSR = 0x01010101;
    CanIf_TxConfirmation(PduIdRecentSent);
}