/*
 * abc2.c
 *
 * padre graba abcedario en mayusculas
 * hijo graba un abcedario en minusculas
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
	char letra = 'A',letra_hijo = 'a';
	pid_t pid = fork();
	if ( pid == 0 ) {
		// proceso hijo
		// escribir un abecedario
		while(letra_hijo <= 'z') {
			write(fd,&letra_hijo,1);
			letra_hijo++;
		}
	} else {
		// proceso padre
		// escribir un abecedario
		while(letra <= 'Z') {
			write(fd,&letra,1);
			letra++;
		}
	}
	close(fd);
	return 0;
}