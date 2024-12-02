/*
 * rmififo.c
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
 * Mejoramos el parsing de los mensajes que envia el escritor
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
	printf("main(%s): voy a abrir ./mififo1 ./mififo2 de lectura\n",argv[0]);
	int fd1 = open("mififo1",O_RDONLY);
	int fd2 = open("mififo2",O_RDONLY);
	printf("main(%s):  abri ./mififo1 fd=%d, ./mififo2 fd=%d de lectura\n",argv[0],fd1,fd2);
	int n1=0,n2=0,largo;
	char buffer[100];
	memset(buffer,0,100);
	do {
		printf("main(%s): voy a leer de ./mififo1\n",argv[0]);
		n1 = read(fd1,&largo,sizeof(int));
		if ( n1 > 0 ) {
			n2 = read(fd2,buffer,largo);
			if ( n2 > 0 ) {
				printf("main(%s): lei %d bytes [%s] de ./mififo2 y %d bytes de ./mififo1\n",argv[0],n2,buffer,n1);
			}
		}
	} while(n1 > 0 && n2 > 0);
	close(fd1);
	close(fd2);
	return 0;
}

