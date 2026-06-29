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

#include <stdio.h>

void serial_printf(const char* data, ...) 
{
	size_t size = strlen(data);
	for (size_t i = 0; i < size; i++) {
        outb(PORT, data[i]);
	}
}

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
    serial_printf(data);
}
