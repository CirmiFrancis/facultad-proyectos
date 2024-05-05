/*
 * shell1.c
 * 
 * Copyright 2024 osboxes <osboxes@osboxes>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * shell primitivo en foreground
 * no soporta argumentos en los comandos
*/

// Este código es un intérprete de comandos básico que se ejecuta en primer plano o en "foreground". El término "foreground" se utiliza para describir el estado en el que un proceso está activo y en ejecución en la interfaz de usuario principal, y el usuario interactúa directamente con él, a diferencia del "background" donde el proceso se ejecuta en segundo plano y puede seguir ejecutándose mientras el usuario interactúa con otros procesos.
// Funciona como una especie de shell básica en C.
// *IMPORTANTE* Solo acepta comandos sin espacios de por medio (en otras palabras, sin argumentos). Por lo que 'ps' funciona pero 'ps ax' no.

#include <stdio.h>
#include <stdlib.h> // POR ALGÚN MOTIVO, ESTE NO ES NECESARIO
#include <unistd.h>
#include <string.h> // Este encabezado proporciona declaraciones de funciones y macros relacionadas con manipulación de cadenas (strings). Algunas de las funciones más comunes incluyen: strcpy(), strncopy(), strcat(), strncat(), strlen(), strcmp(), strncmp(), strstr(), strchr(), strrchr()
#include <sys/types.h>
#include <sys/wait.h>

// Directivas de preprocesador en C, que se utilizan para definir macros
// Las macros permiten la creación de código más eficiente, legible y mantenible en C (y otros lenguajes de programación), e vitnado el código repetido y optimizándolo. Los nombres de las directivas no pueden: comenzar con un número, contener espacio, contener un guión medio
#define LOOP_JROMER 1 // Cuando se encuentra esta macro en el código, será reemplazada por el valor 1 antes de que el compilador procese el código
#define LOOP_GRCHERE strcmp(comando,"fin") != 0 // Lo que hace es usar la función strcmp para comparar la cadena comando con la cadena "fin". Si la comparación no resulta en igualdad (es decir, si la cadena comando es diferente de "fin"), la expresión será verdadera (devolverá un valor distinto de cero), de lo contrario, será falsa (devolverá 0)

int main(int argc, char **argv)
{
	char comando[256]; // [256] es la longitud del array, es decir, cuántos caracteres puede contener. En este caso, el array comando puede contener hasta 256 caracteres, incluyendo el carácter nulo \0 que marca el final de la cadena en C
	do {
		printf("$$>"); // indicador de comandos
		fgets(comando, 256, stdin); // lee una línea de texto desde la entrada estándar (stdin) y la almacena en el array comando
		//fgets() permite leer toda la línea, en cambio, scanf() automáticamente delimita la cadena en función de los espacios en blanco. Es decir, el comando 'ps ax', fgets() devuelve 7 caracteres: ('p','s',' ','a','x','\n','\0'), y scanf() devuelve 3 caracteres: ('p','s','\0'), ya que solo toma 'ps'.
		// IMPORTANTE: a la cadena de caraceres se le suman al final
		// '\n' el caracter de nueva linea, el cual se agrega solo cuando la cadena tiene espacios en blanco
		// '\0' el caracter nulo para representar el fin de la cadena
		comando[strlen(comando) - 1] = '\0'; // NO TERMINO DE ENTENDER BIEN CÓMO FUNCIONA PERO ES NECESARIA. ¿Para qué quiero agregar un '\0' al final de la cadena si la función fgets() ya lo agrega por sí sola?
		if ( strcmp(comando, "fin") != 0 ) { // creo que puedo reemplazarlo por LOOP_GRCHERE
			// es un comando a ejecutar!
			pid_t pid = fork();
			if ( pid == 0 ) {
				// proceso hijo
				// exec
				// reemplaza el proceso hijo con un nuevo programa utilizando la función execlp(), que busca y ejecuta el comando especificado. Si el comando no existe, imprime un mensaje de error
				int rc = execlp(comando, comando, NULL); // es una función que se utiliza para ejecutar un programa desde un archivo. En general, los primeros 2 argumentos son iguales, ya que indican el Nombre del programa que se desea ejecutar (ruta) y el Nombre del programa que se ejecutará. Luego se pasa un NULL para indicar que no hay más argumentos
				printf("comando [%s] no existe!!\n", comando);
				exit(rc);
			} 
			else {
				// proceso padre, shell
				// esperamos a que el proceso hijo termine su ejecución utilizando la función wait()
				int estado = 0; // almacena el estado de salida del proceso hijo
				pid_t pid_hijo = wait(&estado); // pid_hijo contendrá el ID del proceso hijo que terminó. 'wait(&estado)' espera a que CUALQUIER proceso hijo termine, y es el mismo 'wait' el que modifica el valor de 'estado' para contener información sobre el estado de finalización del proceso hijo
				printf("PID %d finalizado con retorno %d\n", pid_hijo, estado/256); // imprime el ID del proceso hijo y el valor de retorno (si es distinto de cero) dividido por 256
				// estado/256 == 0: El proceso hijo terminó exitosamente y devolvió un estado de salida de 0
				// estado/256 == 255: El proceso hijo terminó debido a una señal y el valor de retorno específico dependerá de la señal que causó su terminación
			}
		}
	} while(LOOP_GRCHERE); // el ciclo sigue mientras que la comparación sea verdadera
	return 0;
}

// Algunos comandos:

// ls | mostrará el contenido del directorio actual
// pwd | mostrará la ruta del directorio actual
// echo | su función principal es imprimir texto en la salida estándar

// ps | muestra los procesos en ejecución del usuario actual en formato corto, asociados al terminal
// fin | es un comando personalizado, finaliza la ejecuión del programa



// Este código hace lo siguiente:
// 	* Agregamos macros para utilizarlos posteriormente (es similar a declarar variables)
//	* Declaramos una variable llamada 'comando' que contenga un array de caracteres para guardar los comandos escritos por el usuario
// 	* Dentro de un ciclo do-while, imprimimos en pantalla un 'indicador de comandos' para que el usuario escriba un comando. La condición del ciclo es que finaliza una vez que el comando sea "fin"
//	* El sistema lee el comando ingresado y lo almacena con fgets()
//	* Se agrega un fin de cadena '\0' y utiliza un if para preguntar y asegurar que el comando sea distinto a "fin"
//	* Si es distinto, se usa un fork() y se guarda el pid del hijo
//	* Luego, se utiliza un if-else para dividir las tareas del proceso hijo y del proceso padre
//	* El proceso hijo, utilizando la función execlp(), es reemplazado por un nuevo programa que ejecuta el comando escrito y lo devuelve como salida. En caso de no existir el comando, se imprime un mensaje error
//	* El proceso padre declara una variable 'estado' y una variable 'pid_hijo'. En la segunda se esperará a cualquier proceso hijo que finalice su ejecución para guardar su pid, y a su vez modificará la variable 'estado', guardando en esta el estado de salida de ese proceso hijo. Por último, se imprime un texto que contiene el PID del hijo y el estado de salida
//	* Finalmente, luego del ciclo do-while, se hace un 'return 0;'