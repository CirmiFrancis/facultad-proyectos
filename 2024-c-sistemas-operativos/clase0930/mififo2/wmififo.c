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
	printf("main(%s): voy a abrir ./mififo1 ./mififo2\n",argv[0]);
	int fd1 = open("mififo1",O_WRONLY); // longitud de mensajes
	int fd2 = open("mififo2",O_WRONLY); // mensajes
	printf("main(%s):  abri ./mififo1 fd=%d ./mififo2 fd2=%d\n",argv[0],fd1,fd2);
	char buffer[100];
	int i;
	for(i=0;i<50;i++) {
		snprintf(buffer,100,"Hola Mundo!#%d",i);
		printf("main(%s): voy a grabar en ./mififo1\n",argv[0]);
		int largo = strlen(buffer)+1;
		int n1 = write(fd1,&largo,sizeof(int));
		printf("main(%s): voy a grabar en ./mififo2\n",argv[0]);
		int n2 = write(fd2,buffer,strlen(buffer)+1);
		printf("main(%s): grabe %d bytes [%s] en ./mififo2, %d bytes en ./mififo1\n",argv[0],n2,buffer,n1);
	}
	close(fd1);
	close(fd2);
	return 0;
}

