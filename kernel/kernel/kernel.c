#include "../include/kernel/tty.h"

void kernel_main(void) 
{
	terminal_initialize();

	kprintf("Hello, Max Unix World! %d", 9);
}