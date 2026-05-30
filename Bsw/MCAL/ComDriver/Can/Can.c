#include "Can.h"
#include "Can_Cfg.h"
#include "CanIf.h"
#include "stm32f103xb.h"

#define CAN_UNINIT 0x00
#define CAN_READY 0x01

static const Can_ConfigType *LocalConfig = NULL_PTR;
static uint8 Can_StateMachine[NUMBER_OF_CAN_CONTROLLERS] = {CAN_UNINIT};
static CAN_TypeDef *Can_Hardware[NUMBER_OF_CAN_HW_UNITS] = {CAN1};
Can_ControllerStateType Can_ControllerState[NUMBER_OF_CAN_CONTROLLERS] = {CAN_CS_UNINIT};
static PduIdType Can_TxPduIds[CAN_DRIVER_HOH] = {0};

// CALL BY EcuM module
void Can_Init(const Can_ConfigType *Config)
{
    if (Config == NULL_PTR)
    {
        // Report error
    }

    LocalConfig = Config;

    if (Can_StateMachine[LocalConfig->CanController->CanControllerNumber] == CAN_UNINIT && Config != NULL_PTR)
    {
        Can_Hardware[LocalConfig->CanController->CanControllerNumber]->MCR = 0x00010002;
        Can_Hardware[LocalConfig->CanController->CanControllerNumber]->MCR = LocalConfig->CanController->CanDebugMode << 16 |
                                                                             LocalConfig->CanController->CanTimerTriggerCommunicationMode << 7 |
                                                                             LocalConfig->CanController->CanAutoBusOffMode << 6 |
                                                                             LocalConfig->CanController->CanAutoWakeupMode << 5 |
                                                                             LocalConfig->CanController->CanAutoRetransmission << 4 |
                                                                             LocalConfig->CanController->CanReceiveFifoLockedMode << 3 |
                                                                             LocalConfig->CanController->CanTransmitFifoPriority << 2;

        Can_Hardware[LocalConfig->CanController->CanControllerNumber]->FMR |= (1 << 0);
        for (int i = 0; i < NUMBER_OF_CAN_FILTERS; i++)
        {
            Can_Hardware[LocalConfig->CanController->CanControllerNumber]->FA1R &= ~(1 << i);
            if (LocalConfig->CanFilter[i].FilterStatus == CAN_FILTER_ON)
            {
                if (LocalConfig->CanFilter[i].FilterScale == CAN_FILTER_SCALE_1_32)
                {
                    Can_Hardware[LocalConfig->CanController->CanControllerNumber]->FS1R |= (1 << i);
                }
                else
                {
                    Can_Hardware[LocalConfig->CanController->CanControllerNumber]->FS1R &= ~(1 << i);
                }

                if (LocalConfig->CanFilter[i].FilterMode == CAN_FILTER_MODE_LISTMODE)
                {
                    Can_Hardware[LocalConfig->CanController->CanControllerNumber]->FM1R |= (1 << i);
                }
                else
                {
                    Can_Hardware[LocalConfig->CanController->CanControllerNumber]->FM1R &= ~(1 << i);
                }

                if (LocalConfig->CanFilter[i].FilterAssignToFifo == 1)
                {
                    Can_Hardware[LocalConfig->CanController->CanControllerNumber]->FFA1R |= (1 << i);
                }
                else
                {
                    Can_Hardware[LocalConfig->CanController->CanControllerNumber]->FFA1R &= ~(1 << i);
                }

                if (LocalConfig->CanFilter[i].FilterScale == CAN_FILTER_SCALE_1_32)
                {
                    if (LocalConfig->CanFilter[i].FilterMode == CAN_FILTER_MODE_MASKMODE)
                    {
                        if (LocalConfig->CanFilter[i].FilterIdType == CAN_FILTER_STANDART_ID)
                        {
                            Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFilterRegister[i].FR1 = (LocalConfig->CanFilter[i].FilterId1 << 21);
                            Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFilterRegister[i].FR2 = (LocalConfig->CanFilter[i].FilterMask1 << 21);
                        }
                        else
                        {
                            Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFilterRegister[i].FR1 = (LocalConfig->CanFilter[i].FilterId1 << 3) | (1 << 2); // Kích hoạt bit IDE=1 cho Extended
                            Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFilterRegister[i].FR2 = (LocalConfig->CanFilter[i].FilterMask1 << 3) | (1 << 2);
                        }
                    }
                    else
                    {
                        if (LocalConfig->CanFilter[i].FilterIdType == CAN_FILTER_STANDART_ID)
                        {
                            Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFilterRegister[i].FR1 = (LocalConfig->CanFilter[i].FilterId1 << 21);
                            Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFilterRegister[i].FR2 = (LocalConfig->CanFilter[i].FilterId2 << 21);
                        }
                        else
                        {
                            Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFilterRegister[i].FR1 = (LocalConfig->CanFilter[i].FilterId1 << 3) | (1 << 2);
                            Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFilterRegister[i].FR2 = (LocalConfig->CanFilter[i].FilterId2 << 3) | (1 << 2);
                        }
                    }
                }
                else
                {
                    if (LocalConfig->CanFilter[i].FilterIdType == CAN_FILTER_EXTENDED_ID)
                    {
                        // Report
                    }
                    else
                    {
                        if (LocalConfig->CanFilter[i].FilterMode == CAN_FILTER_MODE_MASKMODE)
                        {
                            Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFilterRegister[i].FR1 = ((LocalConfig->CanFilter[i].FilterId1 << 5) & 0xFFFF) |
                                                                                                                    ((LocalConfig->CanFilter[i].FilterMask1 << 21));

                            Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFilterRegister[i].FR2 = ((LocalConfig->CanFilter[i].FilterId2 << 5) & 0xFFFF) |
                                                                                                                    ((LocalConfig->CanFilter[i].FilterMask2 << 21));
                        }
                        else
                        {
                            Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFilterRegister[i].FR1 = ((LocalConfig->CanFilter[i].FilterId1 << 5) & 0xFFFF) |
                                                                                                                    ((LocalConfig->CanFilter[i].FilterId2 << 21));

                            Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFilterRegister[i].FR2 = ((LocalConfig->CanFilter[i].FilterId3 << 5) & 0xFFFF) |
                                                                                                                    ((LocalConfig->CanFilter[i].FilterId4 << 21));
                        }
                    }
                }

                Can_Hardware[LocalConfig->CanController->CanControllerNumber]->FA1R |= (1 << i);
            }
            else
            {
                Can_Hardware[LocalConfig->CanController->CanControllerNumber]->FA1R &= ~(1 << i);
            }
        }
        Can_Hardware[LocalConfig->CanController->CanControllerNumber]->FMR &= ~(1 << 0);

        Can_Hardware[LocalConfig->CanController->CanControllerNumber]->MCR |= (1 << 0);
        Can_StateMachine[LocalConfig->CanController->CanControllerNumber] = CAN_READY;
        Can_ControllerState[LocalConfig->CanController->CanControllerNumber] = CAN_CS_STOPPED;
    }
    else if (Can_StateMachine[LocalConfig->CanController->CanControllerNumber] != CAN_UNINIT)
    {
        // Report error
    }
}

void Can_DeInit(void)
{
    LocalConfig = NULL_PTR;
    for (uint8 i = 0; i < NUMBER_OF_CAN_CONTROLLERS; i++)
    {
        Can_StateMachine[i] = CAN_UNINIT;
        Can_ControllerState[i] = CAN_CS_UNINIT;
    }
}

Std_ReturnType Can_SetControllerMode(uint8 Controller, Can_ControllerStateType Transition)
{
    uint32 Error;
    switch (Transition)
    {
    case CAN_CS_STOPPED:
        Can_Hardware[Controller]->MCR |= (1 << 0);
        Error = 0xFF;
        while (!(Can_Hardware[Controller]->MSR & (1 << 0)))
        {
            Error--;
            if (Error == 0)
            {
                return E_NOT_OK;
            }
        }
        Can_ControllerState[Controller] = CAN_CS_STOPPED;
        // CanIf_ControllerModeIndication()
        return E_OK;

    case CAN_CS_SLEEP:
        if (Can_ControllerState[Controller] != CAN_CS_STOPPED)
        {
            return E_NOT_OK;
        }
        else
        {
            Can_Hardware[Controller]->MCR &= ~(1 << 0);
            Error = 0xFF;
            while (Can_Hardware[Controller]->MSR & (1 << 0))
            {
                Error--;
                if (Error == 0)
                {
                    return E_NOT_OK;
                }
            }

            Can_Hardware[Controller]->MCR |= (1 << 1);
            Error = 0xFF;
            while (!(Can_Hardware[Controller]->MSR & (1 << 1)))
            {
                Error--;
                if (Error == 0)
                {
                    return E_NOT_OK;
                }
            }
            Can_ControllerState[Controller] = CAN_CS_SLEEP;
            // CanIf_ControllerModeIndication()
            return E_OK;
        }
        break;

    case CAN_CS_STARTED:
        if (Can_ControllerState[Controller] != CAN_CS_STOPPED)
        {
            return E_NOT_OK;
        }
        else
        {
            Can_Hardware[Controller]->MCR &= ~(1 << 1);
            Error = 0xFF;
            while (Can_Hardware[Controller]->MSR & (1 << 1))
            {
                Error--;
                if (Error == 0)
                {
                    return E_NOT_OK;
                }
            }
            Can_Hardware[Controller]->MCR &= ~(1 << 0);
            Error = 0xFF;
            while (Can_Hardware[Controller]->MSR & (1 << 0))
            {
                Error--;
                if (Error == 0)
                {
                    return E_NOT_OK;
                }
            }
            Can_ControllerState[Controller] = CAN_CS_STARTED;
            // CanIf_ControllerModeIndication()
            return E_OK;
        }

    default:
        break;
    }
    return E_NOT_OK;
}

void Can_DisableControllerInterrupts(uint8 Controller)
{
    Can_Hardware[Controller]->IER = 0;
    NVIC_DisableIRQ(USB_LP_CAN1_RX0_IRQn + Controller);
    NVIC_DisableIRQ(USB_HP_CAN1_TX_IRQn);
}
void Can_EnableControllerInterrupts(uint8 Controller)
{
    Can_Hardware[Controller]->IER = (LocalConfig->CanIsr->CanSleepIsr << 17) |
                                    (LocalConfig->CanIsr->CanWakeupIsr << 16) |
                                    (LocalConfig->CanIsr->ErrorIsr << 15) |
                                    (LocalConfig->CanIsr->LastErrorCodeIsr << 11) |
                                    (LocalConfig->CanIsr->BusOffIsr << 10) |
                                    (LocalConfig->CanIsr->ErrorPassiveIsr << 9) |
                                    (LocalConfig->CanIsr->ErrorWarningIsr << 8) |
                                    (LocalConfig->CanIsr->Fifo1OverrunIsr << 6) |
                                    (LocalConfig->CanIsr->Fifo1OFullIsr << 5) |
                                    (LocalConfig->CanIsr->Fifo1MessagePendingIsr << 4) |
                                    (LocalConfig->CanIsr->Fifo0OverrunIsr << 3) |
                                    (LocalConfig->CanIsr->Fifo0OFullIsr << 2) |
                                    (LocalConfig->CanIsr->Fifo0MessagePendingIsr << 1) |
                                    (LocalConfig->CanIsr->TransmitMailboxEmptyIsr << 0);
    NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn + Controller);
    NVIC_EnableIRQ(USB_HP_CAN1_TX_IRQn);
}

Std_ReturnType Can_SetBaudrate(uint8 Controller, uint16 BaudRateConfigID)
{
    if (Can_ControllerState[Controller] != CAN_CS_STOPPED)
    {
        return E_NOT_OK;
    }
    uint8 Tq = 1 + LocalConfig->CanBaudrate[Controller].Seg1 + LocalConfig->CanBaudrate[Controller].Seg2;
    uint32 Baudrate = LocalConfig->CanBaudrate[Controller].Clock / (Tq * LocalConfig->CanBaudrate[Controller].Brp);
    if (Baudrate != LocalConfig->CanBaudrate[Controller].BaudRate)
    {
        return E_NOT_OK;
    }
    Can_Hardware[Controller]->BTR = ((LocalConfig->CanBaudrate[Controller].Seg1 - 1) << 16) |
                                    ((LocalConfig->CanBaudrate[Controller].Seg2 - 1) << 20) |
                                    (LocalConfig->CanBaudrate[Controller].SyncJumpWidth << 24) |
                                    (LocalConfig->CanBaudrate[Controller].Brp - 1);
    return E_OK;
}

Std_ReturnType Can_Write(Can_HwHandleType Hth, const Can_PduType *PduInfo)
{
    if ((Hth > CAN_DRIVER_HOH) || (PduInfo == NULL_PTR))
    {
        return E_NOT_OK;
    }

    if (Can_ControllerState[LocalConfig->CanController->CanControllerNumber] != CAN_CS_STARTED)
    {
        return E_NOT_OK;
    }

    if (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->TSR & (1 << (26 + Hth)))
    {
        if (PduInfo->id > 0x7FF)
        {
            Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sTxMailBox[Hth].TIR = (PduInfo->id << 3) | (1 << 2);
        }
        else
        {
            Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sTxMailBox[Hth].TIR = (PduInfo->id << 21);
        }
        Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sTxMailBox[Hth].TDTR = (PduInfo->length & 0x0F);

        uint32 data_low = 0;
        uint32 data_high = 0;

        for (int k = 0; k < PduInfo->length; k++)
        {
            if (k < 4)
            {
                data_low |= ((uint32)PduInfo->sdu[k] << (8 * k));
            }
            else
            {
                data_high |= ((uint32)PduInfo->sdu[k] << (8 * (k - 4)));
            }
        }

        Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sTxMailBox[Hth].TDLR = data_low;
        Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sTxMailBox[Hth].TDHR = data_high;
        Can_TxPduIds[Hth] = PduInfo->swPduHandle;
        Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sTxMailBox[Hth].TIR |= (1 << 0);

        return E_OK;
    }
    return CAN_BUSY;
}

// void Can_MainFunction_Mode(void)
// {
//     Can_Hardware[LocalConfig->CanController->CanControllerNumber]->MSR |= (1 << 0);
// }

void Can_MainFunction_Wakeup(void)
{
    if (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->MSR & (1 << 3))
    {
        Can_Hardware[LocalConfig->CanController->CanControllerNumber]->MSR |= (1 << 3);
        // CanIf_ControllerModeIndication
    }
}

void Can_MainFunction_BusOff(void)
{
    if (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->ESR & (1 << 3))
    {
        // CanIf_ControllerModeIndication
    }
}

void Can_MainFunction_Write(void)
{
    if (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->TSR & (1 << 0))
    {
        if (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->TSR & (1 << 1))
        {
            CanIf_TxConfirmation(Can_TxPduIds[0]);
        }
        Can_Hardware[LocalConfig->CanController->CanControllerNumber]->TSR |= (1 << 0);
    }
    if (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->TSR & (1 << 8))
    {
        if (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->TSR & (1 << 9))
        {
            CanIf_TxConfirmation(Can_TxPduIds[1]);
        }
        Can_Hardware[LocalConfig->CanController->CanControllerNumber]->TSR |= (1 << 8);
    }
    if (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->TSR & (1 << 16))
    {
        if (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->TSR & (1 << 17))
        {
            CanIf_TxConfirmation(Can_TxPduIds[2]);
        }
        Can_Hardware[LocalConfig->CanController->CanControllerNumber]->TSR |= (1 << 16);
    }
}

void Can_MainFunction_Read(void)
{
    uint8 RxBuffer[8];
    if ((Can_Hardware[LocalConfig->CanController->CanControllerNumber]->RF0R & 0x03) > 0)
    {
        Can_HwType HwType;
        PduInfoType PduInfo;

        HwType.Hoh = 0;
        HwType.ControllerId = 0;
        if (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RIR & (1 << 2))
        {
            HwType.CanId = (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RIR >> 3) & 0x1FFFFFFF;
        }
        else
        {
            HwType.CanId = (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RIR >> 21) & 0x7FF;
        }
        PduInfo.SduLength = (uint8)(Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RDTR & 0x0F);
        PduInfo.SduDataPtr = RxBuffer;
        uint32 data_low = Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RDLR;
        uint32 data_high = Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RDHR;

        for (int i = 0; i < PduInfo.SduLength; i++)
        {
            PduInfo.SduDataPtr[i] = (i < 4) ? (uint8)((data_low >> (8 * i)) & 0xFF)
                                            : (uint8)((data_high >> (8 * (i - 4))) & 0xFF);
        }

        CanIf_RxIndication(&HwType, &PduInfo);
        Can_Hardware[LocalConfig->CanController->CanControllerNumber]->RF0R |= (1 << 5);
    }

    if ((Can_Hardware[LocalConfig->CanController->CanControllerNumber]->RF1R & 0x03) > 0)
    {
        Can_HwType HwType;
        PduInfoType PduInfo;
        HwType.Hoh = 1;
        HwType.ControllerId = 0;
        if (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RIR & (1 << 2))
        {
            HwType.CanId = (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RIR >> 3) & 0x1FFFFFFF;
        }
        else
        {
            HwType.CanId = (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RIR >> 21) & 0x7FF;
        }
        PduInfo.SduLength = (uint8)(Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RDTR & 0x0F);
        PduInfo.SduDataPtr = RxBuffer;
        uint32 data_low = Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RDLR;
        uint32 data_high = Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RDHR;
        for (int i = 0; i < PduInfo.SduLength; i++)
        {
            PduInfo.SduDataPtr[i] = (i < 4) ? (uint8)((data_low >> (8 * i)) & 0xFF)
                                            : (uint8)((data_high >> (8 * (i - 4))) & 0xFF);
        }
        CanIf_RxIndication(&HwType, &PduInfo);
        Can_Hardware[LocalConfig->CanController->CanControllerNumber]->RF1R |= (1 << 5);
    }
}

void USB_LP_CAN1_RX0_IRQHandler(void)
{

    uint8 RxBuffer[8];
    if ((Can_Hardware[LocalConfig->CanController->CanControllerNumber]->RF0R & 0x03) > 0)
    {
        Can_HwType HwType;
        PduInfoType PduInfo;

        HwType.Hoh = 0;
        HwType.ControllerId = 0;
        if (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RIR & (1 << 2))
        {
            HwType.CanId = (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RIR >> 3) & 0x1FFFFFFF;
        }
        else
        {
            HwType.CanId = (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RIR >> 21) & 0x7FF;
        }
        PduInfo.SduLength = (uint8)(Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RDTR & 0x0F);
        PduInfo.SduDataPtr = RxBuffer;
        uint32 data_low = Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RDLR;
        uint32 data_high = Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RDHR;

        for (int i = 0; i < PduInfo.SduLength; i++)
        {
            PduInfo.SduDataPtr[i] = (i < 4) ? (uint8)((data_low >> (8 * i)) & 0xFF)
                                            : (uint8)((data_high >> (8 * (i - 4))) & 0xFF);
        }

        CanIf_RxIndication(&HwType, &PduInfo);
        Can_Hardware[LocalConfig->CanController->CanControllerNumber]->RF0R |= (1 << 5);
    }

    if ((Can_Hardware[LocalConfig->CanController->CanControllerNumber]->RF1R & 0x03) > 0)
    {
        Can_HwType HwType;
        PduInfoType PduInfo;
        HwType.Hoh = 1;
        HwType.ControllerId = 0;
        if (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RIR & (1 << 2))
        {
            HwType.CanId = (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RIR >> 3) & 0x1FFFFFFF;
        }
        else
        {
            HwType.CanId = (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RIR >> 21) & 0x7FF;
        }
        PduInfo.SduLength = (uint8)(Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RDTR & 0x0F);
        PduInfo.SduDataPtr = RxBuffer;
        uint32 data_low = Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RDLR;
        uint32 data_high = Can_Hardware[LocalConfig->CanController->CanControllerNumber]->sFIFOMailBox[0].RDHR;
        for (int i = 0; i < PduInfo.SduLength; i++)
        {
            PduInfo.SduDataPtr[i] = (i < 4) ? (uint8)((data_low >> (8 * i)) & 0xFF)
                                            : (uint8)((data_high >> (8 * (i - 4))) & 0xFF);
        }
        CanIf_RxIndication(&HwType, &PduInfo);
        Can_Hardware[LocalConfig->CanController->CanControllerNumber]->RF1R |= (1 << 5);
    }
}

void USB_HP_CAN1_TX_IRQHandler(void)
{
    if (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->TSR & (1 << 0))
    {
        if (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->TSR & (1 << 1))
        {
            CanIf_TxConfirmation(Can_TxPduIds[0]);
        }
        Can_Hardware[LocalConfig->CanController->CanControllerNumber]->TSR |= (1 << 0);
    }
    if (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->TSR & (1 << 8))
    {
        if (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->TSR & (1 << 9))
        {
            CanIf_TxConfirmation(Can_TxPduIds[1]);
        }
        Can_Hardware[LocalConfig->CanController->CanControllerNumber]->TSR |= (1 << 8);
    }
    if (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->TSR & (1 << 16))
    {
        if (Can_Hardware[LocalConfig->CanController->CanControllerNumber]->TSR & (1 << 17))
        {
            CanIf_TxConfirmation(Can_TxPduIds[2]);
        }
        Can_Hardware[LocalConfig->CanController->CanControllerNumber]->TSR |= (1 << 16);
    }
}