#include "Dem_Cfg.h"

const Dem_DtcConfigType Dem_DtcConfigTable[NUMBER_OF_DEM_EVENTS] = {
    {DEM_EVENT_NONE, 0x000000, "NO_ERROR"},
    {DEM_EVENT_CAN_TIMEOUT, 0xD01150, "U0115: Lost Communication with CAN Node"},
    {DEM_EVENT_CAN_BUS_OFF, 0xD01100, "U0110: CAN Bus Off Error"},
    {DEM_EVENT_LIN_TIMEOUT, 0xD01400, "U0140: Lost Communication with LIN Slave"},
    {DEM_EVENT_LIN_CRC_ERR, 0xD01410, "U0141: LIN Slave Checksum Invalid"},
    {DEM_EVENT_MOTOR_STALL, 0x102340, "P0234: Mechanical Motor Stall Detected"}};