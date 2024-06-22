/*
 * pipe8.c
 * 
 * $ gcc -Wall -o pipe8 pipe8.c
 * 
 * Padre lector
 * Hijo escritor
 * utilizando pipe()
 * el padre imprime la salida del comando ejecutado por el proceso hijo
 * Hijo hace dup de stdout previo a execvp()
 * el stdout del hijo se redirige al extremo de escritura del pipe que
 * luego es leido por el padre
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
	int fd[2];
	pipe(fd);
	if ( fork() ) {
		close(fd[1]);
		char buffer[256];
		int n=0;
		while((n=read(fd[0],buffer,255))) {
			buffer[n]='\0';
			//printf("p:[%s]",buffer);
			printf("%s",buffer);
		}
		printf("padre: espero a fin de hijo\n");
		wait(0);
		close(fd[0]);
	} else {
		dup2(fd[1],STDOUT_FILENO); // stdout <=> fd[1]
		close(fd[0]);
		printf("Hola Mundo! (antes de exec)\n");
		char *myargv[3] = { "ls","-l",NULL };
		execvp(myargv[0],myargv);
		printf("Rayos! fallo en execvp()\n");
		exit(1);
	}
	printf("padre: fin\n");
	return 0;
}
