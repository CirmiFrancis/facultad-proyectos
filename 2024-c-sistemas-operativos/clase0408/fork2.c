#include <stdio.h>
#include <stdlib.h> // POR ALGÚN MOTIVO, ESTE NO SE NECESARIO.
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	pid_t pid = fork();
	printf("Hola! soy el proceso PID=%d, variable pid=%d, mi padre PID=%d\n",getpid(),pid,getppid());
	return 0;
}