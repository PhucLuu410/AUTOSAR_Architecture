CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
CFLAGS = -mcpu=cortex-m3 -mthumb -O0 -g -Wall
IPATH = -I. -I./3_BSW/MCAL/IODriver/DIO -I./SYSTEM/Drivers/CMSIS -I./SYSTEM/Drivers/Common -I./3_BSW/MCAL/IODriver/PORT -I./3_BSW/MCAL/IODriver/PWM -I./3_BSW/MCAL/IODriver -I./3_BSW/MCAL/MCU
SRC = main.c 3_BSW/MCAL/IODriver/DIO/Dio.c ./SYSTEM/Startup/startup.c 3_BSW/MCAL/IODriver/PORT/Port.c 3_BSW/MCAL/IODriver/PWM/Pwm.c 3_BSW/MCAL/IODriver/ADC/Adc.c 3_BSW/MCAL/MCU/Mcu.c
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