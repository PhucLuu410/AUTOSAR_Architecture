#ifndef __CAN_EXTERNALS_H__
#define __CAN_EXTERNALS_H__

#include "Can_GeneralTypes.h"

boolean LPDU_CAN_RX(uint8 Hrh, Can_IdType CanId, uint8 CanDataLegth, const uint8 *CanSduPtr);

#endif