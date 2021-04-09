PREFIX=arm-linux-gnueabihf-
CC=$(PREFIX)gcc
LD=$(PREFIX)ld
AR=$(PREFIX)ar
OBJCOPY=$(PREFIX)objcopy
OBJDUMP=$(PREFIX)objdump

VPATH = ./uart:./led:./obj

OBJS := start.o \
		main.o \
		led/led.o \
		uart/my_printf.o \
		uart/string_utils.o \
		uart/uart.o

INCLUEDS = -I./include
TARGET  = boot

CFLAGS 		:= -Wall -O2
CPPFLAGS   	:= -nostdinc -nostdlib -fno-builtin

default: all pack

all: $(TARGET).bin

$(TARGET).bin: $(OBJS)
	$(LD) -I./obj $^ -T imx6ull.lds -g -o $(TARGET).elf -lgcc -L/opt/gcc-linaro-6.2.1-2016.11-x86_64_arm-linux-gnueabihf/lib/gcc/arm-linux-gnueabihf/6.2.1
	$(OBJCOPY) -O binary -S $(TARGET).elf $(TARGET).bin
	$(OBJDUMP) -D -m arm  $(TARGET).elf > $(TARGET).dis

%.o: %.c
	$(CC) $(INCLUEDS) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

%.o:%.S
	${CC} $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

pack:
	./tools/mkimage -n ./tools/imximage.cfg.cfgtmp -T imximage -e 0x80100000 -d $(TARGET).bin $(TARGET).imx
	dd if=/dev/zero of=header_zero.bin bs=1024 count=1
	cat header_zero.bin $(TARGET).imx > $(TARGET).img
	sz $(TARGET).imx
clean:
	rm *.dis  *.bin *.elf *.imx *.img *.o ./led/*.o ./uart/*.o -f
