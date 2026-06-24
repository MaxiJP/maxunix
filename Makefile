all: kernel assembly link qemu

CC = i686-elf-gcc
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra

AS = i686-elf-as
ASFLAGS=

KERNEL_FILES=kernel/kernel

KERNEL_OUTPUT = build/maxunix-kernel.bin

kernel:
	$(CC) -c $(KERNEL_FILES)/kernel.c -o build/kernel.o $(CFLAGS)
	$(CC) -c kernel/arch/tty.c -o build/tty.o $(CFLAGS)

assembly:
	$(AS) $(KERNEL_FILES)/boot.s -o build/boot.o $(ASFLAGS)

link:
	$(CC) -T $(KERNEL_FILES)/linker.ld -o $(KERNEL_OUTPUT) -ffreestanding -O2 -nostdlib build/tty.o build/boot.o build/kernel.o -lgcc

qemu:
	qemu-system-i386 -kernel $(KERNEL_OUTPUT)

iso:
	cp $(KERNEL_OUTPUT) isodir/boot/maxunix-kernel.bin
	grub-mkrescue -o maxunix.iso isodir
	qemu-system-x86_64 -cdrom maxunix.iso

clean:
	rm build/*