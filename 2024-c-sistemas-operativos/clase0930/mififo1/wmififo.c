/*
 * wmififo.c
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
 * Simple escritor en ./mififo
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
	printf("main(%s): voy a abrir ./mififo\n",argv[0]);
	int fd = open("mififo",O_WRONLY);
	printf("main(%s):  abri ./mififo fd=%d\n",argv[0],fd);
	char buffer[100];
	strcpy(buffer,"Hola Mundo!");
	printf("main(%s): voy a grabar en ./mififo\n",argv[0]);
	int n = write(fd,buffer,strlen(buffer)+1);
	printf("main(%s): grabe %d bytes [%s] en ./mififo\n",argv[0],n,buffer);
	printf("Presione Intro para terminar\n");
	fgets(buffer,100,stdin);
	close(fd);
	return 0;
}

