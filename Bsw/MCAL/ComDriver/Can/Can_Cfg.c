#include "Can_Cfg.h"
#include "Can.h"
#include "Can_GeneralTypes.h"

static Can_HohHandlerConfigType CanHohHandler = {
    .CanDebugMode = CAN_DEBUG_MODE_FREEZE,
    .CanAutoBusOff = CAN_AUTO_BUS_OFF_OFF,
    .CanAutoWakeUp = CAN_AUTO_WAKEUP_OFF,
    .CanAutoRetransmission = CAN_RETRANSMISSION_ON,
    .CanReceiveFifoLockedMode = CAN_RECEIVE_FIFO_LOCKED_MODE_OFF,
    .CanTransmitFifoPriority = CAN_TRANSMIT_FIFO_PRIORITY_OFF};

static Can_BaudrateConfigType CanBaudrateConfig[] = {
    {.CanBaudrateId = 0,
     .CanTseg1 = 12,
     .CanTseg2 = 3,
     .CanBaudratePrescaler = 19,
     .CanSjw = 1}};

static Can_FilterType CanFilterList[CAN_NUMBER_OF_FILTER] = {
    {.Fifo = CAN_FIFO_0_MASK, .Bank = CAN_FILTER_BANK_0, .Id = 0x00000000, .Mask = 0x00000000}};

const Can_ConfigType CanConfig[] = {
    [0] = {
        .CanControllerId = CAN_1,
        .CanIdType = CAN_STANDARD_ID,
        .CanIdMaskMode = CAN_ID_MASK_1_32_BIT,
        .CanFilter = CanFilterList,
        .CanBaudrateConfig = &CanBaudrateConfig[0],
        .CanTrigger = CAN_SW_TRIGGER,
        .CanHohHandler = &CanHohHandler,
        .CanMultiplexTransmission = CAN_MULTIPLEX_OFF,
        .CanEventDetection = CAN_EVENT_DETECT_INTERRUPT,
        .CanInterruptEnable = ((1 << CAN_WAKEUP_INTERUPT) |
                               (1 << CAN_ERROR_INTERUPT) |
                               (1 << CAN_BUS_OFF_INTERUPT) |
                               (1 << CAN_ERROR_PASSIVE_INTERUPT) |
                               (1 << CAN_WARNING_INTERUPT) |
                               (1 << CAN_FIFO1_OVERRUN_INTERUPT) |
                               (1 << CAN_FIFO1_FULL_INTERNAL_INTERUPT) |
                               (1 << CAN_FIFO1_MESSAGE_PENDING_INTERUPT) |
                               (1 << CAN_FIFO0_OVERRUN_INTERUPT) |
                               (1 << CAN_FIFO0_FULL_INTERNAL_INTERUPT) |
                               (1 << CAN_FIFO0_MESSAGE_PENDING_INTERUPT) |
                               (1 << CAN_TX_MAILBOX_EMPTY_INTERUPT)) &
                              0xFFFF,
        .CanTxHardwareObject = 0}};

Can_PduType Can_TxPduInfo = {
    .swPduHandle = CAN_1,
    .length = 8,
    .id = 0x127,
    .sdu = (uint8 *)"ABCDEEGH"};

CAN_TypeDef *const Can_Controllers[CAN_MAX_CONTROLLER] = {CAN1};
Can_ControllerStateType Can_ControllerState[CAN_MAX_CONTROLLER] = {CAN_CS_UNINIT};