#ifndef __RTE_H
#define __RTE_H

#include "Com.h"
#include "Com_Cfg.h"

typedef struct
{
    uint16 SteeringAngle; // 2 byte: Góc lái
    uint8 Speed;          // 1 byte: Tốc độ
    uint8 Mode;           // 1 byte: Chế độ (Auto/Manual)
    uint8 BrakeForce;     // 1 byte: Lực phanh
    uint8 Reserved;       // 1 byte: Dự phòng
    uint8 AliveCounter;   // 1 byte: Nhịp tim hệ thống
    uint8 Checksum;       // 1 byte: Kiểm tra lỗi
} Robot_Control_PDU_Type;

typedef struct
{
    uint16 SteeringAngle; // 2 byte: Góc lái
    uint8 Speed;          // 1 byte: Tốc độ
    uint8 Mode;           // 1 byte: Chế độ (Auto/Manual)
    uint8 BrakeForce;     // 1 byte: Lực phanh
    uint8 Reserved;       // 1 byte: Dự phòng
    uint8 AliveCounter;   // 1 byte: Nhịp tim hệ thống
    uint8 Checksum;       // 1 byte: Kiểm tra lỗi
} Robot_Safety_PDU_Type;

Std_ReturnType Rte_Write_RobotControl(Robot_Control_PDU_Type *AppData);
Std_ReturnType Rte_Write_RobotSafety(Robot_Safety_PDU_Type *AppData);

#endif