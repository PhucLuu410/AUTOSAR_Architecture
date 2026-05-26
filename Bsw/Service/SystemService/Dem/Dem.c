#include "Dem.h"

// static Dem_EventStatusRamType Dem_EventRamTable[NUMBER_OF_DEM_EVENTS];

// void Dem_Init(void)
// {
//     for (uint16 i = 0; i < NUMBER_OF_DEM_EVENTS; i++)
//     {
//         Dem_EventRamTable[i].FaultDetectionCounter = 0;
//         Dem_EventRamTable[i].UdsStatusByte = 0x00U;
//     }

//     /*
//      * Ở ĐÂY: Trong thực tế, bạn có thể gọi NvM_ReadBlock() để nạp lại các lỗi cũ
//      * từ Flash của STM32 lên RAM để kiểm tra xem chu kỳ trước xe có đang dính lỗi gì không.
//      */
// }

// Std_ReturnType Dem_SetEventStatus(Dem_EventIdType EventId, Dem_EventStatusType EventStatus)
// {
//     if ((EventId == DEM_EVENT_NONE) || (EventId >= NUMBER_OF_DEM_EVENTS))
//     {
//         return E_NOT_OK;
//     }
//     // const Dem_EventDataConfigType *cfgPtr = &Dem_DtcConfigTable[EventId];
//     Dem_EventStatusRamType *ramPtr = &Dem_EventRamTable[EventId];
//     if (EventStatus == DEM_EVENT_STATUS_FAILED)
//     {
//         ramPtr->UdsStatusByte |= DEM_UDS_STATUS_TF;
//         if (ramPtr->FaultDetectionCounter < cfgPtr->FailThreshold)
//         {
//             ramPtr->FaultDetectionCounter += cfgPtr->IncrementStepSize;
//             if (ramPtr->FaultDetectionCounter >= cfgPtr->FailThreshold)
//             {
//                 ramPtr->FaultDetectionCounter = cfgPtr->FailThreshold;
//                 ramPtr->UdsStatusByte |= (DEM_UDS_STATUS_CDTC | DEM_UDS_STATUS_PDTC);
//             }
//         }
//     }
//     else if (EventStatus == DEM_EVENT_STATUS_PASSED)
//     {
//         ramPtr->UdsStatusByte &= ~DEM_UDS_STATUS_TF;
//         if (ramPtr->FaultDetectionCounter > cfgPtr->PassThreshold)
//         {
//             ramPtr->FaultDetectionCounter += cfgPtr->DecrementStepSize;
//             if (ramPtr->FaultDetectionCounter <= cfgPtr->PassThreshold)
//             {
//                 ramPtr->FaultDetectionCounter = cfgPtr->PassThreshold;
//                 ramPtr->UdsStatusByte &= ~DEM_UDS_STATUS_CDTC;
//             }
//         }
//     }

//     return E_OK;
// }

// Std_ReturnType Dem_GetEventStatusByte(Dem_EventIdType EventId, uint8 *StatusBytePtr)
// {
//     if ((EventId == DEM_EVENT_NONE) || (EventId >= NUMBER_OF_DEM_EVENTS) || (StatusBytePtr == NULL_PTR))
//     {
//         return E_NOT_OK;
//     }

//     *StatusBytePtr = Dem_EventRamTable[EventId].UdsStatusByte;
//     return E_OK;
// }