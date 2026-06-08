#include "LinIf.h"
#include "Lin_Cfg.h"
#include "PduR.h"
#include "PduR_Cfg.h"

#define NUMBER_OF_LINIF_FRAME_TX 4
#define NUMBER_OF_LINIF_FRAME_RX 4

#define NUMBER_OF_LINTP_FRAME_TX 1
#define NUMBER_OF_LINTP_FRAME_RX 1
typedef enum
{
    LIN_DIRECTION_RX,
    LIN_DIRECTION_TX
} LinIf_DirectionType;

typedef struct
{
    uint8 Channel;
    uint8 PduId;
    uint8 Pid;
    uint8 Length;
    uint8 CsModel;
    LinIf_DirectionType Direction;
    void (*Receive_Func)(PduIdType TxPduId, const PduInfoType *PduInfoPtr);
} LinIf_ReceivePduType;

extern LinIf_ConfigType LinIf_Config;
extern LinTp_ConfigType LinTp_Config;
extern LinIf_ReceivePduType LinIfFrameConfigRx[NUMBER_OF_LINIF_FRAME_RX];

void LinTp_RxIndication(PduIdType TxPduId, const PduInfoType *PduInfoPtr);