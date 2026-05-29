#include "Can_Cfg.h"
#include "Can.h"
#include "Can_GeneralTypes.h"

Can_Filter CanFilter[NUMBER_OF_CAN_FILTERS] = {
    [0] = {
        .FilterStatus = CAN_FILTER_ON,
        .FilterIdType = CAN_FILTER_STANDART_ID,
        .FilterMode = CAN_FILTER_MODE_LISTMODE,
        .FilterScale = CAN_FILTER_SCALE_2_16,
        .FilterId1 = 0x123,
        .FilterId2 = 0x127,
        .FilterId3 = 0x7FF,
        .FilterId4 = 0x7FF,
        .FilterMask1 = 0x7FF,
        .FilterMask2 = 0x7FF,
        .FilterAssignToFifo = 0,
    },
};

Can_Baudrate CanBaudrate[NUMBER_OF_CAN_CONTROLLERS] = {
    {
        .Brp = 8,
        .Baudrate = 100000,
        .Clock = 8000000,
    },
};

Can_Isr CanIsrUsed[] = {
    {
        .CanSleepIsr = TRUE,
        .CanWakeupIsr = TRUE,
        .ErrorIsr = TRUE,
        .LastErrorCodeIsr = TRUE,
        .BusOffIsr = TRUE,
        .ErrorPassiveIsr = TRUE,
        .ErrorWarningIsr = TRUE,
        .Fifo1OverrunIsr = TRUE,
        .Fifo1OFullIsr = TRUE,
        .Fifo1MessagePendingIsr = TRUE,
        .Fifo0OverrunIsr = TRUE,
        .Fifo0OFullIsr = TRUE,
        .Fifo0MessagePendingIsr = TRUE,
        .TransmitMailboxEmptyIsr = TRUE,
    },
    {
        .CanSleepIsr = TRUE,
        .CanWakeupIsr = TRUE,
        .ErrorIsr = TRUE,
        .LastErrorCodeIsr = FALSE,
        .BusOffIsr = FALSE,
        .ErrorPassiveIsr = FALSE,
        .ErrorWarningIsr = FALSE,
        .Fifo1OverrunIsr = FALSE,
        .Fifo1OFullIsr = FALSE,
        .Fifo1MessagePendingIsr = FALSE,
        .Fifo0OverrunIsr = FALSE,
        .Fifo0OFullIsr = FALSE,
        .Fifo0MessagePendingIsr = FALSE,
        .TransmitMailboxEmptyIsr = TRUE,
    }};

Can_Controller CanController[NUMBER_OF_CAN_CONTROLLERS] = {
    {
        .CanControllerNumber = CAN_1_CONTROLLER,
        .CanDebugMode = CAN_DEBUG_MODE_FREEZE,
        .CanTimerTriggerCommunicationMode = CAN_TIMER_TRIGGER_COMMUNICATION_MODE_DISABLE,
        .CanAutoBusOffMode = CAN_AUTO_BUS_OFF_MODE_ENABLE,
        .CanAutoWakeupMode = CAN_AUTO_WAKEUP_MODE_DISABLE,
        .CanAutoRetransmission = CAN_AUTO_RETRANSMISSION_ENABLE,
        .CanReceiveFifoLockedMode = CAN_RECEIVE_FIFO_LOCKED_MODE_OVERWRITE,
        .CanTransmitFifoPriority = CAN_TRANSMIT_FIFO_PRIORITY_BY_ID,
    },
};

Can_HwUnit CanHwUnit[NUMBER_OF_CAN_HW_UNITS] = {
    {

    },
};

Can_ConfigType CanConfig = {
    .CanFilter = &CanFilter[0],
    .CanBaudrate = &CanBaudrate[0],
    .CanHwUnit = &CanHwUnit[0],
    .CanController = &CanController[0],
    .CanIsr = &CanIsrUsed[0]};