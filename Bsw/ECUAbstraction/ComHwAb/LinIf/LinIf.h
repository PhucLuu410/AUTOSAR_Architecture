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
    /* https://www.autosar.org/fileadmin/standards/R25-11/CP/AUTOSAR_CP_SWS_LINInterface.pdf#page=143&zoom=100,410,190 */
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

typedef struct
{
    /* https://www.autosar.org/fileadmin/standards/R25-11/CP/AUTOSAR_CP_SWS_LINInterface.pdf#page=149&zoom=100,405,914 */
    uint32 LinIfBusIdleTimeoutPeriod;
    LinIfGotoSleepConfirmationUL LinIfGotoSleepConfirmationUL;
    uint32 LinIfMainFunctionPeriod;
    LinIfWakeupConfirmationUL LinIfWakeupConfirmationUL;
    uint8 LinIfChannelRef;
    uint8 LinIfComMNetworkHandleRef;
} LinIfChannel;

typedef struct
{
    /* https://www.autosar.org/fileadmin/standards/R25-11/CP/AUTOSAR_CP_SWS_LINInterface.pdf#page=149&zoom=100,340,180 */
    LinIfChannel *LinIfChannelCfg;
} LinIfGlobalConfig;

typedef struct
{
    /* https://www.autosar.org/fileadmin/standards/R25-11/CP/AUTOSAR_CP_SWS_LINInterface.pdf */
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