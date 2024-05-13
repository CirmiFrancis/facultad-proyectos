/*
 * signal1.c 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>

void sig_alarma(int);

#define INPUT_TIME_OUT 15
int salir=0;
sigjmp_buf jmpbuf;


int main(int argc, char **argv)
{
	signal(SIGALRM,sig_alarma);

	if (sigsetjmp(jmpbuf,1)) {
		printf("Salto incondicional de salida!\n");
		salir=1;
	}
	
	while(!salir) {
		alarm(INPUT_TIME_OUT);
		char teclas[256];
		printf("Ingreso Algo (fin=salir):");
		fgets(teclas,256,stdin);
		teclas[strlen(teclas)-1]='\0'; // reemplaza \n por \0
		if ( strcmp(teclas,"fin") == 0 ) salir=1; 
	}
	printf("main(): fin!\n");
	return 0;
}

// handle de la se#al SIGALRM
void sig_alarma(int signo) {
	printf("sig_alarma(%d): hago siglongjmp()\n",signo);
	siglongjmp(jmpbuf,1);  // salto a main()
}