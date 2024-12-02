// Implementar un proceso al cual se le indique por línea de comando la cantidad de procesos a crear, todos los procesos a crear serán hermanos; cada uno de ellos retornará un valor entero distinto al proceso padre. Los procesos hijos quedan en un loop eterno, en una espera no activa, cuando recibe la señal SIGUSR1 o SIGINT el proceso hijo termina retornando un valor entero distinto al de sus hermanos. El proceso padre reportará por pantalla la sumatoria de los retornos de los procesos hijos creados. No se permitirá que existan procesos huérfanos o zombies.

// Librerias necesarias
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t *child_pids; // Arreglo para almacenar los PIDs de los procesos hijos
int child_index;   // Índice único para cada hijo

void signal_handler(int signo) {
    for (int i = 0; child_pids[i] != 0; i++) 
        kill(child_pids[i], SIGUSR1); // Enviar SIGUSR1 a los hijos
}

void child_signal_handler(int signo) {
    exit(child_index); // Cada hijo retorna su índice único
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <cantidad_de_procesos>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int num_children = atoi(argv[1]);
    if (num_children <= 0) {
        fprintf(stderr, "La cantidad de procesos debe ser un número positivo.\n");
        return EXIT_FAILURE;
    }

    child_pids = (pid_t *)calloc(num_children + 1, sizeof(pid_t));
    if (!child_pids) {
        perror("Error al reservar memoria");
        return EXIT_FAILURE;
    }

    signal(SIGINT, signal_handler); // Configurar manejador para SIGINT

    for (int i = 0; i < num_children; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("Error al crear el proceso");
            free(child_pids);
            return EXIT_FAILURE;
        } else if (pid == 0) {
            // Proceso hijo
            signal(SIGUSR1, child_signal_handler); // Manejador para SIGUSR1
            child_index = i + 1; // Índice único del hijo
            printf("Hijo %d creado con PID %d.\n", child_index, getpid());
            while (1) pause(); // Espera no activa
        } else {
            // Proceso padre
            child_pids[i] = pid; // Guardar PID del hijo
        }
    }

    // Proceso padre: Esperar a los hijos y calcular la sumatoria de retornos
    int status, sum = 0;
    for (int i = 0; i < num_children; i++) {
        pid_t child_pid = waitpid(child_pids[i], &status, 0);
        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            printf("Hijo con PID %d terminó con código de salida %d.\n", child_pid, exit_code);
            sum += exit_code;
        }
    }

    printf("La sumatoria de los retornos de los hijos es: %d\n", sum);
    free(child_pids);
    printf("Proceso padre finalizado.\n");
    return EXIT_SUCCESS;
}