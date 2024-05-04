#include <stdio.h>
#include <stdlib.h> // POR ALGÚN MOTIVO, ESTE NO ES NECESARIO.
#include <sys/types.h>
#include <sys/wait.h> // Este encabezado proporciona la función wait(), que se utiliza para esperar a que los procesos hijos terminen.
#include <unistd.h>

int main(int argc, char **argv)
{
	fork();
	fork();
	printf("Hola! Soy el proceso PID=%d, mi padre PID=%d\n", getpid(), getppid());
	wait(0);
	wait(0);
	wait(0);
	wait(0);
	return 0;
}

// Este programa realiza 2 fork(). 
// Devuelve el PID del proceso actual y del proceso padre, para cada uno de los procesos.
// Espera a que terminen de ejecutarse los procesos hijos para luego seguir con el proceso padre (esto evita el pid=1).
// Finaliza exitosamente el programa.