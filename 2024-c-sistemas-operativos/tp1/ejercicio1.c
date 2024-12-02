// Implementación del programa Shell (en su versión más completa, que soporta procesos foreground y background; que haga uso de la señal SIGCHLD para verificar la finalización de procesos en background) que evite la existencia de procesos zombies. 
// El programa termina cuando el usuario ingresa el comando “salir”. Si el usuario presiona CTRL+C el programa esperará a que terminen todos los procesos y luego finalizará sin dejar procesos zombies o huérfanos.

// Librerías necesarias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

// Flag para indicar si se debe terminar el programa
volatile sig_atomic_t exit_requested = 0;

// Maneja la señal SIGCHLD para limpiar procesos hijos terminados
void sigchld_handler(int signo) {
    while (waitpid(-1, NULL, WNOHANG) > 0); // Recolecta todos los procesos hijos zombies
}

// Maneja la señal SIGINT para permitir una salida controlada
void sigint_handler(int signo) {
    printf("\nSe recibió CTRL+C. Esperando que terminen los procesos en background...\n");
    exit_requested = 1;
}

int main() {
    char input[256];
    char *args[20];
    pid_t pid;
    int background;

    // Configurar manejadores de señales
    signal(SIGCHLD, sigchld_handler); // Maneja la finalización de procesos hijos
    signal(SIGINT, sigint_handler);  // Maneja CTRL+C

    while (1) {
        // Mostrar el prompt
        printf("shell> ");
        fflush(stdout);

        // Leer la entrada del usuario
        if (fgets(input, sizeof(input), stdin) == NULL) break;

        // Quitar el salto de línea
        input[strcspn(input, "\n")] = '\0';

        // Comprobar si el usuario quiere salir
        if (strcmp(input, "salir") == 0 || exit_requested) break;

        // Parsear la entrada en argumentos
        int i = 0;
        char *token = strtok(input, " ");
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Comprobar si el proceso debe ejecutarse en background
        background = (i > 0 && strcmp(args[i - 1], "&") == 0);
        if (background) {
            args[i - 1] = NULL; // Eliminar el "&" de los argumentos
        }

        // Crear un proceso hijo
        pid = fork();
        if (pid < 0) {
            perror("Error al crear el proceso");
            continue;
        } else if (pid == 0) {
            // Proceso hijo
            if (execvp(args[0], args) == -1) {
                perror("Error al ejecutar el comando");
                exit(EXIT_FAILURE);
            }
        } else {
            // Proceso padre
            if (!background) {
                // Si no es en background, esperar al hijo
                waitpid(pid, NULL, 0);
            } else {
                printf("Proceso en background iniciado con PID %d\n", pid);
            }
        }
    }

    // Esperar a que terminen todos los procesos en background antes de salir
    printf("Saliendo de la shell. Esperando procesos en background...\n");
    while (waitpid(-1, NULL, 0) > 0);

    printf("Todos los procesos terminados. Adiós.\n");
    return 0;
}