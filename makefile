CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -mcpu=cortex-m3 -mthumb -O0 -g -Wall

IPATH = -I. \
		-I./System/Drivers/CMSIS \
		-I./System/Drivers/Common \
		-I./Bsw/Mcal/IoDriver/Dio \
		-I./Bsw/Mcal/IoDriver/Port \
		-I./Bsw/Mcal/IoDriver/Pwm \
		-I./Bsw/Mcal/IoDriver/Icu \
		-I./Bsw/Mcal/IoDriver \
		-I./Bsw/Mcal/McuDriver/Mcu \
		-I./Bsw/Mcal/ComDriver/Can \
		-I./Bsw/Mcal/ComDriver/Lin \
		-I./Bsw/EcuAbstraction/IoHwAb \
		-I./Bsw/EcuAbstraction/ComHwAb/CanIf \
		-I./Bsw/EcuAbstraction/ComHwAb/LinIf \
		-I./Bsw/Service/ComService/PduR \
		-I./Bsw/Service/ComService/Com \
		-I./Bsw/Service/SystemService/Os \
		-I./Rte \
		-I./App/Swc_GasControl \
		-I./App/Swc_DiagError \
		-I./App/Swc_ElectricDoorControl \
		-I./App/Swc_PedalControl \
		-I./Bsw/Service/SystemService/Dem \
		-I./Bsw/Service/SystemService/Det \

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
		Bsw/EcuAbstraction/IoHwAb/IoHwAb.c \
		Bsw/EcuAbstraction/IoHwAb/IoHwAb_Cfg.c \
		Bsw/EcuAbstraction/ComHwAb/CanIf/CanIf.c \
		Bsw/EcuAbstraction/ComHwAb/CanIf/CanIf_Cfg.c \
		Bsw/EcuAbstraction/ComHwAb/CanIf/CanTp.c \
		Bsw/EcuAbstraction/ComHwAb/LinIf/LinIf.c \
		Bsw/EcuAbstraction/ComHwAb/LinIf/LinIf_Cfg.c \
		Bsw/EcuAbstraction/ComHwAb/LinIf/LinTp.c \
		Bsw/Service/ComService/PduR/PduR.c \
		Bsw/Service/ComService/PduR/PduR_Cfg.c \
		Bsw/Service/ComService/Com/Com.c \
		Bsw/Service/ComService/Com/Com_Cfg.c \
		Bsw/Service/SystemService/Os/Os.c \
		Bsw/Service/SystemService/Dem/Dem.c \
		Bsw/Service/SystemService/Dem/Dem_Cfg.c \
		Bsw/Service/SystemService/Det/Det.c \
		Rte/Rte.c \
		App/Swc_GasControl/Swc_GasControl.c \
		App/Swc_DiagError/Swc_DiagError.c \
		App/Swc_ElectricDoorControl/Swc_ElectricDoorControl.c \
		App/Swc_PedalControl/Swc_PedalControl.c \

		

LDFLAGS = -T ./System/Linker/linker.ld -nostdlib -Wl,-Map=output.map
TARGET = firmware
BIN = $(TARGET).bin

all:
	$(CC) $(CFLAGS) $(IPATH) $(SRC) $(LDFLAGS) -o $(TARGET).elf

flash:
	$(OBJCOPY) -O binary $(TARGET).elf $(BIN)
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program $(TARGET).elf verify reset exit"

clean:
	del /Q $(TARGET).elf $(TARGET).map $(TARGET).bin 