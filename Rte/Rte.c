#include "Rte.h"

Std_ReturnType Rte_Write_RobotControl(Robot_Control_PDU_Type *AppData)
{
    if (AppData == NULL_PTR)
    {
        return E_NOT_OK;
    }

    uint8 *pBuffer = ComTxSignalConfig[0].SduDataPtr;

    pBuffer[0] = (uint8)(AppData->SteeringAngle >> 8);
    pBuffer[1] = (uint8)(AppData->SteeringAngle & 0xFF);
    pBuffer[2] = AppData->Speed;
    pBuffer[3] = AppData->Mode;
    pBuffer[4] = AppData->BrakeForce;
    pBuffer[5] = AppData->Reserved;
    pBuffer[6] = AppData->AliveCounter;

    uint8 crc = 0;
    for (int i = 0; i < 7; i++)
    {
        crc ^= pBuffer[i];
    }
    pBuffer[7] = crc;
    return Com_SendSignal(0);
}

Std_ReturnType Rte_Write_RobotSafety(Robot_Safety_PDU_Type *AppData)
{
    if (AppData == NULL_PTR)
    {
        return E_NOT_OK;
    }

    uint8 *pBuffer = ComTxSignalConfig[1].SduDataPtr;

    pBuffer[0] = (uint8)(AppData->SteeringAngle >> 8);
    pBuffer[1] = (uint8)(AppData->SteeringAngle & 0xFF);
    pBuffer[2] = AppData->Speed;
    pBuffer[3] = AppData->Mode;
    pBuffer[4] = AppData->BrakeForce;
    pBuffer[5] = AppData->Reserved;
    pBuffer[6] = AppData->AliveCounter;

    uint8 crc = 0;
    for (int i = 0; i < 7; i++)
    {
        crc ^= pBuffer[i];
    }
    pBuffer[7] = crc;
    return Com_SendSignal(0);
}