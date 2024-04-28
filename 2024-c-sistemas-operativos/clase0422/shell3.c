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
 * soporta argumentos en los comandos y cualquier cantidad de espacios
 * intermedios entre los argumentos del comando
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LOOP_JROMER 1
#define LOOP_GRCHERE strcmp(comando,"fin") != 0

int main(int argc, char **args)
{
	char comando[256];
	do {
		printf("$$>");
		fgets(comando,256,stdin);
		comando[strlen(comando)-1]='\0'; // reemplaza \n por \0
		
		int i,ii=0,z=0,w;
		i=0;
		char *argv[256];
		memset(argv,0,sizeof(char *)*256);
		//for(w=0;w<256;w++) argv[w]=NULL;

		// salteo los espacios que separan a los argumentos del comando
		while(comando[i] && comando[i] == ' ') i++;
		do {
			char palabra[256];
			ii=0;
			while(comando[i] && comando[i] != ' ' && ii < 256) {
				palabra[ii] = comando[i];
				i++;ii++;
			}
			palabra[ii]='\0';
			argv[z] = strdup(palabra);
			z++;
			// salteo los espacios que separan a los argumentos del comando
			while(comando[i] && comando[i] == ' ') i++;
		} while(comando[i] && z < 255);
		argv[z] = NULL;
		
		// trace, chequeo que funciona el parsing
		for(w=0;w<256 && argv[w];w++) printf("argv[%d]=[%s]\n",w,argv[w]);
		
		//si no hay comando, vuelvo al prompt
		if ( strcmp(argv[0],"") == 0 ) continue; // presiono ENTER
		
		if ( strcmp(argv[0],"cd") == 0 ) { // comando interno cd
			if ( argv[1] == NULL ) {
				printf("debe indicar directorio!\n");
				continue;
			}
			chdir(argv[1]);
		} else if ( strcmp(comando,"fin") != 0 ) {
			// es un comando a ejecutar!
			pid_t pid = fork();
			if ( pid == 0 ) {
				// proceso hijo
				// exec
				
				int rc = execvp(argv[0],argv);
				printf("comando [%s] no existe!!\n",comando);

				// libero la memoria solicitada por strdup()
				for(w=0;w<256 && argv[w];w++) free(argv[w]);
				exit(rc);

			} else {
				// proceso padre, shell
				int estado=0;
				pid_t pid_hijo = wait(&estado);
				printf("PID %d finalizado con retorno %d\n",pid_hijo,estado/256);

				// libero la memoria solicitada por strdup()
				for(w=0;w<256 && argv[w];w++) free(argv[w]);

			}
		}
	} while(LOOP_GRCHERE);
	return 0;
}

