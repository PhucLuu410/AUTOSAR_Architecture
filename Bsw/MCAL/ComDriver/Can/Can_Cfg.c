#include "Can_Cfg.h"
#include "Can.h"
#include "Can_GeneralTypes.h"

Can_Isr CanIsrUsed[] = {
    {
        .CanSleepIsr = FALSE,
        .CanWakeupIsr = FALSE,
        .ErrorIsr = FALSE,
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
        .TransmitMailboxEmptyIsr = FALSE,
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
    .CanHwUnit = &CanHwUnit[0],
    .CanController = &CanController[0],
    .CanIsr = &CanIsrUsed[0]};