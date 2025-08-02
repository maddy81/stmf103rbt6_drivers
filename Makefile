CC=arm-none-eabi-gcc
MACH=cortex-m3
CFLAGS= -c -mcpu=$(MACH) -mthumb -std=gnu99

SRCDIR= Core/source
INCLUDEDIR=Core/include

main.o:$(SRCDIR)/main.c
	#$(CC) $(CFLAGS) main.c -o main.o
	$(CC) $(CFLAGS) $^ -o $@