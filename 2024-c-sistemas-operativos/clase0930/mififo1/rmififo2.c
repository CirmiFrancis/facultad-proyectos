/*
 * rmififo2.c
 * 
 * Copyright 2024 osboxes <osboxes@osboxes>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * Simple lector en ./mififo
 * Previamente crear ./mififo con $ mkfifo mififo
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char **argv)
{
	printf("main(%s): voy a abrir ./mififo de lectura\n",argv[0]);
	int fd = open("mififo",O_RDONLY);
	printf("main(%s):  abri ./mififo fd=%d de lectura\n",argv[0],fd);
	char buffer[100];
	memset(buffer,0,100); // buffer=0
	int n=0;
	do {
		printf("main(%s): voy a leer de ./mififo\n",argv[0]);
		n = read(fd,buffer,100);
		printf("main(%s): lei %d bytes [%s] de ./mififo\n",argv[0],n,buffer);
	} while(n > 0);
	close(fd);
	return 0;
}

