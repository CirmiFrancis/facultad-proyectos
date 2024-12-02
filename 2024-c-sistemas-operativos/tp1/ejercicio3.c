// Implementación de una sincronización de los hilos A, B y C de forma tal, que la secuencia de ejecución y acceso a su sección crítica sea la siguiente: ABAC... detener el proceso luego de N iteraciones completas (el número N se ingresa por línea de comandos). Resolver la sincronización con variables Mutex (librería pthread).

// Librerias necesarias
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Mutex y variables de condición
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_A = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_B = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_C = PTHREAD_COND_INITIALIZER;

int turn = 0; // Variable para controlar el turno (0: A1, 1: B, 2: A2, 3: C)
int iterations = 0; // Contador de iteraciones completas
int N; // Número de iteraciones

void *thread_A(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        // Espera según su turno
        while (turn != 0 && turn != 2)
            pthread_cond_wait(&cond_A, &mutex);

        printf("Hilo A\n");

        if (turn == 0) {
            turn = 1; // A1 sigue con B
            pthread_cond_signal(&cond_B);
        } else if (turn == 2) {
            turn = 3; // A2 sigue con C
            pthread_cond_signal(&cond_C);
        }

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *thread_B(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        // Espera según su turno
        while (turn != 1)
            pthread_cond_wait(&cond_B, &mutex);

        printf("Hilo B\n");
        turn = 2; // B sigue con A2
        pthread_cond_signal(&cond_A);

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *thread_C(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        // Espera según su turno
        while (turn != 3)
            pthread_cond_wait(&cond_C, &mutex);

        printf("Hilo C\n");

        // Incrementa el contador de iteraciones al finalizar una secuencia completa
        iterations++;
        if (iterations >= N) {
            pthread_mutex_unlock(&mutex);
            break; // Salir del bucle
        }

        turn = 0; // C sigue con A1
        pthread_cond_signal(&cond_A);

        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 2 || (N = atoi(argv[1])) <= 0) {
        fprintf(stderr, "Uso: %s <número_de_iteraciones>\n", argv[0]);
        return EXIT_FAILURE;
    }

    pthread_t threadA, threadB, threadC;

    // Crear hilos
    pthread_create(&threadA, NULL, thread_A, NULL);
    pthread_create(&threadB, NULL, thread_B, NULL);
    pthread_create(&threadC, NULL, thread_C, NULL);

    // Esperar al hilo C (controlador principal de las iteraciones)
    pthread_join(threadC, NULL);

    // Cancelar los hilos restantes
    pthread_cancel(threadA);
    pthread_cancel(threadB);

    // Destruir mutex y variables condicionales
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_A);
    pthread_cond_destroy(&cond_B);
    pthread_cond_destroy(&cond_C);

    printf("Ejecución completada con %d iteraciones.\n", N);
    return EXIT_SUCCESS;
}