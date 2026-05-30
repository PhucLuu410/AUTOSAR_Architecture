#include "CanIf_Cfg.h"

#include "Can_Cfg.h"

#define SIZE_OF_CAN_IF_TABLE 3

CanIf_PduRxTableConfig CanIf_RxTable[] = {
    [0] = {.CanIf_LocalId = 1,
           .CanIf_CanId = 0x123,
           .Length = 0,
           .data = NULL_PTR},
    [1] = {.CanIf_LocalId = 0,
           .CanIf_CanId = 0x127,
           .Length = 0,
           .data = NULL_PTR},
    [2] = {.CanIf_LocalId = 2,
           .CanIf_CanId = 0x321,
           .Length = 0,
           .data = NULL_PTR}};

CanIf_PduTxTableConfig CanIf_TxTable[SIZE_OF_CAN_IF_TABLE] = {
    [0] = {.Hoh = 0,
           .CanIf_LocalId = 0,
           .CanIf_CanId = 0x123},
    [1] = {.Hoh = 1,
           .CanIf_LocalId = 1,
           .CanIf_CanId = 0x127},
    [2] = {.Hoh = 2,
           .CanIf_LocalId = 2,
           .CanIf_CanId = 0x321}};

CanIf_PduModeType CanIfPduMode[SIZE_OF_CAN_IF_TABLE] = {
    CANIF_OFFLINE,
    CANIF_OFFLINE,
    CANIF_OFFLINE};

CanIf_ConfigType CanIfConfig = {.RxTableConfig = CanIf_RxTable,
                                .TxTableConfig = CanIf_TxTable};
