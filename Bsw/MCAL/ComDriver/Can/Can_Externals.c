#include "Can_Externals.h"
#include "Can.h"
#include "Can_Cfg.h"
#include "stm32f103xb.h"
boolean LPDU_CAN_RX(uint8 Hrh, Can_IdType CanId, uint8 CanDataLegth, const uint8 *CanSduPtr)
{
    return true;
}