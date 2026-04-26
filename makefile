CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -mcpu=cortex-m3 -mthumb -O0 -g -Wall

IPATH = -I. \
		-I./Bsw/MCAL/IODriver/DIO \
		-I./SYSTEM/Drivers/CMSIS \
		-I./SYSTEM/Drivers/Common \
		-I./Bsw/MCAL/IODriver/PORT \
		-I./Bsw/MCAL/IODriver/PWM \
		-I./Bsw/MCAL/IODriver \
		-I./Bsw/MCAL/MCU \
		-I./Bsw/SystemService \
		-I./Bsw/ECUAbstraction/IoHwAb \

SRC = 	./SYSTEM/Startup/startup.c \
		App/main.c \
		Bsw/MCAL/IODriver/DIO/Dio.c  \
		Bsw/MCAL/IODriver/PORT/Port.c \
		Bsw/MCAL/IODriver/PWM/Pwm.c \
		Bsw/MCAL/IODriver/ADC/Adc.c \
		Bsw/MCAL/MCU/Mcu.c \
		Bsw/SystemService/Os_Isr.c \
		Bsw/SystemService/Os.c \
		Bsw/ECUAbstraction/IoHwAb/IoHwAb.c

LDFLAGS = -T ./SYSTEM/Linker/linker.ld -nostdlib -Wl,-Map=output.map
TARGET = firmware
BIN = $(TARGET).bin

all:
	$(CC) $(CFLAGS) $(IPATH) $(SRC) $(LDFLAGS) -o $(TARGET).elf

flash:
	$(OBJCOPY) -O binary $(TARGET).elf $(BIN)
	openocd -f interface/stlink.cfg -f target/stm32f1x.cfg -c "program $(TARGET).elf verify reset exit"

clean:
	del /Q $(TARGET).elf $(TARGET).map $(TARGET).bin 