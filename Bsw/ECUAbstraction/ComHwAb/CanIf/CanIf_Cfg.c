#include "CanIf_Cfg.h"
#include "CanIf.h"
#include "Can_Cfg.h"
static uint8 CanIfSensor1TxDataBuffer[8] = {0x01, 0x02, 0x04, 0x04, 0x05, 0x06, 0x07, 0x08};
static uint8 CanIfSensor2TxDataBuffer[8] = {0x02, 0x01, 0x01, 0x04, 0x05, 0x06, 0x07, 0x08};
static uint8 CanIfSensor3TxDataBuffer[8] = {0x03, 0x02, 0x02, 0x04, 0x05, 0x06, 0x07, 0x08};

PduInfoType CanIfTxPduInfo[] = {
    [SENSOR_0] = {.SduDataPtr = CanIfSensor1TxDataBuffer,
                  .SduLength = 8},
    [SENSOR_1] = {.SduDataPtr = CanIfSensor2TxDataBuffer,
                  .SduLength = 8},
    [SENSOR_2] = {.SduDataPtr = CanIfSensor3TxDataBuffer,
                  .SduLength = 8},
};

uint8 CanIfSensor1RxDataBuffer[8];
uint8 CanIfSensor2RxDataBuffer[8];
uint8 CanIfSensor3RxDataBuffer[8];

PduInfoType CanIfRxPduInfo[] = {
    [SENSOR_0] = {.SduDataPtr = CanIfSensor1RxDataBuffer,
                  .SduLength = 0},
    [SENSOR_1] = {.SduDataPtr = CanIfSensor2RxDataBuffer,
                  .SduLength = 0},
    [SENSOR_2] = {.SduDataPtr = CanIfSensor3RxDataBuffer,
                  .SduLength = 0},
};

CanIf_ConfigType CanIfConfig = {
    .TxPduConfig = CanTxPduInfo,
    .RxPduConfig = CanIfRxPduInfo,
};