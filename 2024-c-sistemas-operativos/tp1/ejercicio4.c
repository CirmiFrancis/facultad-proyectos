// Implementación de una sincronización con procesos independientes A, B y C de forma tal, que la secuencia de ejecución y acceso a su sección crítica sea la siguiente: ABAC... detener el proceso luego de N iteraciones completas (el número N se ingresa por línea de comandos). Resolver la sincronización con: semáforos SVR4.

// Librerias necesarias
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

// Operaciones con semáforos
struct sembuf wait_op = {0, -1, 0};  // Operación WAIT
struct sembuf signal_op = {0, 1, 0}; // Operación SIGNAL

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <número de iteraciones>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int n = atoi(argv[1]); // Número de iteraciones
    if (n <= 0) {
        fprintf(stderr, "El número de iteraciones debe ser mayor a 0.\n");
        exit(EXIT_FAILURE);
    }

    // Crear semáforos (3 semáforos: A, B y C)
    int sem_id = semget(IPC_PRIVATE, 3, IPC_CREAT | 0666);
    if (sem_id == -1) {
        perror("Error al crear los semáforos");
        exit(EXIT_FAILURE);
    }

    // Inicializar los semáforos (A=1, B=0, C=0)
    semctl(sem_id, 0, SETVAL, 1); // Semáforo A
    semctl(sem_id, 1, SETVAL, 0); // Semáforo B
    semctl(sem_id, 2, SETVAL, 0); // Semáforo C

    // Crear procesos A, B y C
    pid_t pidA = fork();
    if (pidA == 0) {
        // Proceso A
        for (int i = 0; i < 2 * n; i++) {
            wait_op.sem_num = 0;    // Espera en el semáforo A
            semop(sem_id, &wait_op, 1);
            printf("Proceso A\n");
            signal_op.sem_num = (i % 2 == 0) ? 1 : 2; // Señal a B o C
            semop(sem_id, &signal_op, 1);
        }
        exit(EXIT_SUCCESS);
    }

    pid_t pidB = fork();
    if (pidB == 0) {
        // Proceso B
        for (int i = 0; i < n; i++) {
            wait_op.sem_num = 1;    // Espera en el semáforo B
            semop(sem_id, &wait_op, 1);
            printf("Proceso B\n");
            signal_op.sem_num = 0; // Señal a A
            semop(sem_id, &signal_op, 1);
        }
        exit(EXIT_SUCCESS);
    }

    pid_t pidC = fork();
    if (pidC == 0) {
        // Proceso C
        for (int i = 0; i < n; i++) {
            wait_op.sem_num = 2;    // Espera en el semáforo C
            semop(sem_id, &wait_op, 1);
            printf("Proceso C\n");
            signal_op.sem_num = 0; // Señal a A
            semop(sem_id, &signal_op, 1);
        }
        exit(EXIT_SUCCESS);
    }

    // Proceso padre espera a los hijos
    wait(NULL);
    wait(NULL);
    wait(NULL);

    // Liberar recursos de los semáforos
    semctl(sem_id, 0, IPC_RMID, 0);
    printf("Ejecución completada con %d iteraciones.\n", n);

    return EXIT_SUCCESS;
}