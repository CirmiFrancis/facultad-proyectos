#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
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