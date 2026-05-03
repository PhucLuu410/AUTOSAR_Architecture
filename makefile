CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -mcpu=cortex-m3 -mthumb -O0 -g -Wall

IPATH = -I. \
		-I./Bsw/Mcal/IoDriver/DIO \
		-I./System/Drivers/CMSIS \
		-I./System/Drivers/Common \
		-I./Bsw/Mcal/IoDriver/PORT \
		-I./Bsw/Mcal/IoDriver/PWM \
		-I./Bsw/Mcal/IoDriver \
		-I./Bsw/Mcal/McuDriver/Mcu \
		-I./Bsw/Mcal/ComDriver/Can \
		-I./Bsw/SystemService \
		-I./Bsw/EcuAbstraction/IoHwAb \

SRC = 	./System/Startup/startup.c \
		App/main.c \
		Bsw/Mcal/IoDriver/DIO/Dio.c  \
		Bsw/Mcal/IoDriver/DIO/Dio_Cfg.c \
		Bsw/Mcal/IoDriver/PORT/Port.c \
		Bsw/Mcal/IoDriver/PORT/Port_Cfg.c \
		Bsw/Mcal/IoDriver/PWM/Pwm.c \
		Bsw/Mcal/IoDriver/PWM/Pwm_Cfg.c \
		Bsw/Mcal/IoDriver/ADC/Adc.c \
		Bsw/Mcal/IoDriver/ADC/Adc_Cfg.c \
		Bsw/Mcal/McuDriver/Mcu/Mcu.c \
		Bsw/Mcal/McuDriver/Mcu/Mcu_Cfg.c \
		Bsw/Mcal/ComDriver/Can/Can.c \
		Bsw/Mcal/ComDriver/Can/Can_Cfg.c \
		Bsw/SystemService/Os_Isr.c \
		Bsw/SystemService/Os.c \
		Bsw/EcuAbstraction/IoHwAb/IoHwAb.c \
		Bsw/EcuAbstraction/IoHwAb/IoHwAb_Cfg.c \
		

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