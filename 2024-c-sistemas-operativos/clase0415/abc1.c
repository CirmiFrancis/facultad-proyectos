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
 * padre e hijo graban un abecedario en mayusculas
 * 
 * compilar:
 * $ gcc -Wall -o abc1 abc1.c
*/

#include <stdio.h>
#include <stdlib.h> // POR ALGÚN MOTIVO, ESTE NO ES NECESARIO.
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h> // Este encabezado proporciona declaraciones de funciones y tipos de datos para la obtención de información sobre archivos, como los permisos de archivos, el tamaño, la marca de tiempo, etc. Por ejemplo, la estructura struct stat se define en este encabezado y se utiliza para almacenar información sobre un archivo después de llamar a la función stat(). POR ALGÚN MOTIVO, ESTE NO ES NECESARIO.
#include <fcntl.h> // Este encabezado proporciona constantes y macros utilizadas para la manipulación de descriptores de archivo y el control de apertura de archivos. Por ejemplo, O_RDONLY, O_WRONLY, O_RDWR son constantes utilizadas para especificar los modos de apertura de archivos (lectura, escritura, lectura/escritura).

int main(int argc, char **argv)
{
	int fd = open("abecedario", O_TRUNC | O_CREAT | O_WRONLY, 0777);
	char letra = 'A';
	pid_t pid = fork();
	// Son 2 procesos, por lo que se ejecutara 2 veces
	// Primero: el proceso padre irá a la segunda condición, y segundo: el proceso hijo irá a la primera condición porque pid = 0
	if ( pid == 0 ) {
		// proceso hijo
		// escribir un abecedario
		while(letra <= 'Z') {
			write(fd, &letra, 1);
			letra++;
		}
	} 
	else {
		// proceso padre
		// escribir un abecedario
		while(letra <= 'Z') {
			write(fd, &letra, 1);
			letra++;
		}
		// para separar el resultado de ambos procesos
		write(fd, "\n", 1);
	}
	close(fd);
	return 0;
}

// Dentro de la variable entera, se abre el archivo llamado 'abecedario'
// Hay 3 argumentos/banderas (flags) que indican el modo de apertura del archivo: 
// - 'O_TRUNC' para truncarlo a longitud cero (eliminar el contenido), si el archivo existe
// - 'O_CREAT' para crear el archivo, en caso de no existir
// - 'O_WRONLY' para abrir el archivo en modo solo-escritura (se ejecuta indirectamente con la llamada a open())
// '0777' es el modo de permisos para el nuevo archivo creado. En este caso otorga permisos de lectura, escritura y ejecución para el propietario, el grupo y otros usuarios
// Se crea una variable char llamada 'letra' donde se guarda 'A', y una variable pid_t llamada 'pid' donde se guarda el pid del proceso hijo
// Se utiliza un if-else, donde:
// - En el proceso hijo (cuando pid == 0), se escribe el alfabeto en mayúsculas en el archivo 'abecedario' usando un bucle while.Cada letra se escribe en el archivo utilizando la función write(), donde 'fd' identifica el archivo en el que se van a escribir los datos, '&letra' es la dirección de memoria de la variable 'letra' y '1' es el número de bytes que se van a escribir en el archivo
// - En el proceso padre (cuando pid != 0), también se escribe el alfabeto en mayúsculas en el archivo 'abecedario' utilizando un bucle while similar al del proceso hijo
// Finalmente, se cierra el descriptor de archivo fd con la función close() y se devuelve 0