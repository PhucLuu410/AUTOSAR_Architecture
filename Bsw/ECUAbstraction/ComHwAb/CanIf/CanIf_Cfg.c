#include "CanIf_Cfg.h"
#include "CanIf.h"

static uint8 CanIfBuffer_ReceiveSensor1[8] = {0};
static uint8 CanIfBuffer_ReceiveSensor2[8] = {0};
static uint8 CanIfBuffer_ReceiveSensor3[8] = {0};

Can_PduType Can_RxPduInfo[] = {
    [0] = {.swPduHandle = 0,
           .length = 8,
           .id = 0x127,
           .sdu = CanIfBuffer_ReceiveSensor1},
    [1] = {.swPduHandle = 0,
           .length = 8,
           .id = 0x123,
           .sdu = CanIfBuffer_ReceiveSensor2},
    [2] = {.swPduHandle = 0,
           .length = 8,
           .id = 0x321,
           .sdu = CanIfBuffer_ReceiveSensor3}};

CanIfRxPduCfg CanIfRxPduType = {
    .RxPduType = Can_RxPduInfo,
};

uint8 CanIfBuffer_Transmit[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

PduInfoType CanIfPduInfo = {
    .SduDataPtr = CanIfBuffer_Transmit,
    .SduLength = 8,
};

Can_PduType Can_TxPduInfo[] = {
    [CAN_SENSOR_0] = {.swPduHandle = 0,
                      .length = 8,
                      .id = 0x127,
                      .sdu = NULL_PTR},
    [CAN_SENSOR_1] = {.swPduHandle = 0,
                      .length = 8,
                      .id = 0x123,
                      .sdu = NULL_PTR},
    [CAN_SENSOR_2] = {.swPduHandle = 0,
                      .length = 8,
                      .id = 0x321,
                      .sdu = NULL_PTR}};

CanIfTxPduCfg CanIfTxPduType = {
    .TxPduType = Can_TxPduInfo,
};

CanIf_ConfigType CanIf_Config = {
    .TxPduConfig = &CanIfTxPduType,
    .RxPduConfig = &CanIfRxPduType,
};
