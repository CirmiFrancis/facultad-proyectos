/*
 * delsem.c
 * 
 * Proceso de borrado de semaforos SVR4
 * $ ipcs
 * $ gcc -Wall -o delsem delsem.c
 * $ ipcs
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
	printf("delsem: semid = %d\n",semid);
	semctl(semid,0,IPC_RMID);
	printf("delsem: semaforos 0xA borrados!\n");
	return 0;
}