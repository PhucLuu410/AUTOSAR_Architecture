#include "KeyM.h"

Std_ReturnType KeyM_Finalize(const uint8 *RequestDataPtr,
                             uint16 RequestDataLength,
                             uint8 *ResponseDataPtr,
                             uint16 ResponseMaxDataLength)
{
    MemIf_Write(0, 0, NULL_PTR);
    return E_OK;
}
