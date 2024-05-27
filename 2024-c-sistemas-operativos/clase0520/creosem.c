/*
 * creosem.c
 * 
 * Proceso de creacion de semaforos SVR4
 * $ gcc -Wall -o creosem creosem.c
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
	// creo dos semaforos SVR4, con clave 0xA, permisos 0600
	int semid = semget(0xA,2,IPC_CREAT|IPC_EXCL|0600);
	printf("creosem: semid = %d\n",semid);
	
	return 0;
}