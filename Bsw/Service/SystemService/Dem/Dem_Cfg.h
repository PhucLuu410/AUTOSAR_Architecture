// Dem_Cfg.h
#ifndef DEM_CFG_H
#define DEM_CFG_H

#include "Std_Types.h"

typedef uint16 Dem_EventIdType;

#define DEM_EVENT_NONE 0x0000U
#define DEM_EVENT_CAN_TIMEOUT 0x0001U
#define DEM_EVENT_CAN_BUS_OFF 0x0002U
#define DEM_EVENT_LIN_TIMEOUT 0x0003U
#define DEM_EVENT_LIN_CRC_ERR 0x0004U
#define DEM_EVENT_MOTOR_STALL 0x0005U

#define NUMBER_OF_DEM_EVENTS 6

typedef struct
{
    Dem_EventIdType EventId;
    uint32_t DtcCode;
    const char *DtcString;
} Dem_DtcConfigType;

extern const Dem_DtcConfigType Dem_DtcConfigTable[NUMBER_OF_DEM_EVENTS];

#endif