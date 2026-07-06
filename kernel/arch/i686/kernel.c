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

#include <stdlib.h>

struct GDT {
	uint32_t offset;
	uint32_t base;
	uint32_t limit;
	uint8_t access_byte;
	uint8_t flags;
};

void maxfetch(struct utsname info) {
	char ascii_art[10][100];
	strcpy(ascii_art[0], " ▄███████████████▄ Kernel:       ");
	strcpy(ascii_art[1], "\n █████████████████ Hostname:     ");
	strcpy(ascii_art[2], "\n █████████████████ Release:      ");
	strcpy(ascii_art[3], "\n █████████████████ Architecture: ");
	strcpy(ascii_art[4], "\n █████████████████ Domain name:  ");
	strcpy(ascii_art[5], "\n █████████████████");
	strcpy(ascii_art[6], "\n ███  █   █  ██ ██");
	strcpy(ascii_art[7], "\n ███    █ █  ██ ██");
	strcpy(ascii_art[8], "\n ███ █  █ █     ██ Author/Porter: Max Prime");
	strcpy(ascii_art[9], "\n ▀███████████████▀ Build:  2026.07.03");
	
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

void encodeGdtEntry(uint8_t *target, struct GDT source)
{
    // Check the limit to make sure that it can be encoded
    if (source.limit > 0xFFFFF) {printf("GDT cannot encode limits larger than 0xFFFFF");}
    
    // Encode the limit
    target[0] = source.limit & 0xFF;
    target[1] = (source.limit >> 8) & 0xFF;
    target[6] = (source.limit >> 16) & 0x0F;
    
    // Encode the base
    target[2] = source.base & 0xFF;
    target[3] = (source.base >> 8) & 0xFF;
    target[4] = (source.base >> 16) & 0xFF;
    target[7] = (source.base >> 24) & 0xFF;
    
    // Encode the access byte
    target[5] = source.access_byte;
    
    // Encode the flags
    target[6] |= (source.flags << 4);
}

void gdt_setup(void) {
	
}

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

	printf("[MAIN] Hello, Max Unix World!\n%d%s", 1769, "\n");

	maxfetch(info);

	char buff[27] = "qwertyuiopasdfghjklzxcvbnm";
	char printer[27] = ".......!";
	memcpy(&printer, &buff, 5);
	printf(printer);

}