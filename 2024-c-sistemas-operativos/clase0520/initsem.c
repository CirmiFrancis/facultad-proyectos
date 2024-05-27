/*
 * initsem.c
 * Proceso de inicializacion de semaforos SVR4
 * $ gcc -Wall -o initsem initsem.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h> // memoria compartida
#include <sys/sem.h> // semaforos system V  SVR4

int main(int argc, char **argv)
{
	// obtengo semid de semaforos SVR4 con clave 0xA previamente creado
	int semid = semget(0xA,0,0);
	printf("initsem: semid = %d\n",semid);
	// semaforo 0 inicializado en 1
	semctl(semid,0,SETVAL,1);
	// semaforo 1 inicializado en 0
	semctl(semid,1,SETVAL,0);
	
	return 0;
}