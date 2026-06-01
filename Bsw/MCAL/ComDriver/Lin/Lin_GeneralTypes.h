#ifndef LIN_GENERAL_TYPES_H
#define LIN_GENERAL_TYPES_H

#include "Std_Types.h"

typedef uint8 Lin_FramePidType;
typedef uint8 Lin_FrameDlType;

typedef enum
{
    LIN_ENHANCED_CS,
    LIN_CLASSIC_CS,
} Lin_FrameCsModelType;

typedef enum
{
    LIN_FRAMERESPONSE_TX,
    LIN_FRAMERESPONSE_RX,
    LIN_FRAMERESPONSE_IGNORE,
} Lin_FrameResponseType;

typedef struct
{
    Lin_FramePidType Pid;
    Lin_FrameDlType Dl;
    Lin_FrameCsModelType CsModel;
    Lin_FrameResponseType Response;
    uint8 *SduDataPtr;
} Lin_PduType;

typedef enum
{
    LIN_NOT_OK,
    LIN_OK,
    LIN_BUSY,
    LIN_TX_HEADER_ERROR,
    LIN_TX_ERROR,
    LIN_RX_OK,
    LIN_RX_BUSY,
    LIN_RX_ERROR,
    LIN_RX_NO_RESPONSE,
    LIN_OPERATIONAL,
    LIN_CH_SLEEP,
} Lin_StatusType;

typedef enum
{
    LIN_ERR_HEADER,
    LIN_ERR_RESP_STOPBIT,
    LIN_ERR_RESP_CHKSUM,
    LIN_ERR_RESP_DATABIT,
    LIN_ERR_NO_RESP,
    LIN_ERR_INC_RESP,
} Lin_SlaveErrorType;

#endif