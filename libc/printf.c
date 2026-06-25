#include <kernel/tty.h>
#include <string.h>

#include <stdio.h>

void printf(const char* data, ...) 
{
	size_t size = strlen(data);
	for (size_t i = 0; i < size; i++) {
        switch (data[i]) {
            case '\n':
                handle_new_line();
                break;
            default:
                terminal_putchar(data[i]);
        }
	}
}
