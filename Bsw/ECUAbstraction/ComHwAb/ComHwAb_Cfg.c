#include "ComHwAb_Cfg.h"
#include "ComHwAb.h"

uint8 Buffer_Motor[4] = {0x12, 0x13, 0x14, 0x15};
uint8 Buffer_Arm[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

CanDataTransmit DataTransmit[] = {
    [0] = {.CanId = 0x123,
           .CanDataLength = 4,
           .Data = Buffer_Motor},
    [1] = {.CanId = 0x123,
           .CanDataLength = 8,
           .Data = Buffer_Arm}};