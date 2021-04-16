PREFIX=arm-linux-gnueabihf-
CC=$(PREFIX)gcc
LD=$(PREFIX)ld
AR=$(PREFIX)ar
OBJCOPY=$(PREFIX)objcopy
OBJDUMP=$(PREFIX)objdump

VPATH = ./uart:./led:./obj:./clk:./mmc

OBJS := start.o \
		main.o \
		led/led.o \
		uart/my_printf.o \
		uart/string_utils.o \
		uart/uart.o \
		clk/clk.o \
		iomux/iomux-v3.o

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
	cat tools/header_zero_1K.bin $(TARGET).imx > $(TARGET).img
	sz $(TARGET).imx
clean:
	@find -type f -name "*.o" -exec rm -f {} \;
	@rm *.dis  *.bin *.elf *.imx *.img -f
