/*
 * shell2.c
 * 
 * shell primitivo en foreground
 * soporta argumentos en los comandos y cualquier cantidad de espacios
 * intermedios entre los argumentos del comando
*/

#include <stdio.h>
#include <stdlib.h> // POR ALGÚN MOTIVO, ESTE NO ES NECESARIO.
#include <unistd.h>
#include <string.h>
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
				int i,ii=0,z=0,w;
				i=0;
				char *argv[256];
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
				//for(w=0;w<256 && argv[w];w++) printf("argv[%d]=[%s]\n",w,argv[w]);
				
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
			}
		}
	} while(LOOP_GRCHERE);
	return 0;
}