# Toolchain
CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

# MCU and flags
CPU = cortex-m3
CFLAGS = -mcpu=$(CPU) -mthumb -std=gnu99 -Wall -O0

# Directories
SRCDIR = Core/source
INCDIR = Core/include
STARTUPDIR = Startup
LINKERDIR = Linker
BUILDDIR = build

# Linker script path
LDSCRIPT = $(LINKERDIR)/stm32_linker.ld

# Sources - add your source files here, update paths for startup
SRCS = $(SRCDIR)/main.c $(SRCDIR)/syscalls.c $(SRCDIR)/sysmem.c $(STARTUPDIR)/startup_stm32f103rbt6.s

# Objects go directly into build/, remove directory paths for .o names
OBJS = $(patsubst %.c,$(BUILDDIR)/%.o,$(notdir $(filter %.c,$(SRCS)))) \
       $(patsubst %.s,$(BUILDDIR)/%.o,$(notdir $(filter %.s,$(SRCS))))

# Default target
all: $(BUILDDIR)/firmware.elf $(BUILDDIR)/firmware.bin

# Compile C files from SRCDIR to build/ flat
$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Compile ASM files from STARTUPDIR to build/ flat
$(BUILDDIR)/%.o: $(STARTUPDIR)/%.s
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Link
$(BUILDDIR)/firmware.elf: $(OBJS)
	$(CC) $(CFLAGS) -T $(LDSCRIPT) $^ -o $@

# ELF to bin
$(BUILDDIR)/firmware.bin: $(BUILDDIR)/firmware.elf
	$(OBJCOPY) -O binary $< $@

# Clean
clean:
	rm -rf $(BUILDDIR)

.PHONY: all clean
