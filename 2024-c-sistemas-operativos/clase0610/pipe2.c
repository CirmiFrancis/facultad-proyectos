/*
 * pipe2.c
 * 
 * $ gcc -Wall -o pipe2 pipe2.c
 * se redirige el error standard a salida.txt
 * printf() funciona como siempre
 * perror() y fprintf(stderr,.. ) van a salida.txt
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
	dup2(fd, STDERR_FILENO);
	printf("Hola Mundo!\n"); // esto sale en pantalla
	perror("Esto es un error!");
	fprintf(stderr,"Rayos, esto tambien es un error!!\n");
	close(fd);
	return 0;
}
