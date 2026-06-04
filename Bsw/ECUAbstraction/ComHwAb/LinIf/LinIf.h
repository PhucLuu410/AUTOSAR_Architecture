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

//------------------------------------------------------------------------

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

typedef struct
{
    LinIfFrameType LinIfFrameType_0;
} LinIfFrame;

typedef struct
{
    uint32 LinIfChannelRef_0;
    uint32 LinIfComMNetworkHandleRef_0;
    LinIfNodeType LinIfNodeType_0;
    uint8 LinIfBusIdleTimeoutPeriod_0;
    LinIfGotoSleepConfirmationUL LinIfGotoSleepConfirmationUL_0;
    LinIfWakeupConfirmationUL LinIfWakeupConfirmationUL_0;
    uint32 LinIfMainFunctionPeriod;
    LinIfFrame LinIfFrame_0;
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

typedef struct
{

} LinTp_ConfigType;

void LinIf_Init(const LinIf_ConfigType *ConfigPtr);
Std_ReturnType LinIf_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr);
Std_ReturnType LinIf_ScheduleRequest(NetworkHandleType Channel, LinIf_SchHandleType ScheduleTableIdx);
Std_ReturnType LinIf_GotoSleep(NetworkHandleType Channel);
Std_ReturnType LinIf_Wakeup(NetworkHandleType Channel);
Std_ReturnType LinIf_GetPIDTable(NetworkHandleType Channel, Lin_FramePidType *PidBuffer, uint8 *PidBufferLength);
Std_ReturnType LinIf_SetPIDTable(NetworkHandleType Channel, Lin_FramePidType *PidBuffer, uint8 PidBufferLength);
Std_ReturnType LinIf_GetConfiguredNAD(NetworkHandleType Channel, uint8 *Nad);
Std_ReturnType LinIf_SetConfiguredNAD(NetworkHandleType Channel, uint8 Nad);

void LinTp_Init(const LinTp_ConfigType *ConfigPtr);
Std_ReturnType LinTp_Transmit(PduIdType TxPduId, const PduInfoType *PduInfoPtr);
void LinTp_Shutdown(void);
Std_ReturnType LinTp_ChangeParameter(PduIdType id, TPParameterType parameter, uint16 value);
// Std_ReturnType LinIf_CheckWakeup(EcuM_WakeupSourceType WakeupSource);
Std_ReturnType LinIf_EnableBusMirroring(NetworkHandleType Channel, boolean MirroringActive);

// void LinIf_WakeupConfirmation(EcuM_WakeupSourceType WakeupSource);
void LinIf_MainFunction_SendHeader1(void);
void LinIf_MainFunction_SendHeader2(void);
void LinIf_MainFunction_SendHeader3(void);
void LinIf_MainFunction_SendData3(void);
void LinIf_MainFunction_ReceiveStatus(void);
#endif