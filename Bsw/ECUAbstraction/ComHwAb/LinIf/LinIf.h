#ifndef __LINIF_H__
#define __LINIF_H__

#include "Com.h"
#include "ComStack_Types.h"
#include "EcuM.h"
#include "Lin_GeneralTypes.h"
#include "Std_Types.h"

typedef uint8 LinIf_SchHandleType;

typedef struct
{
    boolean LinIfBusMirroringSupported;
    boolean LinIfDevErrorDetect;
    boolean LinIfMultipleDriversSupported;
    boolean LinIfMultipleTrcvDriverSupported;
    boolean LinIfNcOptionalRequestSupported;
    boolean LinIfTpSupported;
    boolean LinIfTrcvDriverSupported;
} LinIfGeneral;

typedef enum
{
    WAKE_UP_CDD,
    WAKE_UP_LIN_SM,
} LinIfWakeupConfirmationUL;

typedef enum
{
    GOTO_SLEEP_CDD,
    GOTO_SLEEP_LIN_SM,
} LinIfGotoSleepConfirmationUL;

typedef enum
{
    CLASSIC,
    ENHANCED,
} LinIfChecksumType;

typedef enum
{
    ASSIGN,
    ASSIGN_FRAME_ID_RANGE,
    ASSIGN_NAD,
    CONDITIONAL,
    EVENT_TRIGGERED,
    FREE,
    MRF,
    SAVE_CONFIGURATION,
    SPORADIC,
    SRF,
    UNASSIGN,
    UNCONDITIONAL,
} LinIfFrameType;

typedef struct
{
    LinIfChecksumType LinIfChecksum;
    uint8 LinIfFrameId;
    uint8 LinIfFrameIndex;
    LinIfFrameType LinIfFrame;
} LinIfFrame;

typedef struct
{
    uint32 LinIfBusIdleTimeoutPeriod;
    LinIfGotoSleepConfirmationUL LinIfGotoSleepConfirmationUL;
    uint32 LinIfMainFunctionPeriod;
    LinIfWakeupConfirmationUL LinIfWakeupConfirmationUL;
    uint8 LinIfChannelRef;
    uint8 LinIfComMNetworkHandleRef;
    LinIfFrame *LinIfFrameCfg;
} LinIfChannel;

typedef struct
{
    LinIfChannel *LinIfChannelCfg;
} LinIfGlobalConfig;

typedef struct
{
    LinIfGeneral LinIfGeneralCfg;
    LinIfGlobalConfig LinIfGlobalCfg;
} LinIf_ConfigType;

void LinIf_Init(const LinIf_ConfigType *ConfigPtr);
Std_ReturnType LinIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr);
Std_ReturnType LinIf_GotoSleep(NetworkHandleType Channel);
Std_ReturnType LinIf_Wakeup(NetworkHandleType Channel);
void LinIf_RxIndication(NetworkHandleType Channel, uint8 *Lin_SduPtr);
Std_ReturnType LinIf_EnableBusMirroring(NetworkHandleType Channel, boolean MirroringActive);

//-------------------------------------------------------------------------------------------------

// typedef struct
// {
//     LinTpGeneral LinTpGeneralCfg;
//     LinTpGlobalConfig LinTpGlobalCfg;
// } LinTp_ConfigType;

// void LinTp_Init(const LinTp_ConfigType *ConfigPtr);
// Std_ReturnType LinTp_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr);
// void LinTp_Shutdown(void);
// Std_ReturnType LinTp_ChangeParameter(PduIdType id, TPParameterType parameter, uint16 value);
// void LinIf_MainFunction_LinTpMasterSend_SF_FF(void);
// void LinIf_MainFunction_LinTpMasterSend_CF(void);

#endif