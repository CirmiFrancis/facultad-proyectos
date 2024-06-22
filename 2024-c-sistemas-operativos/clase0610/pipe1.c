/*
 * pipe1.c
 * 
 * $ gcc -Wall -o pipe1 pipe1.c
 * 
 * La salida de printf() va a archivo salida.txt
 * stdout esta anulado, no funciona mas luego de dup2()
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
	//remove("salida.txt");
	int fd = open("salida.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666);
	dup2(fd, STDOUT_FILENO);
	printf("Hola Mundo!\n");
	printf("Hola Mundo Cruel!\n");
	close(fd);
	return 0;
}
