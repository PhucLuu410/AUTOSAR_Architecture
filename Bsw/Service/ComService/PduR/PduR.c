#include "PduR.h"
#include "PduR_Cfg.h"

static PduR_StateType PduR_ModuleState = PDUR_UNINIT;
static const PduR_PBConfigType *PduR_ConfigPtr = NULL_PTR;

void PduR_Init(const PduR_PBConfigType *ConfigPtr)
{
    PduR_ConfigPtr = ConfigPtr;
    PduR_ModuleState = PDUR_ONLINE;
}

void PduR_RxIndication(PduIdType RxPduId, const PduInfoType *PduInfoPtr)
{
}