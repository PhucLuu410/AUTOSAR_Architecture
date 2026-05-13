#include "CanIf_Cfg.h"

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

static CanIfRxTable RxTable[] = {[SENSOR_0] = {.CanId = SENSOR_0_ID},
                                 [SENSOR_1] = {.CanId = SENSOR_1_ID},
                                 [SENSOR_2] = {.CanId = SENSOR_2_ID}};

CanIf_ConfigType CanIfConfig = {.TxPduConfig = CanIfTxPduInfo,
                                .RxTable = RxTable};
