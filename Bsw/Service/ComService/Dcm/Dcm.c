#include "Dcm.h"
#include "Rte.h"

typedef enum
{
    Diag_Close = 0,
    Diag_Open = 1,
} Diag_StateType;

uint8 Dcm_Buffer[30] = {0};
Diag_StateType Diag_Flag = Diag_Close;
volatile uint8_t debug_counter = 0;

BufReq_ReturnType Dcm_CopyRxData(PduIdType id, const PduInfoType *info, PduLengthType *bufferSizePtr)
{
    for (int i = 0; i < info->SduLength; i++)
    {
        Dcm_Buffer[i] = info->SduDataPtr[i];
    }
    return BUFREQ_OK;
}

BufReq_ReturnType Dcm_StartOfReception(PduIdType id, const PduInfoType *info, PduLengthType TpSduLength, PduLengthType *bufferSizePtr)
{
    if (TpSduLength > 30)
    {
        return BUFREQ_NOT_OK;
    }
    else
    {
        return BUFREQ_OK;
    }
}

void Dcm_TpRxIndication(PduIdType id, Std_ReturnType result)
{
    if (result != E_OK)
    {
        return;
    }

    if (Dcm_Buffer[0] == 0x50 && Dcm_Buffer[1] == 0x03 && Dcm_Buffer[2] == 0x00)
    {
        Diag_Flag = Diag_Open;
    }

    uint8_t sid = Dcm_Buffer[0];
    uint16 ResponseSID = (Dcm_Buffer[1] << 8 | Dcm_Buffer[2]);

    if (sid == 0x62 && Diag_Flag == Diag_Open)
    {
        switch (ResponseSID)
        {
        case 0x010C:
            Rte_Write_Diag_RPM(((uint16_t)Dcm_Buffer[3] << 8) | Dcm_Buffer[4]);
            break;
        case 0x0105:
            Rte_Write_Diag_Temp(Dcm_Buffer[3]);
            break;
        case 0xF189:
            // SW_VERSION
            break;
        case 0xF190:
            // VIN
            break;
        case 0xF001:
            // eVCU_Snapshot
            debug_counter = 6;
            break;
        case 0x2711:
            // NOT_SUPPORT_DIAG
            break;
        default:
            break;
        }
    }
    // Clear buffer for debug
    for (int i = 0; i < 30; i++)
    {
        Dcm_Buffer[i] = 0;
    }
}
