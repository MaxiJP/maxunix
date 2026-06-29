/*
	This file is part of Max Unix.

	Max Unix is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Max Unix is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Max Unix.  If not, see <https://www.gnu.org/licenses/>.

	Copyright (c) Max Prime 2026. All rights reserved.
*/

#include <kernel/serial.h>
#include <kernel/tty.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

void serial_puts(const char data) 
{
    outb(PORT, data);
}

void printf(const char* data, ...) 
{
	int argsize = 0;
	size_t size = strlen(data);
	for (size_t i = 0; i < size; i++) {
        switch (data[i]) {
			case '%':
				++i;
				++argsize;
				break;
        }
	}

	va_list args;
	va_start(args, argsize);

	for (size_t j = 0; j < size; j++) {
        switch (data[j]) {
            case '\n':
                handle_new_line();
				serial_puts('\n');
                break;
			case '%':
				j++;
				switch (data[j]) {
					case '%':
						// its just a percent sign
						terminal_putchar('%');
						break;
					case 's':
						printf(va_arg(args, char*));
						break;
					case 'd':
						// its an integer, idfk man
						break;
				}
				break;
            default:
                terminal_putchar(data[j]);
				serial_puts(data[j]);
        }
	}

}


