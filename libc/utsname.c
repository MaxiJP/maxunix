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

#define NODENAME "maxunix"
#define SYSNAME "MaxUnix"
#define RELEASE "0.0.1"
#define VERSION "#1 MAXUNIXBUILD "
#define MACHINE "i686"
#define DOMAINNAME "(none)"

#include <sys/utsname.h>
#include <stdio.h>
#include <string.h>

void uname(struct utsname *info) {

	char local_version[1000] = VERSION;
	strcat(local_version, COMPILE_TIME);

    strcpy(info->nodename, NODENAME);
    strcpy(info->sysname, SYSNAME);
    strcpy(info->release, RELEASE);
    strcpy(info->version, local_version);
    strcpy(info->machine, MACHINE);
	strcpy(info->_domainname, DOMAINNAME);

}