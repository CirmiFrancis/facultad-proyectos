/*
 * pipe10.c
 * 
 * $ gcc -Wall -o pipe10 pipe10.c
 * Comunicacion simple entre padre e hijo usando pipe
 * sin hacer dup2() 
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
	char buffer[256];
	if ( fork() ) {
		close(fd[1]);
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
		close(fd[0]);
		char *mensajes[4] = { "Hola\n","Mundo\n","Cruel\n","escrito por proceso hijo!\n" };
		int i;
		for(i=0;i<4;i++) write(fd[1],mensajes[i],strlen(mensajes[i]));
		close(fd[1]);
		exit(0);
	}
	printf("padre: fin\n");
	return 0;
}
