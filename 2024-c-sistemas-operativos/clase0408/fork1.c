/*
 * fork1.c
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
 * 
*/

#include <stdio.h> // Este encabezado proporciona las declaraciones para las funciones de entrada y salida estándar, como printf() y scanf().
#include <stdlib.h> // Este encabezado proporciona prototipos para funciones de gestión de memoria dinámica, como malloc() y free(), así como otras funciones y macros útiles. Si planeas usar funciones relacionadas con la gestión de memoria dinámica, necesitarás incluir este encabezado. POR ALGÚN MOTIVO, ESTE NO SE NECESARIO.
#include <sys/types.h> // Este encabezado define varios tipos de datos que se utilizan en llamadas al sistema. Algunos de los tipos de datos comunes definidos en este encabezado incluyen pid_t (para identificadores de proceso en sistemas UNIX), uid_t y gid_t (para identificadores de usuario y grupo, respectivamente), entre otros.
#include <unistd.h> // Este encabezado proporciona prototipos para funciones estándar de Unix, como fork(), exec(), getpid(), etc. Si tu programa realiza llamadas al sistema relacionadas con la administración de procesos, como la creación de nuevos procesos o la obtención del identificador de proceso actual, necesitarás incluir este encabezado.

int main(int argc, char **argv)
{
	pid_t pid = fork();
	printf("Hola! soy el proceso PID=%d, variable pid=%d\n",getpid(),pid);
	return 0;
}