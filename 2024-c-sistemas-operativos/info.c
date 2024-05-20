#include <stdio.h> 
// Este encabezado proporciona las declaraciones para las funciones de entrada y salida estándar, como printf() y scanf().

#include <stdlib.h> 
// Este encabezado proporciona prototipos para funciones de gestión de memoria dinámica, como malloc() y free(), así como otras funciones y macros útiles. Si planeas usar funciones relacionadas con la gestión de memoria dinámica, necesitarás incluir este encabezado. 

#include <sys/types.h> 
// Este encabezado define varios tipos de datos que se utilizan en llamadas al sistema. Algunos de los tipos de datos comunes definidos en este encabezado incluyen pid_t (para identificadores de proceso en sistemas UNIX), uid_t y gid_t (para identificadores de usuario y grupo, respectivamente), entre otros.

#include <unistd.h> 
// Este encabezado proporciona prototipos para funciones estándar de Unix, como fork(), exec(), getpid(), etc. Si tu programa realiza llamadas al sistema relacionadas con la administración de procesos, como la creación de nuevos procesos o la obtención del identificador de proceso actual, necesitarás incluir este encabezado.

#include <sys/wait.h> 
// Este encabezado proporciona la función wait(), que se utiliza para esperar a que los procesos hijos terminen, evitando procesos huérfanos. También recogen el estado de salida del proceso hijo que ha terminado, evitando procesos zombies.

#include <sys/stat.h> 
// Este encabezado proporciona declaraciones de funciones y tipos de datos para la obtención de información sobre archivos, como los permisos de archivos, el tamaño, la marca de tiempo, etc. Por ejemplo, la estructura struct stat se define en este encabezado y se utiliza para almacenar información sobre un archivo después de llamar a la función stat(). 

#include <fcntl.h> 
// Este encabezado proporciona constantes y macros utilizadas para la manipulación de descriptores de archivo y el control de apertura de archivos. Por ejemplo, O_RDONLY, O_WRONLY, O_RDWR son constantes utilizadas para especificar los modos de apertura de archivos (lectura, escritura, lectura/escritura).

#include <string.h> 
// Este encabezado proporciona declaraciones de funciones y macros relacionadas con manipulación de cadenas (strings). Algunas de las funciones más comunes incluyen: strcpy(), strncopy(), strcat(), strncat(), strlen(), strcmp(), strncmp(), strstr(), strchr(), strrchr()

#include <signal.h> 
// Este encabezado proporciona declaraciones de funciones y macros relacionadas con el manejo de señales. Las señales son eventos asíncronos que pueden ser generados por el sistema operativo o por otros procesos, y pueden ser utilizadas para notificar a un proceso de eventos importantes, como errores, eventos de temporización, o solicitudes de terminación. Algunas de las funciones y macros comunes proporcionadas son: signal(), kill(), sigaction(), sigemptyset(), sigfillset(), sigaddset(), sigdelset(), SIGINT, SIGTERM, SIGKILL

/*
 * ls -l ... Lista el contenido del directorio actual en formato detallado.
 * ps ... Muestra una lista de procesos en ejecución en el sistema. La información es básica.
 * ps -l ... Muestra una lista de procesos en formato largo. Proporciona más detalles sobre los procesos, como el ID del proceso (PID)
 * ps -lax ... Muestra una lista de todos los procesos en formato largo, incluyendo aquellos de todos los usuarios en el sistema. La opción -a muestra todos los procesos y la opción -x muestra también los procesos que no están asociados con una terminal. 
 * ps ax ... Similar al anterior, muestra una lista de todos los procesos en formato corto, incluyendo aquellos de todos los usuarios en el sistema.
 * fin ... Parece un comando personalizado que usa el profesor.

 * $ gcc -Wall -o abc1 abc1.c ... Esta línea de comando compila el archivo abc1.c utilizando GCC (compilador), muestra todas las advertencias durante la compilación (-wall) y genera un ejecutable llamado abc1 (-o abc1)

 * - IR AL DIRECTORIO -
 * cd ...
 * 
 * - COMPILAR Y CREAR EJECUTABLE -
 * gcc -o programa programa.c
 * gcc -Wall -o programa programa.c
 *
 * - EJECUTAR -
 * ./programa
*/

/*
 * 'return 0;' indica que el programa se completó exitosamente
 * '%d' especifica que el valor es número entero 
 * '%f' especifica que el valor es número flotante 
 * '%c' especifica que el valor es un caracter 
 * '%s' especifica que el valor es una cadena de texto
 * '\n' inserta una nueva línea en la salida
*/

/*
 'int main(int argc, char **argv)' aunque los parámetros no son necesarios, incluirlos en la declaración de la función main es una práctica común y no causa ningún problema incluso si el programa no los utiliza. 

 'argc' significa 'argument count' e indica la cantidad (int) de argumentos que se pasan al programa desde la línea de comandos cuando se ejecuta.

 '**argv' significa 'argument vector'. Cada elemento en argv es una cadena de caracteres (char) que representa uno de los argumentos pasados al programa. 
 Respecto al doble asterisco (**), indica un puntero a un puntero. Se utiliza para representar un puntero a un array de punteros a cadenas de caracteres. Cada elemento en argv es un puntero a una cadena de caracteres (un char *), y argv en sí mismo es un puntero a un array de estos punteros.
*/

/*
FORK & PID
 fork(): es una llamada al sistema en sistemas Unix y sistemas similares que se utiliza para crear un nuevo proceso. Después de que fork() es llamado, el proceso original se bifurca en dos procesos separados: el proceso padre y el proceso hijo. Ambos procesos tienen su propio espacio de memoria, registros, ID de proceso, y otros atributos del proceso, pero comparten el mismo código de programa.
 fork()^n => 2^n

 pid_t: es un tipo de datos utilizado para almacenar IDs de procesos en C.

 pid: es una variable que almacena el resultado de la llamada al sistema fork(). Después de llamar a fork(), pid contendrá el ID del proceso hijo en el proceso padre y 0 en el proceso hijo. 
*/

/*
 ADVERTENCIA: 
 A veces el getppid() devuelve 1, y esto significa que el proceso padre del proceso actual ya no existe y el proceso init (pid=1) se convierte en el padre del proceso actual. Esto puede ocurrir si el proceso padre terminó su ejecución antes de que el proceso actual llamara a getppid().
 Para evitar esto se utiliza wait(0).
*/

/*
    Proceso Huérfano:
        Un proceso huérfano es un proceso hijo cuyo proceso padre ha terminado antes que él. El proceso huérfano sigue ejecutándose, pero su padre ya no está presente para esperarlo o manejar su estado.

    Proceso Zombie:
        Un proceso zombie es un proceso hijo que ha terminado de ejecutarse, pero su entrada aún permanece en la tabla de procesos del sistema operativo (consumiendo recursos del sistema). Esto sucede cuando el proceso padre no ha llamado a la función wait() o waitpid() para obtener el estado de salida del proceso hijo después de que termina.

        Un proceso hijo termina su ejecución y devuelve un valor de salida normalmente. El problema que lleva a la generación de procesos zombie no radica en la falta de salida del proceso hijo, sino en la falta de recolección de esta salida por parte de su proceso padre.

    En resumen, la diferencia clave radica en el estado del proceso hijo después de que su proceso padre termina. 
    Un proceso huérfano sigue ejecutándose sin un proceso padre vivo, mientras que un proceso zombie ha terminado su ejecución pero su estado de salida no ha sido recogido por su proceso padre.
*/