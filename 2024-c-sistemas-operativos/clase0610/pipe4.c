/*
 * pipe4.c
 * 
 * $ gcc -Wall -o pipe4 pipe4.c
 * 
 * Puedo usar un file descriptor 5 (x ejemplo, uno no usado en el programa)
 * y tambien funciona para redirigir 
 * el write graba mensaje en salida.txt
 * muestra en pantalla la cantidad de bytes grabados
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
	int fd = open("salida.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666);
	int fd2 = 5;
	dup2(fd, fd2); // fd2 => fd
	char *buf1 = "Hola Mundo!\n";
	int bw = write(fd2,buf1,strlen(buf1));
	//perror("error write ");
	printf("grabe %d bytes\n",bw);
	close(fd2);
	return 0;
}
