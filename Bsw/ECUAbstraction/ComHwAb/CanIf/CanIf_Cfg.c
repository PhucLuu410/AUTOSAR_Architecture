#include "CanIf_Cfg.h"

#include "Can_Cfg.h"

static uint8 CanIfBufferReceive[SIZE_OF_CAN_IF_TABLE][8] = {0};

#define SIZE_OF_CAN_IF_TABLE 3

CanIfPduRxTableType CanIfRxTable[] = {
    [0] = {.RxPduId = 0,
           .CanId = 0x123,
           .Length = 0,
           .data = CanIfBufferReceive[0]},
    [1] = {.RxPduId = 1,
           .CanId = 0x127,
           .Length = 0,
           .data = CanIfBufferReceive[1]},
    [2] = {.RxPduId = 2,
           .CanId = 0x321,
           .Length = 0,
           .data = CanIfBufferReceive[2]}};

CanIf_PduTableConfig CanIf_PduTable[SIZE_OF_CAN_IF_TABLE] = {[0] = {.CanChannel = CAN_MAILBOX_0,
                                                                    .CanIf_LocalId = 0,
                                                                    .CanIf_CanId = 0x123},
                                                             [1] = {.CanChannel = CAN_MAILBOX_1,
                                                                    .CanIf_LocalId = 1,
                                                                    .CanIf_CanId = 0x127},
                                                             [2] = {.CanChannel = CAN_MAILBOX_2,
                                                                    .CanIf_LocalId = 2,
                                                                    .CanIf_CanId = 0x321}};

CanIf_PduModeType CanIfPduMode[SIZE_OF_CAN_IF_TABLE] = {CANIF_OFFLINE, CANIF_OFFLINE, CANIF_OFFLINE};

CanIf_ConfigType CanIfConfig = {.RxTableConfig = CanIfRxTable,
                                .TxTableConfig = CanIf_PduTable};
