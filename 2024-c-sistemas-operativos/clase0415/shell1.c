/*
 * shell1.c
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
 * shell primitivo en foreground
 * no soporta argumentos en los comandos
*/

#include <stdio.h>
#include <stdlib.h> // POR ALGÚN MOTIVO, ESTE NO SE NECESARIO.
#include <unistd.h>
#include <string.h> // Este encabezado proporciona declaraciones de funciones y macros relacionadas con manipulación de cadenas (strings). Algunas de las funciones más comunes incluyen: strcpy(), strncopy(), strcat(), strncat(), strlen(), strcmp(), strncmp(), strstr(), strchr(), strrchr()
#include <sys/types.h>
#include <sys/wait.h>

#define LOOP_JROMER 1
#define LOOP_GRCHERE strcmp(comando,"fin") != 0

int main(int argc, char **argv)
{
	char comando[256];
	do {
		printf("$$>");
		fgets(comando,256,stdin);
		comando[strlen(comando)-1]='\0';
		if ( strcmp(comando,"fin") != 0 ) {
			// es un comando a ejecutar!
			pid_t pid = fork();
			if ( pid == 0 ) {
				// proceso hijo
				// exec
				int rc = execlp(comando,comando,NULL);
				printf("comando [%s] no existe!!\n",comando);
				exit(rc);
			} else {
				// proceso padre, shell
				int estado=0;
				pid_t pid_hijo = wait(&estado);
				printf("PID %d finalizado con retorno %d\n",pid_hijo,estado/256);
			}
		}
	} while(LOOP_GRCHERE);
	return 0;
}