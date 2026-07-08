#ifndef CAN_GENERALTYPES_H
#define CAN_GENERALTYPES_H

#include "ComStack_Types.h"
#include "Std_GeneralTypes.h"

#define CAN_BUSY 0x02

typedef uint32 Can_IdType;
typedef uint16 Can_HwHandleType;

typedef struct
{
    PduIdType swPduHandle;
    uint8 length;
    Can_IdType id;
    uint8 *sdu;
} Can_PduType;

typedef struct
{
    Can_IdType CanId;
    Can_HwHandleType Hoh;
    uint8 ControllerId;
} Can_HwType;

typedef enum
{
    CAN_ERRORSTATE_ACTIVE,
    CAN_ERRORSTATE_PASSIVE,
    CAN_ERRORSTATE_BUSOFF
} Can_ErrorStateType;

typedef enum
{
    CAN_CS_UNINIT = 0x00,
    CAN_CS_STOPPED = 0x01,
    CAN_CS_STARTED = 0x02,
    CAN_CS_SLEEP = 0x03
} Can_ControllerStateType;

typedef enum
{
    CAN_ERROR_BIT_MONITORING1 = 0x01,
    CAN_ERROR_BIT_MONITORING0 = 0x02,
    CAN_ERROR_BIT = 0x03,
    CAN_ERROR_CHECK_ACK_FAILED = 0x04,
    CAN_ERROR_ACK_DELIMITER = 0x05,
    CAN_ERROR_ARBITRATION_LOST = 0x06,
    CAN_ERROR_OVERLOAD = 0x07,
    CAN_ERROR_CHECK_FORM_FAILED = 0x08,
    CAN_ERROR_CHECK_STUFFING_FAILED = 0x09,
    CAN_ERROR_CHECK_CRC_FAILED = 0x0A,
    CAN_ERROR_BUS_LOCK = 0x0B
} Can_ErrorType;

typedef struct
{
    uint32 nanoseconds;
    uint32 seconds;
} Can_TimeStampType;

#endif