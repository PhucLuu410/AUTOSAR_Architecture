#ifndef DEM_H
#define DEM_H

#include "Dem_Types.h"
#include "Dem_Cfg.h"

void Dem_Init(void);
Std_ReturnType Dem_SetEventStatus(Dem_EventIdType EventId, Dem_EventStatusType EventStatus);
Std_ReturnType Dem_GetEventStatusByte(Dem_EventIdType EventId, uint8 *StatusBytePtr);

#endif /* DEM_H */