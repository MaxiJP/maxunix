all: kernel link assembly

CC = i686-elf-gcc
AS = i686-elf-as

KERNEL_OUTPUT = maxunix-kernel.bin

kernel:
	$(CC) -c kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

link:
	$(CC) -T linker.ld -o $(KERNEL_OUTPUT) -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

assembly:
	$(AS) boot.s -o boot.o

qemu:
	qemu-system-i386 -kernel $(KERNEL_OUTPUT)