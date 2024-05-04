#include <stdio.h>
#include <stdlib.h> // POR ALGÚN MOTIVO, ESTE NO ES NECESARIO.
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	pid_t pid = fork();
	printf("Hola! Soy el proceso PID=%d, mi hijo pid=%d, mi padre PPID=%d\n", getpid(), pid, getppid());
	return 0;
}

// Este programa crea un proceso hijo y devuelve el PID del proceso actual, del proceso hijo y del proceso padre, para cada uno de los procesos.