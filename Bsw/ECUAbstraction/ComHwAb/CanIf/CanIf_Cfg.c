#include "CanIf_Cfg.h"

#include "Can_Cfg.h"

static uint8 CanIfBufferReceive[CAN_SERSOR_DATA_LENGTH][8] = {0};

CanIfPduRxTableType CanIfRxTable[] = {
    [0] = {.RxPduId = 0,
           .CanId = SENSOR_0_ID,
           .Length = 0,
           .data = CanIfBufferReceive[0]},
    [1] = {.RxPduId = 1,
           .CanId = SENSOR_1_ID,
           .Length = 0,
           .data = CanIfBufferReceive[1]},
    [2] = {.RxPduId = 2,
           .CanId = SENSOR_2_ID,
           .Length = 0,
           .data = CanIfBufferReceive[2]}};

static uint8 CanIfBufferTransmit[8] = {0};

Can_PduType CanTxPduInfo[] = {[0] = {.swPduHandle = SENSOR_0,
                                     .length = 0,
                                     .id = SENSOR_0_ID,
                                     .sdu = CanIfBufferTransmit},
                              [1] = {.swPduHandle = SENSOR_1,
                                     .length = 0,
                                     .id = SENSOR_1_ID,
                                     .sdu = CanIfBufferTransmit},
                              [2] = {.swPduHandle = SENSOR_2,
                                     .length = 0,
                                     .id = SENSOR_2_ID,
                                     .sdu = CanIfBufferTransmit}};

CanIfPduTxTableType CanIfTxTable[] = {
    [0] = {.TxPduId = 0,
           .TxPduTable = &CanTxPduInfo[0]},
    [1] = {.TxPduId = 1,
           .TxPduTable = &CanTxPduInfo[1]},
    [2] = {.TxPduId = 2,
           .TxPduTable = &CanTxPduInfo[2]}};

CanIf_PduModeType CanIfPduMode[CAN_SERSOR_DATA_LENGTH] = {CANIF_OFFLINE, CANIF_OFFLINE, CANIF_OFFLINE};

CanIf_ConfigType CanIfConfig = {.RxTableConfig = CanIfRxTable,
                                .TxTableConfig = CanIfTxTable};
