#include "Dcm.h"
#include "Dcm_Cfg.h"
#include "Rte_Diag.h"

Std_ReturnType Dcm_ReadData(uint8 *Data)
{
    if (Data != NULL_PTR)
    {
        for (int i = 0; i < 30; i++)
        {
            Data[i] = Dcm_Rx_Buffer[i];
        }
        return E_OK;
    }
    return E_NOT_OK;
}

Std_ReturnType Dcm_WriteData(const uint8 *Data, uint16 DataLength, Dcm_NegativeResponseCodeType *ErrorCode)
{
    PduInfoType PduInfo;
    PduInfo.SduDataPtr = (uint8 *)Data;
    PduInfo.SduLength = DataLength;
    return PduR_DcmTransmit(DCM_ID, &PduInfo);
}

BufReq_ReturnType Dcm_CopyRxData(PduIdType id, const PduInfoType *info, PduLengthType *bufferSizePtr)
{
    for (int i = 0; i < info->SduLength; i++)
    {
        Dcm_Rx_Buffer[i] = info->SduDataPtr[i];
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

    if (Dcm_Rx_Buffer[0] == 0x50 && Dcm_Rx_Buffer[1] == 0x03 && Dcm_Rx_Buffer[2] == 0x00)
    {
        Diag_Flag = Diag_Open;
        for (int i = 0; i < 30; i++)
        {
            Dcm_Rx_Buffer[i] = 0;
        }
    }
}
