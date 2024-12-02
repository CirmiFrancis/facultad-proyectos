#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

/* Creo memoria compartida, semaforos e inicializo semaforos */

// gcc -Wall -o shmcrear shmcrear.c -I. mysem.c
int main(void) {
	// memoria compartida de N=1 longitud mensaje 256 bytes
	int shmid1 = shmget(0xA,256,0777|IPC_CREAT);
	int shmid2 = shmget(0xB,256,0777|IPC_CREAT);

	// arreglo de 4 semaforos:
	// S0, S1 son usados por el writer del usuario1 y el reader del usuario2
	// S2, S3 son usados por el writer del usuario2 y el reader del usuario1
	int semid = semget(0xA,4,0777|IPC_CREAT);	
	
	printf("shmid1 = %d\n",shmid1);
	printf("shmid2 = %d\n",shmid2);
	printf("semid = %d\n",semid);

	// inicializo semaforos
	semctl(semid,0,SETVAL,1); // S0=1
	semctl(semid,1,SETVAL,0); // S1=0
	semctl(semid,2,SETVAL,1); // S2=1
	semctl(semid,3,SETVAL,0); // S3=0

	// inicializo contenido de memoria compartida
	/*
	char *msg1 = shmat(shmid1,0,0);
	memset(msg1,0,512);
	char *msg2 = shmat(shmid2,0,0);
	memset(msg2,0,512);
	*/
	
	// desconecto memoria compartida
	/*
	shmdt(msg1);
	shmdt(msg2);
	*/
	
	return 0;
}
