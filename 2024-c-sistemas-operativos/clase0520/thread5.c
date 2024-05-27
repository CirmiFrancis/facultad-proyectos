/*
 * thread4.c
 * 
 * $ gcc -Wall -o thread5 thread5.c -lpthread
 * 
 * intentando hacer secuencia hiloA hilob hiloA hilob
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

void *hijoA(void *);  // hilo que imprime letras mayusculas
void *hijob(void *);  // hilo que imprime letras minusculas

sem_t mA, mB;

int main(int argc, char **argv)
{
	// mA=1
	sem_init(&mA,0,1);
	// mB=0
	sem_init(&mB,0,0);
	
	pthread_t hiloA, hilob;
	int rc = pthread_create(&hiloA,NULL,hijoA,NULL);
	printf("main(): rc=%d creando hiloA\n",rc);
	rc = pthread_create(&hilob,NULL,hijob,NULL);
	printf("main(): rc=%d creando hilob\n",rc);
	printf("main(): hago join() esperando a la finalizacion del hiloA\n");
	rc = pthread_join(hiloA,NULL);
	printf("main(): join hiloA retorno rc=%d\n",rc);
	printf("main(): hago join() esperando a la finalizacion del hilob\n");
	rc = pthread_join(hilob,NULL);
	printf("main(): join hilob retorno rc=%d\n",rc);
	printf("main(): fin!\n");
	return 0;
}


void *hijoA(void *p) {  // hilo que imprime letras mayusculas
	char letra='A';
	while(letra <= 'Z') {
		sem_wait(&mA);
			printf("%c\n",letra);
		sem_post(&mB);
		letra+=2;
	}
	pthread_exit(NULL);
}

void *hijob(void *p) {  // hilo que imprime letras minusculas
	char letra='b';
	while(letra <= 'z') {
		sem_wait(&mB);
			printf("   %c\n",letra);
		sem_post(&mA);
		letra+=2;
	}
	pthread_exit(NULL);
}