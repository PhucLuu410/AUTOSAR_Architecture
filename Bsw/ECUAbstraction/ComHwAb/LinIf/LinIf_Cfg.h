#include "LinIf.h"
#include "Lin_Cfg.h"

typedef enum
{
    LINTP_UNINIT,
    LINTP_INIT,
} LinTpStateMachine;

typedef enum
{
    LINTP_MASTER_IDLE,
    LINTP_MASTER_WAIT_FC,
    LINTP_MASTER_SEND_CF,
    LINTP_MASTER_BUSY,
    LINTP_MASTER_FAIL,
} LinTpMaterSubStateMachine;

typedef enum
{
    LINTP_SLAVE_IDLE,
    LINTP_SLAVE_WAIT_CF,
    LINTP_SLAVE_SEND_FC,
    LINTP_SLAVE_BUSY,
    LINTP_SLAVE_FAIL,
} LinTpSlaveSubStateMachine;

extern const LinIf_ConfigType LinIf_Config;
extern const LinTp_ConfigType LinTp_Config;

extern LinTpTxNSdu LinTpTxNSduConfig[1];
extern LinTpRxNSdu LinTpRxNSduConfig[1];

extern uint8 Buffer_ID_0x12[20];