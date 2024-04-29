#include <stdio.h>
#include <stdlib.h> // POR ALGÚN MOTIVO, ESTE NO SE NECESARIO.
#include <sys/types.h>
#include <sys/wait.h> // Este encabezado proporciona la función wait(), que se utiliza para esperar a que los procesos hijos terminen.
#include <unistd.h>

int main(int argc, char **argv)
{
	fork();
	fork();
	printf("Hola! soy el proceso PID=%d, mi padre es PID=%d\n",getpid(),getppid());
	wait(0);
	wait(0);
	wait(0);
	wait(0);
	return 0;
}