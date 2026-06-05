#ifndef __LINIF_H__
#define __LINIF_H__

#include "Com.h"
#include "ComStack_Types.h"
#include "EcuM.h"
#include "Lin_GeneralTypes.h"
#include "Std_Types.h"

typedef uint8 LinIf_SchHandleType;

typedef enum
{
    LINTP_APPLICATIVE_SCHEDULE,
    LINTP_DIAG_REQUEST,
    LINTP_DIAG_RESPONSE,
} LinTp_Mode;

typedef enum
{
    LINIF_E_SCHEDULE_TABLE_SWITCH_REQUEST_NOT_ACCEPTED,
    LINTP_E_DROPPED_CONSECUTIVE_FRAMES_DETECTED,
    LINTP_E_LINTPNAS_TIMEOUT_OCCURRED,
    LINTP_E_LINTPNCR_TIMEOUT_OCCURRED,
    LINTP_E_LINTPNCS_TIMEOUT_OCCURRED,
    LINTP_E_SWAPPED_CONSECUTIVE_FRAMES_RECEIVED,
} LinTpDemEventParameterRefs;

typedef struct
{
    uint8 LinTpNcr;
    uint32 LinTpRxNSduId;
    uint8 LinTpRxNSduNad;
    uint8 LinTpRxNSduChannelRef;
    uint8 LinTpRxNSduPduRef;
} LinTpRxNSdu;

typedef struct
{
    uint8 LinTpMaxBufReq;
    uint8 LinTpNas;
    uint8 LinTpNcs;
    uint32 LinTpTxNSduId;
    uint8 LinTpTxNSduNad;
    uint8 LinTpTxNSduChannelRef;
    uint8 LinTpTxNSduPduRef;
} LinTpTxNSdu;

typedef struct
{
    boolean LinTpDropNotRequestedNad;
    uint32 LinTpMaxNumberOfRespPendingFrames;
    uint8 LinTpP2Max;
    uint8 LinTpP2Timing;
    boolean LinTpScheduleChangeDiag;
    uint8 LinTpChannelRef;
} LinTpChannelConfig;

typedef struct
{
    boolean LinTpChangeParameterApi;
} LinTpGeneral;

typedef struct
{
    uint32 LinTpMaxRxNSduCnt;
    uint32 LinTpMaxTxNSduCnt;
    LinTpChannelConfig *LinTpChannelConfig_0;
    LinTpDemEventParameterRefs *LinTpDemEventParameterRefs_0;
    LinTpRxNSdu *LinTpRxNSdu_0;
    LinTpTxNSdu *LinTpTxNSdu_0;
} LinTpGlobalConfig;

typedef struct
{
    LinTpGeneral LinTpGeneral_0;
    LinTpGlobalConfig LinTpGlobalConfig_0;
} LinTp_ConfigType;

//------------------------------------------------------------------------

typedef struct
{
    uint8 Channel;
    uint8 LocalPduId;
    uint8 Pid;
    uint8 CsModel;
    Lin_FrameResponseType Response;
} Lin_FrameConfigType;

typedef struct
{
    boolean LinIfBusMirroringSupported;
    boolean LinIfDevErrorDetect;
    boolean LinIfMultipleDriversSupported;
    boolean LinIfMultipleTrcvDriverSupported;
    boolean LinIfNcOptionalRequestSupported;
    boolean LinIfTpSupported;
    boolean LinIfTrcvDriverSupported;
    boolean LinIfVersionInfoApi;
} LinIfGeneral;

typedef enum
{
    LINIF_MASTER,
    LINIF_SLAVE,
} LinIfNodeType;

typedef enum
{
    GOTO_SLEEP_CDD,
    GOTO_SLEEP_LIN_SM,
} LinIfGotoSleepConfirmationUL;

typedef enum
{
    WAKEUP_CDD,
    WAKEUP_LIN_SM,
} LinIfWakeupConfirmationUL;

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

typedef enum
{
    CLASSIC,
    ENHANCED,
} LinIfChecksumType;

typedef struct
{
    LinIfChecksumType LinIfChecksumType_0;
    uint8 LinIfFrameId;
    uint8 LinIfFrameIndex;
    LinIfFrameType LinIfFrameType_0;
    uint8 LinIfFixedFrameSdu[8];
} LinIfFrame;

typedef struct
{
    uint32 LinIfChannelRef_0;
    uint32 LinIfComMNetworkHandleRef_0;
    uint8 LinIfBusIdleTimeoutPeriod_0;
    LinIfGotoSleepConfirmationUL LinIfGotoSleepConfirmationUL_0;
    LinIfWakeupConfirmationUL LinIfWakeupConfirmationUL_0;
    uint32 LinIfMainFunctionPeriod;
    LinIfFrame *LinIfFrame_0;
    LinIfNodeType LinIfNodeType_0;

} LinIfChannel;

typedef struct
{
    LinIfChannel *LinIfChannel_0;
} LinIfGlobalConfig;

typedef struct
{
    LinIfGlobalConfig *LinIfGlobalConfig_0;
    LinIfGeneral *LinIfGeneral_0;
} LinIf_ConfigType;

void LinIf_Init(const LinIf_ConfigType *ConfigPtr);
Std_ReturnType LinIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr);
Std_ReturnType LinIf_GotoSleep(NetworkHandleType Channel);
Std_ReturnType LinIf_Wakeup(NetworkHandleType Channel);
void LinIf_RxIndication(NetworkHandleType Channel, uint8 *Lin_SduPtr);

void LinTp_Init(const LinTp_ConfigType *ConfigPtr);
Std_ReturnType LinTp_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr);
void LinTp_Shutdown(void);
Std_ReturnType LinTp_ChangeParameter(PduIdType id, TPParameterType parameter, uint16 value);
Std_ReturnType LinIf_EnableBusMirroring(NetworkHandleType Channel, boolean MirroringActive);

#endif