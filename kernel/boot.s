/*

	This Max Unix file is credited to wiki.osdev.org. All copyright and rights are held by them.

	This file has been modified from the original source taken.

*/

.section .multiboot
.align 4
.long 0x1BADB002 // magic number
.long 0b00000011 // flags (?)
.long -(0x1BADB002 + 0b00000011) // checksum

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start
.type _start, @function

gdtr:
	.word 0 # For limit storage
    .long 0 # For base storage

setGdt:
	movw   4(%esp), %ax
	movw   %ax, gdtr
	movl   8(%esp), %eax
	movl   %eax, gdtr+2
	LGDT  [gdtr]
	RET

_start:
	cli

	call gdt_setup

	call kernel_early_main

	mov $stack_top, %esp

	call kernel_main

1:	hlt
	jmp 1b

.size _start, . - _start
