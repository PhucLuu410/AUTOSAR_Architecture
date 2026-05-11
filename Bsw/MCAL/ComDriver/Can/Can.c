#include "Can.h"
#include "Can_Cfg.h"
#include "CanIf.h"

void Can_Init(const Can_ConfigType *ConfigPtr)
{
    GPIOA->ODR |= (1 << 11);
    Can_Controllers[ConfigPtr->CanControllerId]->MCR = 0x00010002;
    Can_Controllers[ConfigPtr->CanControllerId]->MCR |= ConfigPtr->CanHohHandler->CanDebugMode << 16;
    Can_Controllers[ConfigPtr->CanControllerId]->MCR |= ConfigPtr->CanTrigger << 7;
    Can_Controllers[ConfigPtr->CanControllerId]->MCR |= ConfigPtr->CanHohHandler->CanAutoBusOff << 6;
    Can_Controllers[ConfigPtr->CanControllerId]->MCR |= ConfigPtr->CanHohHandler->CanAutoWakeUp << 5;
    Can_Controllers[ConfigPtr->CanControllerId]->MCR |= ConfigPtr->CanHohHandler->CanAutoRetransmission << 4;
    Can_Controllers[ConfigPtr->CanControllerId]->MCR |= ConfigPtr->CanHohHandler->CanReceiveFifoLockedMode << 3;
    Can_Controllers[ConfigPtr->CanControllerId]->MCR |= ConfigPtr->CanHohHandler->CanTransmitFifoPriority << 2;
    Can_Controllers[ConfigPtr->CanControllerId]->FMR |= (1 << 0);
    for (int i = 0; i < CAN_NUMBER_OF_FILTER; i++)
    {
        Can_Controllers[ConfigPtr->CanControllerId]->FS1R |= (ConfigPtr->CanIdMaskMode >> 1) << i;
        Can_Controllers[ConfigPtr->CanControllerId]->FM1R |= (ConfigPtr->CanIdMaskMode & 0x01) << i;
        Can_Controllers[ConfigPtr->CanControllerId]->FFA1R |= (ConfigPtr->CanFilter[i].Fifo << i);
        Can_Controllers[ConfigPtr->CanControllerId]->FA1R |= (1 << ConfigPtr->CanFilter[i].Bank);
        if (ConfigPtr->CanIdType == CAN_STANDARD_ID)
        {
            Can_Controllers[ConfigPtr->CanControllerId]->sFilterRegister[i].FR1 = ((ConfigPtr->CanFilter[i].Id) << 21);
            Can_Controllers[ConfigPtr->CanControllerId]->sFilterRegister[i].FR2 = ((ConfigPtr->CanFilter[i].Mask) << 21);
        }
        else
        {
            Can_Controllers[ConfigPtr->CanControllerId]->sFilterRegister[i].FR1 = ((ConfigPtr->CanFilter[i].Id) << 3) | (1 << 2);
            Can_Controllers[ConfigPtr->CanControllerId]->sFilterRegister[i].FR2 = ((ConfigPtr->CanFilter[i].Mask) << 3) | (1 << 2);
        }
    }
    Can_Controllers[ConfigPtr->CanControllerId]->FMR &= ~(1 << 0);
}

void Can_DeInit(void)
{
    for (uint8 i = 0; i < CAN_MAX_CONTROLLER; i++)
    {
        Can_Controllers[i]->MCR = 0x00010002;
    }
}

Std_ReturnType Can_SetBaudrate(uint8 Controller, uint16 BaudRateConfigID)
{
    Can_Controllers[Controller]->MCR &= ~(1 << 1);
    while (Can_Controllers[Controller]->MSR & (1 << 1))
        ;
    Can_Controllers[Controller]->MCR |= (1 << 0);
    while (!(Can_Controllers[Controller]->MSR & (1 << 0)))
        ;
    Can_Controllers[Controller]->BTR = (CanConfig[Controller].CanBaudrateConfig[BaudRateConfigID].CanBaudratePrescaler << 0) |
                                       (CanConfig[Controller].CanBaudrateConfig[BaudRateConfigID].CanTseg1 << 16) |
                                       (CanConfig[Controller].CanBaudrateConfig[BaudRateConfigID].CanTseg2 << 20) |
                                       (CanConfig[Controller].CanBaudrateConfig[BaudRateConfigID].CanSjw << 24);

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
        while ((Can_Controllers[Controller]->MSR & (1 << 0)))
            ;
        break;
    case CAN_CS_STOPPED:
        Can_Controllers[Controller]->MCR |= (1 << 0);
        while (!(Can_Controllers[Controller]->MSR & (1 << 0)))
            ;
        break;
    case CAN_CS_SLEEP:
        Can_Controllers[Controller]->MCR |= (1 << 1);
        while (!(Can_Controllers[Controller]->MSR & (1 << 1)))
            ;
        break;
    default:
        return E_NOT_OK;
    }
    return E_OK;
}
void Can_DisableControllerInterrupts(uint8 Controller)
{
    NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn);
    Can_Controllers[Controller]->IER = 0;
}

void Can_EnableControllerInterrupts(uint8 Controller)
{
    NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
    Can_Controllers[Controller]->IER = CanConfig[Controller].CanInterruptEnable;
}

Std_ReturnType Can_CheckWakeup(uint8 Controller)
{
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
        return E_NOT_OK;
    }
    ControllerModePtr = &Can_ControllerState[Controller];
    return E_OK;
}

Std_ReturnType Can_GetControllerRxErrorCounter(uint8 ControllerId, uint8 *RxErrorCounterPtr)
{
    if (ControllerId >= CAN_MAX_CONTROLLER || RxErrorCounterPtr == NULL_PTR)
    {
        return E_NOT_OK;
    }
    *RxErrorCounterPtr = (Can_Controllers[ControllerId]->ESR >> 24) & 0xFF;
    return E_OK;
}

Std_ReturnType Can_GetControllerTxErrorCounter(uint8 ControllerId, uint8 *TxErrorCounterPtr)
{
    if (ControllerId >= CAN_MAX_CONTROLLER || TxErrorCounterPtr == NULL_PTR)
    {
        return E_NOT_OK;
    }
    *TxErrorCounterPtr = (Can_Controllers[ControllerId]->ESR >> 16) & 0xFF;
    return E_OK;
}

Std_ReturnType Can_SetCanPnFrameDataMask(uint8 Controller, uint8 *DataMaskArrayPtr, uint8 Length)
{
    return 0;
}

Std_ReturnType Can_Write(Can_HwHandleType Hth, const Can_PduType *PduInfo)
{
    if (!(Can_Controllers[PduInfo->swPduHandle]->TSR & (1 << (26 + Hth))))
    {
        return E_NOT_OK;
    }
    Can_Controllers[PduInfo->swPduHandle]->sTxMailBox[Hth].TDTR = PduInfo->length;
    Can_Controllers[PduInfo->swPduHandle]->sTxMailBox[Hth].TDLR = *((uint32 *)PduInfo->sdu);
    Can_Controllers[PduInfo->swPduHandle]->sTxMailBox[Hth].TDHR = *((uint32 *)(PduInfo->sdu + 4));
    if (CanConfig[PduInfo->swPduHandle].CanIdType == CAN_STANDARD_ID)
    {
        Can_Controllers[PduInfo->swPduHandle]->sTxMailBox[Hth].TIR = 0;
        Can_Controllers[PduInfo->swPduHandle]->sTxMailBox[Hth].TIR |= (PduInfo->id << 21);
        Can_Controllers[PduInfo->swPduHandle]->sTxMailBox[Hth].TIR &= ~(1 << 1);
        Can_Controllers[PduInfo->swPduHandle]->sTxMailBox[Hth].TIR |= (1 << 0);
    }
    else if (CanConfig[PduInfo->swPduHandle].CanIdType == CAN_EXTENDED_ID)
    {
        Can_Controllers[PduInfo->swPduHandle]->sTxMailBox[Hth].TIR = 0;
        Can_Controllers[PduInfo->swPduHandle]->sTxMailBox[Hth].TIR |= (PduInfo->id << 3);
        Can_Controllers[PduInfo->swPduHandle]->sTxMailBox[Hth].TIR |= (1 << 2);
        Can_Controllers[PduInfo->swPduHandle]->sTxMailBox[Hth].TIR &= ~(1 << 1);
        Can_Controllers[PduInfo->swPduHandle]->sTxMailBox[Hth].TIR |= (1 << 0);
    }
    else
    {
        return E_NOT_OK;
    }
    return E_OK;
}

void USB_LP_CAN1_RX0_IRQHandler(void)
{
    uint8 tempPayload[8];
    PduInfoType rxPdu;
    Can_HwType mailbox;

    mailbox.CanId = (CAN1->sFIFOMailBox[0].RIR >> 21) & 0x7FF;
    mailbox.Hoh = 0;

    *((uint32 *)(&tempPayload[0])) = CAN1->sFIFOMailBox[0].RDLR;
    *((uint32 *)(&tempPayload[4])) = CAN1->sFIFOMailBox[0].RDHR;

    rxPdu.SduDataPtr = tempPayload;
    rxPdu.SduLength = (CAN1->sFIFOMailBox[0].RDTR & 0x0F);

    CanIf_RxIndication(&mailbox, &rxPdu);
}