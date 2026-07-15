#ifndef MEMACC_GENERALTYPES_H
#define MEMACC_GENERALTYPES_H

#include "Std_GeneralTypes.h"

/*=========================================================
 * Memory Identifier
 *========================================================*/
typedef uint16 MemAcc_MemoryIdType;

/*=========================================================
 * Address Type
 *========================================================*/
typedef uint32 MemAcc_AddressType;

/*=========================================================
 * Length Type
 *========================================================*/
typedef uint32 MemAcc_LengthType;

/*=========================================================
 * Job Result
 *========================================================*/
typedef enum
{
    MEMACC_JOB_OK,
    MEMACC_JOB_PENDING,
    MEMACC_JOB_FAILED,
    MEMACC_JOB_CANCELLED,
    MEMACC_JOB_ECC_ERROR,
    MEMACC_JOB_VERIFY_FAILED
} MemAcc_JobResultType;

/*=========================================================
 * Memory Device Type
 *========================================================*/
typedef enum
{
    MEMACC_MEMORY_INTERNAL_FLASH,
    MEMACC_MEMORY_EXTERNAL_FLASH,
    MEMACC_MEMORY_EEPROM,
    MEMACC_MEMORY_FRAM
} MemAcc_MemoryType;

/*=========================================================
 * Access Operation
 *========================================================*/
typedef enum
{
    MEMACC_OPERATION_IDLE,
    MEMACC_OPERATION_READ,
    MEMACC_OPERATION_WRITE,
    MEMACC_OPERATION_ERASE,
    MEMACC_OPERATION_COMPARE
} MemAcc_OperationType;

/*=========================================================
 * Access Mode
 *========================================================*/
typedef enum
{
    MEMACC_MODE_SYNC,
    MEMACC_MODE_ASYNC
} MemAcc_AccessModeType;

/*=========================================================
 * Memory Area Descriptor
 *========================================================*/
typedef struct
{
    MemAcc_MemoryIdType MemoryId;

    MemAcc_MemoryType MemoryType;

    MemAcc_AddressType StartAddress;

    MemAcc_LengthType Size;

} MemAcc_MemoryAreaType;

/*=========================================================
 * Job Information
 *========================================================*/
typedef struct
{
    MemAcc_OperationType Operation;

    MemAcc_AddressType Address;

    MemAcc_LengthType Length;

    MemAcc_JobResultType Result;

} MemAcc_JobInfoType;

#endif