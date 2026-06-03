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
    LINIF_UNCONDITIONAL,
    LINIF_EVENT_TRIGGERED,
    LINIF_SPORADIC,
    LINIF_DIAGNOSTIC,
    LINIF_MRF,
    LINIF_SRF
} LinIf_FrameType;

typedef struct
{
    uint8 FramePid;
    uint8 Length;
    LinIf_FrameType Type;
    PduIdType PduRef;
    uint8 Direction;
    uint16 SlotOffsetMs;
} LinIf_FrameConfigType;

typedef enum
{
    LINIF_RUN_CONTINUOUS,
    LINIF_RUN_ONCE
} LinIf_ScheduleModeType;

typedef struct
{
    uint8 ScheduleId;
    LinIf_ScheduleModeType Mode;
    const LinIf_FrameConfigType *const Frames;
    uint8 NumFrames;
    uint32 SlotTimeMs;
} LinIf_ScheduleTableType;

typedef struct
{
    NetworkHandleType ChannelId;
    const LinIf_ScheduleTableType *const ScheduleTables;
    uint8 NumScheduleTables;
    boolean IsMaster;
} LinIf_ChannelConfigType;

typedef struct
{
    const LinIf_ChannelConfigType *const Channels;
    uint8 NumChannels;
} LinIf_ConfigType;

typedef struct
{
    uint8 Nad;
    uint32 P2Timing;
    uint32 StMin;
    uint16 MaxBufferSize;
} LinTp_ChannelConfigType;

typedef struct
{
    const LinTp_ChannelConfigType *const Channels;
    uint8 NumChannels;
} LinTp_ConfigType;

typedef enum
{
    LINTP_APPLICATIVE_SCHEDULE,
    LINTP_DIAG_REQUEST,
    LINTP_DIAG_RESPONSE,
} LinTp_Mode;

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
Std_ReturnType LinIf_HeaderIndication(NetworkHandleType Channel, Lin_PduType *PduPtr);
void LinIf_RxIndication(NetworkHandleType Channel, uint8 *Lin_SduPtr);
void LinIf_TxConfirmation(NetworkHandleType Channel);
void LinIf_LinErrorIndication(NetworkHandleType Channel, Lin_SlaveErrorType ErrorStatus);
void LinIf_MainFunction_ElectricDoor(void);
void LinIf_MainFunction_Diag(void);
#endif