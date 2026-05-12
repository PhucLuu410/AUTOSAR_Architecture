#include "PduR.h"
#include "PduR_Cfg.h"

static PduR_StateType PduR_ModuleState = PDUR_UNINIT;
static const PduR_PBConfigType *PduR_ConfigPtr = NULL_PTR;

uint8 PduR_Buffer[8] = {0};
uint8 PduR_BufferLength = 0;
uint32 id = 0;
void PduR_Init(const PduR_PBConfigType *ConfigPtr)
{
    PduR_ConfigPtr = ConfigPtr;
    PduR_ModuleState = PDUR_ONLINE;
}

void PduR_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
    id = RxPduId;
    for (int i = 0; i < PduInfoPtr->SduLength; i++)
    {
        PduR_Buffer[i] = PduInfoPtr->SduDataPtr[i];
    }
    PduR_BufferLength = PduInfoPtr->SduLength;
}