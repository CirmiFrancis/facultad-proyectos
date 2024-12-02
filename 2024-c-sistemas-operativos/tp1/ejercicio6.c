// Realizar un programa que reciba por línea de comandos un comando a ejecutar y sus argumentos. El programa va crear un proceso hijo con dicho comando y el proceso padre leerá la salida del comando. Para lograr esto, cree un pipe entre proceso padre e hijo y utilice la función dup() o dup2() para duplicar la salida en el pipe y luego leer la salida usando el pipe. No está permitido usar la función popen() que resume o simplifica la técnica propuesta. No generar procesos huérfanos ni zombies.

// Librerias necesarias
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <comando> [argumentos]\n", argv[0]);
        return EXIT_FAILURE;
    }

    int pipefd[2]; // pipefd[0]: lectura, pipefd[1]: escritura

    // Crear el pipe
    if (pipe(pipefd) == -1) {
        perror("Error al crear el pipe");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Error al hacer fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        // Proceso hijo
        close(pipefd[0]); // Cerrar el extremo de lectura del pipe

        // Redirigir la salida estándar (stdout) al pipe
        if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
            perror("Error al redirigir la salida estándar");
            exit(EXIT_FAILURE);
        }

        // Cerrar el extremo de escritura original del pipe
        close(pipefd[1]);

        // Ejecutar el comando con sus argumentos
        execvp(argv[1], &argv[1]);
        perror("Error al ejecutar el comando");
        exit(EXIT_FAILURE);
    } else {
        // Proceso padre
        close(pipefd[1]); // Cerrar el extremo de escritura del pipe

        char buffer[1024];
        ssize_t bytes_read;

        // Leer la salida del pipe y escribirla en la salida estándar del padre
        while ((bytes_read = read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
            buffer[bytes_read] = '\0'; // Null-terminar la cadena
            printf("%s", buffer);
        }

        close(pipefd[0]); // Cerrar el extremo de lectura del pipe

        // Esperar a que termine el proceso hijo
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("\nEl comando terminó con código de salida %d.\n", WEXITSTATUS(status));
        } else {
            printf("\nEl comando no terminó correctamente.\n");
        }
    }

    return EXIT_SUCCESS;
}