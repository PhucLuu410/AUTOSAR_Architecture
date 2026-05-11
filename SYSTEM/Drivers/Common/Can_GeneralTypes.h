#ifndef __CAN_GENERAL_TYPES_H
#define __CAN_GENERAL_TYPES_H

#include "ComStack_Types.h"

#define CAN_BUSY 0x02

typedef uint32 Can_IdType;
typedef uint16 Can_HwHandleType;
typedef uint32 Can_TimeStampType;

typedef struct
{
    Can_IdType CanId;
    Can_HwHandleType Hoh;
    uint8 ControllerId;
} Can_HwType;

typedef struct
{
    PduIdType swPduHandle;
    uint8 length;
    Can_IdType id;
    uint8 *sdu;
} Can_PduType;

typedef enum
{
    CAN_ERRORSTATE_ACTIVE,
    CAN_ERRORSTATE_PASSIVE,
    CAN_ERRORSTATE_BUSOFF
} Can_ErrorStateType;

typedef enum
{
    CAN_CS_UNINIT,
    CAN_CS_STARTED,
    CAN_CS_STOPPED,
    CAN_CS_SLEEP
} Can_ControllerStateType;

typedef enum
{
    CAN_ERROR_BIT_MONITORING1,
    CAN_ERROR_BIT_MONITORING2,
    CAN_ERROR_BIT,
    CAN_ERROR_CHECK_ACK_FAILED,
    CAN_ERROR_ACK_DELIMITER,
    CAN_ERROR_ARBITRATION_LOST,
    CAN_ERROR_OVERLOAD,
    CAN_ERROR_CHECK_FORM_FAILED,
    CAN_ERROR_CHECK_STUFFING_FAILED,
    CAN_ERROR_CHECK_CRC_FAILED,
    CAN_ERROR_BUS_LOCK,
} Can_ErrorType;

#endif /* CAN_GENERAL_TYPES_H */