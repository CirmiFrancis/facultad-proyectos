// Implementar un servidor (basado en hilos) usando sockets tcp/ip. El cliente (use telnet) envía un comando Linux al servidor, el servidor lo ejecuta y devuelve la salida del comando al cliente. La interacción entre cliente y servidor termina cuando el cliente envía el comando “salir”. Reusar el código del ejercicio anterior.

// Librerias necesarias
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PORT 8080          // Puerto en el que escucha el servidor
#define BUFFER_SIZE 1024   // Tamaño del buffer para la comunicación

// Estructura para pasar parámetros a los hilos
typedef struct {
    int client_socket;
} thread_arg;

// Función que ejecuta un comando y envía la salida al cliente
void* handle_client(void* arg) {
    thread_arg* t_arg = (thread_arg*)arg; // Cast de argumento
    int client_socket = t_arg->client_socket;
    free(t_arg); // Liberar memoria del argumento

    char buffer[BUFFER_SIZE];
    ssize_t read_size;

    while (1) {
        // Leer el comando del cliente
        memset(buffer, 0, BUFFER_SIZE);
        read_size = read(client_socket, buffer, BUFFER_SIZE - 1);
        if (read_size <= 0) {
            perror("Error al leer del socket");
            break;
        }
        
        // Eliminar el salto de línea al final del comando
        buffer[strcspn(buffer, "\n")] = 0; // Elimina el salto de línea
        buffer[strcspn(buffer, "\r")] = 0; // Elimina retorno de carro (si está presente)

        // Verificar si el cliente desea salir
        if (strcmp(buffer, "salir") == 0) {
            printf("Cliente desconectado.\n");
            break;
        }

        // Crear un pipe para ejecutar el comando
        int fd[2];
        if (pipe(fd) == -1) {
            perror("Error al crear pipe");
            break;
        }

        pid_t pid = fork();
        if (pid < 0) {
            perror("Error al crear el proceso hijo");
            break;
        }

        if (pid == 0) {
            // Proceso hijo
            close(fd[0]); // Cerrar el extremo de lectura del pipe
            dup2(fd[1], STDOUT_FILENO); // Redirigir stdout al pipe
            dup2(fd[1], STDERR_FILENO); // Redirigir stderr al pipe
            close(fd[1]); // Cerrar el extremo de escritura del pipe

            // Ejecutar el comando
            char* args[] = {"/bin/sh", "-c", buffer, NULL}; // Usar /bin/sh para ejecutar comandos
            execv(args[0], args);
            perror("Error al ejecutar el comando"); // Mensaje de error
            exit(EXIT_FAILURE);
        } else {
            // Proceso padre
            close(fd[1]); // Cerrar el extremo de escritura del pipe
            wait(NULL); // Esperar a que el hijo termine

            // Leer la salida del comando desde el pipe
            memset(buffer, 0, BUFFER_SIZE);
            ssize_t bytes_read = read(fd[0], buffer, BUFFER_SIZE - 1);
            if (bytes_read > 0) {
                write(client_socket, buffer, bytes_read); // Enviar la salida al cliente
            } else {
                write(client_socket, "No output from command.\n", 24); // Mensaje si no hay salida
            }

            close(fd[0]); // Cerrar el extremo de lectura del pipe
        }
    }

    close(client_socket); // Cerrar el socket del cliente
    return NULL;
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);

    // Crear el socket del servidor
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error al crear socket");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Enlazar el socket
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error al enlazar el socket");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones entrantes
    if (listen(server_socket, 5) < 0) {
        perror("Error al escuchar");
        close(server_socket);
        exit(EXIT_FAILURE);
    }

    printf("Servidor escuchando en el puerto %d...\n", PORT);

    while (1) {
        // Aceptar una nueva conexión
        client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_size);
        if (client_socket < 0) {
            perror("Error al aceptar conexión");
            continue;
        }
        
        printf("Cliente conectado.\n");

        // Crear un hilo para manejar al cliente
        pthread_t thread_id;
        thread_arg* t_arg = malloc(sizeof(thread_arg)); // Reservar memoria para los argumentos
        t_arg->client_socket = client_socket; // Asignar el socket del cliente

        if (pthread_create(&thread_id, NULL, handle_client, t_arg) != 0) {
            perror("Error al crear hilo");
            close(client_socket);
            free(t_arg);
        }
        pthread_detach(thread_id); // Desvincular el hilo
    }

    close(server_socket); // Cerrar el socket del servidor
    return 0;
}