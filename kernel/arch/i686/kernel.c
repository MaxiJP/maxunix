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
#include <sys/utsname.h>
#include <kernel/tty.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

void kernel_early_main(void) {

	terminal_initialize();

	printf("[EARLY MAIN] Max Unix early kernel...\n");

	if (init_serial()==1) {
		printf("[EARLY MAIN] Serial failure.\n");
	} else {
		printf("[EARLY MAIN] Serial success.\n");
	}
}

void kernel_main(void) {

	struct utsname info;
	uname(&info);

	printf(strcat(info.sysname, "\n"));

	printf("[MAIN] Hello, Max Unix World!\n");

	char ascii_art[10][100];
	strcpy(ascii_art[0], " ▄███████████████▄ Kernel:       ");
	strcpy(ascii_art[1], " █████████████████ Hostname:     ");
	strcpy(ascii_art[2], "\n █████████████████ Release:      ");
	strcpy(ascii_art[3], "\n █████████████████ Architecture: ");
	strcpy(ascii_art[4], "\n █████████████████ Domain name:  ");
	strcpy(ascii_art[5], "\n █████████████████");
	strcpy(ascii_art[6], "\n ███  █  ⠀█⠀ ██ ██");
	strcpy(ascii_art[7], "\n ███    █⠀█⠀ ██ ██");
	strcpy(ascii_art[8], "\n ███ █  █⠀█     ██ Author: Max Prime");
	strcpy(ascii_art[9], "\n ▀███████████████▀ Build:  2026.05.04");
	
	char output[1000] = "";
	// generate the output that we should give to the terminal with all of the info
	strcat(ascii_art[0], info.sysname); // Linux
	strcat(ascii_art[1], info.nodename); // maxarch
	strcat(ascii_art[2], info.release); // 6.18.7-arch1-1
	strcat(ascii_art[3], info.machine); // x86_64
	strcat(ascii_art[4], info._domainname); // (none)
	strcat(output, "\n\nFull: ");
	strcat(output, info.sysname);
	strcat(output, " ");
	strcat(output, info.nodename);
	strcat(output, " ");
	strcat(output, info.release);
	strcat(output, " ");
	strcat(output, info.version);
	strcat(output, " ");
	strcat(output, info.machine);
	
	//print out the information
	printf("\n");
	for (int i=0;i<10;i++) {
		printf(ascii_art[i]);
	}
	printf("\n");
	printf("%s%s", output, "\n");

}