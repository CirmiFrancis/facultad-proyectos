/*
 * pipe7.c
 * 
 * $ gcc -Wall -o pipe7 pipe7.c
 * 
 * Funciona la redireccion en el hijo, a pesar del exec()
 * No se graba el printf() antes de exec
 * Si se graba write() antes de exec
 * La salida del comando ejecutado por execvp() va a salida.txt
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
	dup2(fd,STDOUT_FILENO); // stdout <=> fd
	if ( fork() ) {
		printf("padre: espero a fin de hijo\n");
		wait(0);
	} else {
		printf("Hola Mundo! (antes de exec)\n");
		/*
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		write(1,"Hola Mundo! (antes de exec)\n",strlen("Hola Mundo! (antes de exec)\n"));
		*/
		//sleep(20);
		char *myargv[3] = { "ls","-l",NULL };
		execvp(myargv[0],myargv);
		printf("Rayos! fallo en execvp()\n");
		exit(1);
	}
	close(fd);
	printf("padre: fin\n");
	return 0;
}
