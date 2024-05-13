/*
 * abc5jromer.c
 * 
 * hijo1 graba abcedario en mayusculas
 * hijo2 graba un abcedario en minusculas
 * la secuencia de ejecucion es hijo1 hijo2 hijo1 hijo2 ... 
 * sincronizado con senales
 * 
 * VERSION JROMER
 *    busque los <microsegundos> apropiados para su computador
 * para que esto funcione!
 * En mi pc anduvo con 100
 * 
 * compilar:
 * $ gcc -Wall -o abc5 abc5.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

// handlers
void f_hijoA(int);         //handler SIGUSR1 para el hijoA
void f_hijob(int);         //handler SIGUSR1 para el hijob
void f_killerFather(int);  //handler SIGINT  para el padre
void tiempo(useconds_t);   //sono la campana!

// variables globales
char letraA;
char letrab;
pid_t pidA,pidb;

int main(int argc, char *argv[])
{
	if ( argc != 2 ) {
		printf("Forma de uso:\n$ abc5jromer <microsegundos>\n");
		exit(1);
	}
	pidA = fork();
	if ( pidA > 0 ) {
		// padre
		pidb = fork();
		if ( pidb > 0 ) {
			// padre
			signal(SIGUSR1,f_killerFather);
			signal(SIGINT,f_killerFather);
			while(1) { // loop romerizado
				tiempo(atoi(argv[1]));
				kill(pidA,SIGUSR1);
				pause();
				tiempo(atoi(argv[1]));
				kill(pidb,SIGUSR1);
				pause();
			}
		} else {
			// hijob
			letrab='b';
			signal(SIGUSR1,f_hijob);
			while(letrab <= ('z'+1)) {
				pause();
				tiempo(atoi(argv[1]));
				kill(getppid(),SIGUSR1);
			}
			kill(getppid(),SIGINT);
		}
	} else {
		// hijoA
		letraA='A';
		signal(SIGUSR1,f_hijoA);
		while(letraA <= ('Z'+1)) {
			pause();
			tiempo(atoi(argv[1]));
			kill(getppid(),SIGUSR1);
		}
		kill(getppid(),SIGINT);
	}
	exit(0);
}

void f_hijoA(int signo) {         //handler SIGUSR1 para el hijoA
	printf("%c\n",letraA);
	letraA+=2;
}
void f_hijob(int signo) {         //handler SIGUSR1 para el hijob
	printf("  %c\n",letrab);
	letrab+=2;
}
void f_killerFather(int signo) {  //handler SIGINT  para el padre
	if ( signo == 2 ) {
		kill(pidA,SIGKILL);
		kill(pidb,SIGKILL);
		exit(0);
	}
}
void tiempo(useconds_t seg) {   //sono la campana!
	usleep(seg);
}