CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CPU = cortex-m3
CFLAGS = -mcpu=$(CPU) -mthumb -std=gnu99 -Wall -O0

SRCDIR = Core/source Drivers/source Example/source
INCDIR = Core/include Drivers/include Example/include
STARTUPDIR = Startup
LINKERDIR = Linker
BUILDDIR = build

LDSCRIPT = $(LINKERDIR)/stm32_linker.ld

SRCS = $(wildcard $(addsuffix /*.c, $(SRCDIR))) \
       $(STARTUPDIR)/startup_stm32f103rbt6.s

OBJS = $(patsubst %.c, $(BUILDDIR)/%.o, $(notdir $(filter %.c, $(SRCS)))) \
       $(patsubst %.s, $(BUILDDIR)/%.o, $(notdir $(filter %.s, $(SRCS))))

all: $(BUILDDIR)/firmware.elf $(BUILDDIR)/firmware.bin

$(BUILDDIR)/%.o:
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(foreach dir, $(INCDIR), -I$(dir)) -c $(firstword $(wildcard $(addsuffix /$*.c, $(SRCDIR))) ) -o $@

$(BUILDDIR)/startup_stm32f103rbt6.o: $(STARTUPDIR)/startup_stm32f103rbt6.s
	mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/firmware.elf: $(OBJS)
	$(CC) $(CFLAGS) -T $(LDSCRIPT) $^ -o $@

$(BUILDDIR)/firmware.bin: $(BUILDDIR)/firmware.elf
	$(OBJCOPY) -O binary $< $@

clean:
	rm -rf $(BUILDDIR)

.PHONY: all clean
