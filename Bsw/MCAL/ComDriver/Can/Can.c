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
    uint32 Ts1 = 0;
    uint32 Ts2 = 0;
    uint32 Total_TQ = LocalConfig->CanBaudrate->Clock / (LocalConfig->CanBaudrate->Baudrate * LocalConfig->CanBaudrate->Brp);
    Ts2 = ((Total_TQ * 3) + 5) / 10;

    if (Total_TQ > (1 + Ts2))
    {
        Ts1 = Total_TQ - 1 - Ts2;
    }
    else
    {
        return E_NOT_OK;
    }
    Can_Hardware[Controller]->BTR = ((Ts2 - 2) << 20) | ((Ts1) << 16) | (LocalConfig->CanBaudrate->Brp - 1);
    return E_OK;
}
Std_ReturnType Can_Write(Can_HwHandleType Hth, const Can_PduType *PduInfo)
{
    return 0;
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

void USB_LP_CAN1_RX0_IRQHandler(void)
{
}

void USB_HP_CAN1_TX_IRQHandler(void)
{
}