BUILD_DATE := $(shell date +"%a, %d %b %Y %T %z")

CC = i686-elf-gcc
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra -fexec-charset=CP437 -DCOMPILE_TIME="\"$(BUILD_DATE)\""

AS = i686-elf-as
ASFLAGS=

LFLAGS=-ffreestanding -O2 -nostdlib -lgcc

INCLUDE_DIR = include
LIBC_INCLUDE_DIR = include/libc
OUTPUT_DIR  = build

all: $(OUTPUT_DIR)/maxunix-kernel.bin

SRCS = \
	kernel/arch/i686/kernel.c \
	kernel/arch/i686/tty.c \
	kernel/arch/i686/serial.c \
	libc/utsname.c \
	libc/memcpy.c \
	libc/memset.c \
	libc/strlen.c \
	libc/strcpy.c \
	libc/strcat.c \
	libc/printf.c \
	libc/itoa.c

OBJS = $(patsubst %.c, $(OUTPUT_DIR)/%.o, $(SRCS))

BOOT_OBJ=$(OUTPUT_DIR)/boot.o

$(OUTPUT_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(LIBC_INCLUDE_DIR) -c $< -o $@ 

$(BOOT_OBJ): kernel/boot.s
	$(AS) $< -o $@ $(ASFLAGS)

$(OUTPUT_DIR)/maxunix-kernel.bin: $(OBJS) $(BOOT_OBJ)
	$(CC) -T kernel/linker.ld $(LFLAGS) -o $@ $^

qemu:
	qemu-system-i386 -kernel $(OUTPUT_DIR)/maxunix-kernel.bin -serial stdio

iso:
	cp $(OUTPUT_DIR)/maxunix-kernel.bin isodir/boot/maxunix-kernel.bin
	grub-mkrescue -o maxunix.iso isodir
	qemu-system-x86_64 -cdrom maxunix.iso -serial stdio

clean:
	rm -rf build/*