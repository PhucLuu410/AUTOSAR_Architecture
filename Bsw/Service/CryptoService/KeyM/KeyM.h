#ifndef KEY_M__
#define KEY_M__

#include "NvM.h"
#include "Std_GeneralTypes.h"
#include "Csm.h"

Std_ReturnType KeyM_Finalize(const uint8 *RequestDataPtr,
                             uint16 RequestDataLength,
                             uint8 *ResponseDataPtr,
                             uint16 ResponseMaxDataLength);

#endif