/*
 * pipe3.c
 * 
 * $ gcc -Wall -o pipe3 pipe3.c
 * 
 * Anula stdout y stderr de la pantalla, no emite mensajes por pantalla
 * se graba primero stderr en archivo salida.txt y luego se graba stdout 
 * en salida.txt y ello no tiene nada que ver con el orden de las 
 * instrucciones dup2()
 * 
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
	dup2(fd, STDOUT_FILENO);
	printf("Hola Mundo!\n");
	perror("Esto es un error!");
	fprintf(stderr,"Rayos, esto tambien es un error!!\n");
	close(fd);
	return 0;
}
