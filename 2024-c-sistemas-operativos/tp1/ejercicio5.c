// Implementación de una sincronización con procesos emparentados PadreA, HijoB y HijoC de forma tal, que la secuencia de ejecución y acceso a su sección crítica sea la siguiente: PadreA HijoB PadreA HijoC... detener el proceso luego de N iteraciones completas (el número N se ingresa por línea de comandos). HijoB e HijoC son hermanos. Resolver la sincronización de la forma que a Ud. le parezca más apropiada (no usar señales).

// Librerias necesarias
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <N_iteraciones>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int N = atoi(argv[1]);
    if (N <= 0) {
        fprintf(stderr, "El número de iteraciones debe ser un entero positivo.\n");
        return EXIT_FAILURE;
    }

    // Pipes para sincronización
    int pipeAB[2], pipeBA[2], pipeAC[2], pipeCA[2];
    if (pipe(pipeAB) == -1 || pipe(pipeBA) == -1 || pipe(pipeAC) == -1 || pipe(pipeCA) == -1) {
        perror("Error al crear pipes");
        return EXIT_FAILURE;
    }

    pid_t pidB = fork(); // Crear HijoB
    if (pidB == 0) {
        // Proceso HijoB
        close(pipeAB[1]); // Cerrar escritura de pipeAB
        close(pipeBA[0]); // Cerrar lectura de pipeBA
        close(pipeAC[0]); // No usado por HijoB
        close(pipeAC[1]); // No usado por HijoB
        close(pipeCA[0]); // No usado por HijoB
        close(pipeCA[1]); // No usado por HijoB

        for (int i = 0; i < N; i++) {
            char signal;
            read(pipeAB[0], &signal, 1); // Espera señal del PadreA
            printf("HijoB\n");
            write(pipeBA[1], "B", 1); // Envía señal de vuelta al PadreA
        }

        close(pipeAB[0]);
        close(pipeBA[1]);
        exit(EXIT_SUCCESS);
    }

    pid_t pidC = fork(); // Crear HijoC
    if (pidC == 0) {
        // Proceso HijoC
        close(pipeAC[1]); // Cerrar escritura de pipeAC
        close(pipeCA[0]); // Cerrar lectura de pipeCA
        close(pipeAB[0]); // No usado por HijoC
        close(pipeAB[1]); // No usado por HijoC
        close(pipeBA[0]); // No usado por HijoC
        close(pipeBA[1]); // No usado por HijoC

        for (int i = 0; i < N; i++) {
            char signal;
            read(pipeAC[0], &signal, 1); // Espera señal del PadreA
            printf("HijoC\n");
            write(pipeCA[1], "C", 1); // Envía señal de vuelta al PadreA
        }

        close(pipeAC[0]);
        close(pipeCA[1]);
        exit(EXIT_SUCCESS);
    }

    // Proceso PadreA
    close(pipeAB[0]); // Cerrar lectura de pipeAB
    close(pipeBA[1]); // Cerrar escritura de pipeBA
    close(pipeAC[0]); // Cerrar lectura de pipeAC
    close(pipeCA[1]); // Cerrar escritura de pipeCA

    for (int i = 0; i < N; i++) {
        printf("PadreA\n");
        write(pipeAB[1], "A", 1); // Señala a HijoB
        char signal;
        read(pipeBA[0], &signal, 1); // Espera señal de HijoB

        printf("PadreA\n");
        write(pipeAC[1], "A", 1); // Señala a HijoC
        read(pipeCA[0], &signal, 1); // Espera señal de HijoC
    }

    close(pipeAB[1]);
    close(pipeBA[0]);
    close(pipeAC[1]);
    close(pipeCA[0]);

    // Esperar a que terminen los hijos
    waitpid(pidB, NULL, 0);
    waitpid(pidC, NULL, 0);

    printf("Ejecución completada con %d iteraciones.\n", N);
    return EXIT_SUCCESS;
}