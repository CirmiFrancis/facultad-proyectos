/*
 * abc4.c
 * 
 * padre graba abcedario en mayusculas
 * hijo graba un abcedario en minusculas
 * solo se graba 1 abecedario
 * mal sincronizado con sleep
 * solucion no aceptable
 * 
 * compilar:
 * $ gcc -Wall -o abc1 abc1.c
 * 
*/

#include <stdio.h>
#include <stdlib.h> // POR ALGÚN MOTIVO, ESTE NO SE NECESARIO.
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h> // POR ALGÚN MOTIVO, ESTE NO SE NECESARIO.
#include <fcntl.h>

int main(int argc, char **argv)
{
	int fd = open("abecedario",O_TRUNC|O_CREAT|O_WRONLY,0777);
	char letra = 'A',letra_hijo = 'b';
	pid_t pid = fork();
	if ( pid == 0 ) {
		// proceso hijo
		// escribir un abecedario
		sleep(1);
		while(letra_hijo <= 'z') {
			write(fd,&letra_hijo,1);
			letra_hijo+=2; // letra_hijo = letra_hijo + 2;
			sleep(1);
		}
	} else {
		// proceso padre
		// escribir un abecedario
		while(letra <= 'Z') {
			write(fd,&letra,1);
			sleep(1);
			letra+=2;
		}
	}
	close(fd);
	return 0;
}