/*
 * procAB.c
 * 
 * $ gcc -Wall -o procAB procAB.c 
 * 
 * proceso AB imprime letras mayusculas y minusculas
 * 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	printf("main(): llamo a ./initsem\n");
	system("./initsem");
	printf("main(): llame a ./initsem\n");
	pid_t pid = fork();
	if ( pid == 0 ) {
		// hijo1
		char *argv[2] = { "./procA", NULL };
		int rc = execvp(argv[0],argv);
		printf("hijo1: error en execvp() rc=%d!!!\n",rc);
		exit(1);
	} else {
		// padre
		pid_t pid2 = fork();
		if ( pid2 == 0 ) {
			// hijo2
			char *argv[2] = { "./procB", NULL };
			int rc = execvp(argv[0],argv);
			printf("hijo2: error en execvp() rc=%d!!!\n",rc);
			exit(1);
		} else {
			// padre, espero por la finalizacion de mis hijos
			wait(0);
			wait(0);
		}
	}
	printf("main(): fin!\n");
	return 0;
}