#include "Can_Cfg.h"

CAN_TypeDef *const CAN_Controllers[2] = {CAN1, 0};

const Can_ConfigType CanConfig = {
    .baudRate = 500000,
    .mode = CAN_MODE_SILENT_LOOPBACK};