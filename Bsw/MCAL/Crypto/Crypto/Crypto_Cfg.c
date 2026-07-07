#include "Crypto_Cfg.h"

Crypto_DriverObjectType Crypto_DriverObject = {0};

Crypto_ConfigType Crypto_Config = {
    1,
    &Crypto_DriverObject,
};