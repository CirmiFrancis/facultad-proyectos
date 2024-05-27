/*
 * versem.c
 * 
 * Proceso de visualizacion de semaforos SVR4
 * $ gcc -Wall -o versem versem.c
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
	printf("versem: semid = %d\n",semid);
	// obtengo valor del semaforo 0
	int valSem0 = semctl(semid,0,GETVAL);
	// semaforo 1 inicializado en 0
	int valSem1 = semctl(semid,1,GETVAL);
	printf("versem: valor semaforo 0 = %d, valor semaforo 1 = %d\n",valSem0,valSem1);
	return 0;
}