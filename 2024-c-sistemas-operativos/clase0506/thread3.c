/*
 * thread1.c
 * 
 * $ gcc -Wall -o thread1 thread1.c -lpthread
 * 
 * programa de hilos que parece estar bien, pero que a veces funciona
 * y otras veces no funciona
 * que esta pasando???  main no espera a la finalizacion de los hilos
 * 
 * intentando (fallidamente) de hacer secuencia hiloA hilob hiloA hilob
 * usando usleep() 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h> // necesario para usar hilos

void *hijoA(void *);  // hilo que imprime letras mayusculas
void *hijob(void *);  // hilo que imprime letras minusculas

int main(int argc, char **argv)
{
	pthread_t hiloA, hilob;
	int rc = pthread_create(&hiloA,NULL,hijoA,NULL); // crea un nuevo hilo con pthread_create. Esta función toma cuatro argumentos: la variable hiloA que se utilizará para identificar el hilo, atributos del hilo (en este caso NULL para los valores por defecto), la función que el hilo ejecutará (hijoA en este caso) y argumentos para esa función (también NULL en este caso). El valor de retorno de pthread_create se almacena en rc, que generalmente es 0 si la creación del hilo tiene éxito.
	printf("main(): rc=%d creando hiloA\n",rc);
	rc = pthread_create(&hilob,NULL,hijob,NULL);
	printf("main(): rc=%d creando hilob\n",rc);
	printf("main(): hago join() esperando a la finalizacion del hiloA\n");
	rc = pthread_join(hiloA,NULL); // _join: estas llamadas bloquean el hilo principal (en este caso, la función main) hasta que los hilos hiloA y hilob terminen su ejecución.
	printf("main(): join hiloA retorno rc=%d\n",rc);
	printf("main(): hago join() esperando a la finalizacion del hilob\n");
	rc = pthread_join(hilob,NULL); // _join: estas llamadas bloquean el hilo principal (en este caso, la función main) hasta que los hilos hiloA y hilob terminen su ejecución.
	printf("main(): join hilob retorno rc=%d\n",rc);
	printf("main(): fin!\n");
	return 0;
}

// hilo que imprime letras mayusculas
void *hijoA(void *p) { // *p indica que hijoA,hijob toman un puntero como argumento.
	char letra='A'; // 'A' = 65
	while(letra <= 'Z') { // 'Z' = 90
		printf("%c\n",letra);
		usleep(10); // es una función que pausa la ejecución del hilo actual durante un período de tiempo especificado en microsegundos. En este caso, usleep(10); pausará la ejecución del hilo actual durante 10 microsegundos. Es importante destacar que usleep está obsoleto y puede no estar disponible en todos los sistemas. Se recomienda el uso de nanosleep o funciones similares en su lugar para pausar la ejecución durante intervalos de tiempo.
		letra+=2;
	}
	pthread_exit(NULL); // es una llamada que indica al hilo actual que debe terminar su ejecución. En este caso, cuando se alcanza esta línea de código, el hilo que ejecuta la función hijoA finalizará su ejecución. El argumento NULL pasado a pthread_exit indica que el hilo no devuelve ningún valor. Esta llamada también libera cualquier recurso asociado con el hilo, como la pila de ejecución, y notifica al sistema operativo que el hilo ha terminado.
}

// hilo que imprime letras minusculas
void *hijob(void *p) { 
	char letra='b';
	usleep(10);
	while(letra <= 'z') {
		printf("   %c\n",letra);
		usleep(10);
		letra+=2;
	}
	pthread_exit(NULL);
}