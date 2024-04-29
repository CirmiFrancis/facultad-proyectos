/*
 * abc1.c
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
 * padre e hijo graban un abcedario en mayusculas
 * 
 * compilar:
 * $ gcc -Wall -o abc1 abc1.c
 * 
*/

#include <stdio.h>
#include <stdlib.h> // POR ALGÚN MOTIVO, ESTE NO SE NECESARIO.
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h> // Este encabezado proporciona declaraciones de funciones y tipos de datos para la obtención de información sobre archivos, como los permisos de archivos, el tamaño, la marca de tiempo, etc. Por ejemplo, la estructura struct stat se define en este encabezado y se utiliza para almacenar información sobre un archivo después de llamar a la función stat(). POR ALGÚN MOTIVO, ESTE NO SE NECESARIO.
#include <fcntl.h> // Este encabezado proporciona constantes y macros utilizadas para la manipulación de descriptores de archivo y el control de apertura de archivos. Por ejemplo, O_RDONLY, O_WRONLY, O_RDWR son constantes utilizadas para especificar los modos de apertura de archivos (lectura, escritura, lectura/escritura).

int main(int argc, char **argv)
{
	int fd = open("abecedario",O_TRUNC|O_CREAT|O_WRONLY,0777);
	char letra = 'A';
	pid_t pid = fork();
	if ( pid == 0 ) {
		// proceso hijo
		// escribir un abecedario
		while(letra <= 'Z') {
			write(fd,&letra,1);
			letra++;
		}
	} else {
		// proceso padre
		// escribir un abecedario
		while(letra <= 'Z') {
			write(fd,&letra,1);
			letra++;
		}
	}
	close(fd);
	return 0;
}