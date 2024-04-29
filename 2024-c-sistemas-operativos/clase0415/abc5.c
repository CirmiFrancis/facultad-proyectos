/*
 * abc1.c
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
	// creo archivo
	int fd = open("abecedario",O_TRUNC|O_CREAT,0777);
	close(fd);
	
	char letra = 'A',letra_hijo = 'b';
	pid_t pid = fork();
	if ( pid == 0 ) {
		// proceso hijo
		fd = open("abecedario",O_RDWR,0777);
		long posicion = 1L;
		// escribir un abecedario
		while(letra_hijo <= 'z') {
			lseek(fd,posicion,SEEK_SET);
			write(fd,&letra_hijo,1);
			letra_hijo+=2; // letra_hijo = letra_hijo + 2;
			posicion+=2;
		}
	} else {
		// proceso padre
		fd = open("abecedario",O_RDWR,0777);
		long posicion = 0L;
		// escribir un abecedario
		while(letra <= 'Z') {
			lseek(fd,posicion,SEEK_SET);
			write(fd,&letra,1);
			letra+=2;
			posicion+=2;
		}
	}
	close(fd);
	return 0;
}