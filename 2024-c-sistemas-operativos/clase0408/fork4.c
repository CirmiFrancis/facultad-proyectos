#include <stdio.h>
#include <stdlib.h> // POR ALGÚN MOTIVO, ESTE NO ES NECESARIO.
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	fork();
	fork();
	fork();
	printf("Hola! Soy el proceso PID=%d, mi padre PID=%d\n", getpid(), getppid());
	return 0;
}

// fork()^n => 2^n

// Este programa crea un proceso hijo, luego crea un proceso hijo y vuelve a crear otro proceso hijo, por lo que existirían 8 procesos. Devuelve el PID del proceso actual y del proceso padre, para cada uno de los procesos.