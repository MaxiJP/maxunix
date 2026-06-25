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

#ifndef _SERIAL_H
#define _SERIAL_H

#include <stdint.h>

#define PORT 0x3f8

void outb (uint16_t _port, uint8_t _data);
uint8_t inb (uint16_t _port);
int init_serial(void);

#endif