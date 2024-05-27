/*
 * procB.c
 * 
 * $ gcc -Wall -o procB procB.c myshm.c -I .
 * 
 * proceso B imprime letras minusculas
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
	
	char letra='b';
	while(letra <= 'z') {
		semWait(semid,1); // 1 -> mB
			printf("   %c\n",letra);
			sleep(1);
		semSignal(semid,0); // 0 -> mA
		letra+=2;
	}
	return 0;
}