/*
 * procA.c
 * 
 * $ gcc -Wall -o procA procA.c myshm.c -I .
 * 
 * proceso A imprime letras mayusculas
 * usa api semaforos System V
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <myshm.h>

int main(int argc, char **argv)
{
	// obtengo semid de semaforos SVR4 con clave 0xA previamente creado
	int semid = semget(0xA,0,0);
		
	char letra='A';
	while(letra <= 'Z') {
		semWait(semid,0); // semaforo 0 -> semA
			printf("%c\n",letra);
			sleep(1);
		semSignal(semid,1); // semaforo 1 -> semB
		letra+=2;
	}
	return 0;
}