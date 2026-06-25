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
#include <stdio.h>
#include <stdint.h>

void kernel_early_main(void) {
	printf("[EARLY MAIN] Max Unix early kernel...\n");

	terminal_initialize();

	if (init_serial()==1) {
		printf("[EARLY MAIN] Serial failure.\n");
	} else {
		printf("[EARLY MAIN] Serial success.\n");
	}
}

void kernel_main(void) {

	printf("[MAIN] Hello, Max Unix World!\n17");
	
}