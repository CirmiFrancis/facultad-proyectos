/*
	Una sincronizacion entre dos procesos usado señales. Imprimir el abecedario de forma intercalada.
	Padre = mayus
	Hijo = minus
*/

/*
	Las señales (signals) son una forma de comunicación asíncrona entre procesos o entre un proceso y el sistema operativo. 
	Las señales se utilizan para notificar a un proceso de eventos o condiciones específicas que ocurren durante la ejecución del programa. 
	Algunos ejemplos comunes de señales incluyen la señal de interrupción (SIGINT), que se envía al presionar Ctrl+C en la terminal, y la señal de finalización (SIGTERM), que se envía para solicitar la terminación de un programa.

	El manejo de señales en C se realiza mediante la función signal() o mediante la función sigaction(). Estas funciones permiten registrar funciones de manejo de señales que se ejecutarán cuando se reciba una señal específica.
*/

// Incompleto. Sacado de CHAT GPT.

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