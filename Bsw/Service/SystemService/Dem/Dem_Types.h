
#ifndef DEM_TYPES_H
#define DEM_TYPES_H

#include "Std_GeneralTypes.h"

typedef uint8 Dem_EventStatusType;
#define DEM_EVENT_STATUS_PASSED 0x00U
#define DEM_EVENT_STATUS_FAILED 0x01U
#define DEM_EVENT_STATUS_PREPASSED 0x02U
#define DEM_EVENT_STATUS_PREFAILED 0x03U

#define DEM_UDS_STATUS_TF (1U << 0)
#define DEM_UDS_STATUS_PDTC (1U << 3)
#define DEM_UDS_STATUS_CDTC (1U << 5)

typedef uint16 Dem_EventIdType;

typedef struct
{
    Dem_EventIdType EventId;
    uint32_t DtcCode;
    sint8 DecrementStepSize;
    sint8 PassThreshold;
    sint8 IncrementStepSize;
    sint8 FailThreshold;
} Dem_EventDataConfigType;

typedef struct
{
    sint8 FaultDetectionCounter;
    uint8 UdsStatusByte;
} Dem_EventStatusRamType;

#endif