/*
 * pipe9.c
 * 
 * $ gcc -Wall -o pipe9 pipe9.c
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
	int fd[2], fd2[2];
	pipe(fd);
	pipe(fd2);
	if ( fork() ) {
		close(fd2[0]);
		close(fd[1]);
		char buffer[256];
		char *aOrdenar[3] = { "Juan\n", "Pedro\n", "Ana\n" };
		int i;
		for(i=0;i<3;i++) write(fd2[1],aOrdenar[i],strlen(aOrdenar[i]));
		close(fd2[1]);
		int n=0;
		while((n=read(fd[0],buffer,255))) {
			buffer[n]='\0';
			//printf("p:[%s]",buffer);
			printf("%s",buffer);
		}
		printf("padre: espero a fin de hijo\n");
		wait(0);
		close(fd[0]);
		close(fd[1]);
	} else {
		dup2(fd[1],STDOUT_FILENO); // stdout <=> fd[1]
		dup2(fd2[0],STDIN_FILENO); // stdin <=> fd[0]
		close(fd2[1]);
		close(fd[0]);
		printf("Hola Mundo! (antes de exec)\n");
		char *myargv[2] = { "sort",NULL };
		execvp(myargv[0],myargv);
		printf("Rayos! fallo en execvp()\n");
		exit(1);
	}
	printf("padre: fin\n");
	return 0;
}
