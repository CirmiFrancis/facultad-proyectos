/*
 * fork2.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int i;
	for(i=0;i<5;i++) {
		pid_t pid = fork();
		//if ( pid == 0 ) break;
	}
	printf("soy pid %d hijo de %d\n",getpid(),getppid());
	return 0;
}