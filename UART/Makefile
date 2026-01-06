/*
File:Makefile

Author:Kaan Acar
*/

CC= arm-none-eabi-gcc
MACH=cortex-m3
CFLAGS= -c -mcpu=$(MACH) -mthumb -mfloat-abi=soft -std=gnu11 -Wall -O0
LDFLAGS= -mcpu=$(MACH) -mthumb -mfloat-abi=soft  --specs=nano.specs -T stm32_ls.ld -Wl,-Map=final.map

all:main.o common_defines.o uart.o startup.o bare_metal_uart.elf

main.o: main.c
	$(CC) $(CFLAGS) -o $@ $^

common_defines.o: common_defines.c
	$(CC) $(CFLAGS) -o $@ $^

uart.o: uart.c
	$(CC) $(CFLAGS) -o $@ $^

startup.o: startup.c
	$(CC) $(CFLAGS) -o $@ $^

bare_metal_uart.elf: main.o common_defines.o uart.o startup.o
	$(CC) $(LDFLAGS) -o $@ $^
load:
	openocd \
	-f /usr/local/xpack-openocd-0.12.0-1/openocd/scripts/interface/stlink.cfg \
	-f /usr/local/xpack-openocd-0.12.0-1/openocd/scripts/target/stm32f1x.cfg \
	-c "program build/bare_metal_uart.elf verify reset exit"
