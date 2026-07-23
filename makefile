CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -mcpu=cortex-m3 -mthumb -O0 -g -Wall

MBEDTLS_DIR = ./Bsw/Mcal/Crypto/MbedTLS

MBEDTLS_INCLUDES = \
    -I$(MBEDTLS_DIR)/include \
    -I$(MBEDTLS_DIR)/tf-psa-crypto/include \
    -I$(MBEDTLS_DIR)/tf-psa-crypto/core

MBEDTLS_SRC_FILES = \
    $(wildcard $(MBEDTLS_DIR)/library/*.c) \
    $(wildcard $(MBEDTLS_DIR)/tf-psa-crypto/core/*.c) \
    $(wildcard $(MBEDTLS_DIR)/tf-psa-crypto/drivers/builtin/src/*.c)

IPATH = -I. \
		-I./System/Drivers/CMSIS \
		-I./System/Drivers/Common \
		-I./Bsw/Mcal/IoDriver/Dio \
		-I./Bsw/Mcal/IoDriver/Port \
		-I./Bsw/Mcal/IoDriver/Pwm \
		-I./Bsw/Mcal/IoDriver/Icu \
		-I./Bsw/Mcal/IoDriver \
		-I./Bsw/Mcal/CryptoDriver/Crypto \
		-I./Bsw/Mcal/CryptoDriver/Key \
		-I./Bsw/Mcal/McuDriver/Mcu \
		-I./Bsw/Mcal/ComDriver/Can \
		-I./Bsw/Mcal/ComDriver/Lin \
		-I./Bsw/Mcal/MemDriver/Flash \
		-I./Bsw/EcuAbstraction/IoHwAb \
		-I./Bsw/EcuAbstraction/ComHwAb/CanIf \
		-I./Bsw/EcuAbstraction/ComHwAb/LinIf \
		-I./Bsw/EcuAbstraction/CryptoHwAb \
		-I./Bsw/EcuAbstraction/MemHwAb/Fee \
		-I./Bsw/Service/ComService/PduR \
		-I./Bsw/Service/ComService/Com \
		-I./Bsw/Service/ComService/Dcm \
		-I./Bsw/Service/CryptoService/Csm \
		-I./Bsw/Service/CryptoService/KeyM \
		-I./Bsw/Service/MemService \
		-I./Bsw/Service/SystemService/Os \
		-I./Bsw/Service/SystemService/Dem \
		-I./Bsw/Service/SystemService/Det \
		-I./Rte \
		-I./App/Swc_EngineStatus \
		-I./App/Swc_DiagError \
		-I./App/Swc_Diag \
		-I./App/Swc_VehicleCommand \

SRC = 	./System/Startup/startup.c \
		main.c \
		Bsw/Mcal/IoDriver/Dio/Dio.c  \
		Bsw/Mcal/IoDriver/Dio/Dio_Cfg.c \
		Bsw/Mcal/IoDriver/Port/Port.c \
		Bsw/Mcal/IoDriver/Port/Port_Cfg.c \
		Bsw/Mcal/IoDriver/Pwm/Pwm.c \
		Bsw/Mcal/IoDriver/Pwm/Pwm_Cfg.c \
		Bsw/Mcal/IoDriver/Icu/Icu.c \
		Bsw/Mcal/IoDriver/Icu/Icu_Cfg.c \
		Bsw/Mcal/IoDriver/Adc/Adc.c \
		Bsw/Mcal/IoDriver/Adc/Adc_Cfg.c \
		Bsw/Mcal/McuDriver/Mcu/Mcu.c \
		Bsw/Mcal/McuDriver/Mcu/Mcu_Cfg.c \
		Bsw/Mcal/ComDriver/Can/Can.c \
		Bsw/Mcal/ComDriver/Can/Can_Cfg.c \
		Bsw/Mcal/ComDriver/Lin/Lin.c \
		Bsw/Mcal/ComDriver/Lin/Lin_Cfg.c \
		Bsw/Mcal/CryptoDriver/Crypto/Crypto.c \
		Bsw/Mcal/CryptoDriver/Crypto/Crypto_Cfg.c \
		Bsw/Mcal/CryptoDriver/Crypto/Crypto_Logic.c \
		Bsw/Mcal/CryptoDriver/KeyM/KeyManager.c \
		Bsw/Mcal/MemDriver/Flash/Flash.c \
		Bsw/Mcal/MemDriver/Flash/Flash_Cfg.c \
		Bsw/EcuAbstraction/IoHwAb/IoHwAb.c \
		Bsw/EcuAbstraction/IoHwAb/IoHwAb_Cfg.c \
		Bsw/EcuAbstraction/ComHwAb/CanIf/CanIf.c \
		Bsw/EcuAbstraction/ComHwAb/CanIf/CanIf_Cfg.c \
		Bsw/EcuAbstraction/ComHwAb/CanIf/CanTp.c \
		Bsw/EcuAbstraction/ComHwAb/CanIf/CanTp_Cfg.c \
		Bsw/EcuAbstraction/ComHwAb/LinIf/LinIf.c \
		Bsw/EcuAbstraction/ComHwAb/LinIf/LinIf_Cfg.c \
		Bsw/EcuAbstraction/CryptoHwAb/CryIf.c \
		Bsw/EcuAbstraction/CryptoHwAb/CryIf_Cfg.c \
		Bsw/EcuAbstraction/MemHwAb/Fee/Fee.c \
		Bsw/Service/ComService/PduR/PduR.c \
		Bsw/Service/ComService/PduR/PduR_Cfg.c \
		Bsw/Service/ComService/Com/Com.c \
		Bsw/Service/ComService/Com/Com_Cfg.c \
		Bsw/Service/ComService/Dcm/Dcm.c \
		Bsw/Service/ComService/Dcm/Dcm_Cfg.c \
		Bsw/Service/CryptoService/Csm/Csm.c \
		Bsw/Service/CryptoService/Csm/Csm_Cfg.c \
		Bsw/Service/CryptoService/KeyM/KeyM.c \
		Bsw/Service/MemService/NvM.c \
		Bsw/Service/SystemService/Os/Os.c \
		Bsw/Service/SystemService/Os/AutosarOs.c \
		Bsw/Service/SystemService/Os/OsAlarm.c \
		Bsw/Service/SystemService/Os/OsArch.c \
		Bsw/Service/SystemService/Os/OsArch.S \
		Bsw/Service/SystemService/Os/OsCounter.c \
		Bsw/Service/SystemService/Os/OsSchedule.c \
		Bsw/Service/SystemService/Os/OsTask.c \
		Bsw/Service/SystemService/Os/OsResource.c \
		Bsw/Service/SystemService/Dem/Dem.c \
		Bsw/Service/SystemService/Dem/Dem_Cfg.c \
		Bsw/Service/SystemService/Det/Det.c \
		Rte/Rte_Diag.c \
		Rte/Rte_EngineStatus.c \
		Rte/Rte_VehicleCommand.c \
		App/Swc_EngineStatus/Swc_EngineStatus.c \
		App/Swc_Diag/Swc_Diag.c \
		App/Swc_VehicleCommand/Swc_VehicleCommand.c \

LDFLAGS = -T ./System/Linker/linker.ld -nostdlib -Wl,-Map=output.map
TARGET = firmware
BIN = $(TARGET).bin

all:
	$(CC) $(CFLAGS) $(IPATH) $(SRC) $(LDFLAGS) -o $(TARGET).elf -lc -lgcc
	arm-none-eabi-size $(TARGET).elf

flash:
	$(OBJCOPY) -O binary $(TARGET).elf $(BIN)
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program $(TARGET).elf verify reset exit"

clean:
	del /Q $(TARGET).elf $(TARGET).map $(TARGET).bin 