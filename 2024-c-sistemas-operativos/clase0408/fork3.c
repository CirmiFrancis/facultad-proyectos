#include <stdio.h>
#include <stdlib.h> // POR ALGÚN MOTIVO, ESTE NO ES NECESARIO.
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	fork();
	fork();
	printf("Hola! Soy el proceso PID=%d, mi padre PPID=%d\n", getpid(), getppid());
	return 0;
}

// Este programa crea un proceso hijo y luego crea un proceso hijo para ambos procesos ya existentes, por lo que existirían 4 procesos. Devuelve el PID del proceso actual y del proceso padre, para cada uno de los procesos.