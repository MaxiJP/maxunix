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

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "../kernel/vga.h"

#define VGA_MEMORY  0xB8000 

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer = (uint16_t*)VGA_MEMORY;

size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = 0b00001001; // first 4 bits are for the background color (SRGB), last 4 bits for foreground color (SRGB)

	for (size_t y = 0; y < VGA_HEIGHT; y++) {
			for (size_t x = 0; x < VGA_WIDTH; x++) {
					const size_t index = y * VGA_WIDTH + x;
					terminal_buffer[index] = vga_entry(' ', terminal_color);
			}
	}
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
	    const size_t index = y * VGA_WIDTH + x;
    	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) 
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
				terminal_row = 0;
	}
}

void terminal_write(const char* data, size_t size) 
{
	for (size_t i = 0; i < size; i++)
			terminal_putchar(data[i]);
}

void kprintf(const char* data) 
{
	terminal_write(data, strlen(data));
}