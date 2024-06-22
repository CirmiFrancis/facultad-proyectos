/*
 * pipe6.c
 * 
 * $ gcc -Wall -o pipe6 pipe6.c
 * 
 * El proceso hijo hereda dup2() del padre, existen los file descriptors 
 * del padre en proceso hijo y tambien funciona la redireccion
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
	int fd = open("salida.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666);
	dup2(fd,5); // 5 => fd
	if ( fork() ) {
		printf("padre: espero a fin de hijo\n");
		wait(0);
	} else {
		char *buf1 = "Hola Mundo!\n";
		int bw = write(5,buf1,strlen(buf1));
		//perror("error write ");
		printf("hijo:grabe %d bytes\n",bw);
		exit(0);
	}
	close(5);
	printf("padre: fin\n");
	return 0;
}
