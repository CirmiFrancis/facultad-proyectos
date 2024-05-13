/*
 * thread1.c
 * 
 * $ gcc -Wall -o thread1 thread1.c -lpthread
 * 
 * programa de hilos que parece estar bien, pero que a veces funciona
 * y otras veces no funciona
 * que esta pasando???
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *hijoA(void *);  // hilo que imprime letras mayusculas
void *hijob(void *);  // hilo que imprime letras minusculas

int main(int argc, char **argv)
{
	pthread_t hiloA, hilob;
	int rc = pthread_create(&hiloA,NULL,hijoA,NULL);
	printf("main(): rc=%d creando hiloA\n",rc);
	rc = pthread_create(&hilob,NULL,hijob,NULL);
	printf("main(): rc=%d creando hilob\n",rc);
	return 0;
}

void *hijoA(void *p) {  // hilo que imprime letras mayusculas
	char letra='A';
	while(letra <= 'Z') {
		printf("%c\n",letra);
		letra+=2;
	}
	pthread_exit(NULL);
}

void *hijob(void *p) {  // hilo que imprime letras minusculas
	char letra='b';
	while(letra <= 'z') {
		printf("   %c\n",letra);
		letra+=2;
	}
	pthread_exit(NULL);
}