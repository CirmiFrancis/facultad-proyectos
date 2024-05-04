/*
	Una sincronizacion entre dos procesos usado señales. Imprimir el abecedario de forma intercalada.
	Padre = mayus
	Hijo = minus
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

void handler (int signum) {
}

int main() {
	pid_t pid;
	int i;
	char letra = 'A';
	
	signal(SIGUSR1,handler);
	pid = fork();
	
	if (pid == -1) {
		perror("Error al crear proceso hijo");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0) {
		while (1) {
			pause();
			printf("%c ", letra);
			fflush(stdout);
			letra += 2;
			
			if (letra > 'Z') {
				letra = 'A';
				kill(getppid(), SIGUSR1);
			}
		}
	}
	else {
		while (1) {
			printf("%c ", letra);
			fflush(stdout);
			letra += 2;
			
			if (letra > 'Z') {
				letra = 'A';
				kill(pid, SIGUSR1);
				pause();
			}	
		}
	}
	return 0;
}