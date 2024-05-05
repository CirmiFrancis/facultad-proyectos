/*
 * shell2.c
 * 
 * shell primitivo en foreground
 * soporta argumentos en los comandos y cualquier cantidad de espacios
 * intermedios entre los argumentos del comando
*/

#include <stdio.h>
#include <stdlib.h> // POR ALGÚN MOTIVO, ESTE NO ES NECESARIO.
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define LOOP_JROMER 1
#define LOOP_GRCHERE strcmp(comando,"fin") != 0

int main(int argc, char **argv)
{
	char comando[256];
	do {
		printf("$$>");
		fgets(comando, 256, stdin);
		comando[strlen(comando)-1]='\0';
		if ( strcmp(comando,"fin") != 0 ) {
			// es un comando a ejecutar!
			pid_t pid = fork();
			if ( pid == 0 ) {
				// proceso hijo
				// exec
				// Esta parte analiza el comando ingresado por el usuario y dividirlo en una serie de argumentos que pueden ser pasados a la función execvp(), la cual ejecuta un programa con los argumentos especificados.
				int i, ii=0, z=0, w; 
				// variables.  
				// 'i' funciona como índice para recorrer el comando ingresado
				// 'ii' se usa como índice para construir cada palabra del comando
				// 'z' se usa como índice para el arreglo argv que almacenará los argumentos del comando
				// 'w' se usa como índice para iterar a través de argv al final del bucle
				i=0;
				char *argv[256];
				do { // El bucle do-while continúa hasta que se procesen todos los argumentos o se alcance el límite de 255 argumentos
					char palabra[256]; // Se declara un arreglo de caracteres 'palabra' de tamaño 256, que se utilizará para almacenar cada palabra del comando
					ii=0; // ii se reinicia a 0 al inicio de cada iteración del bucle interno
					// Se entra en un bucle while interno que recorre el comando ingresado (a partir de la posición i) hasta encontrar un espacio en blanco o el final del comando. Mientras tanto, se copian los caracteres uno por uno desde el comando a la palabra actual y se incrementan los índices i e ii
					while(comando[i] && comando[i] != ' ' && ii < 256) {
						palabra[ii] = comando[i];
						i++;ii++;
					}
					palabra[ii]='\0'; // Se agrega el carácter nulo al final de la palabra para marcar su fin
					argv[z] = strdup(palabra); // Se asigna un duplicado de la palabra al elemento argv[z] del arreglo de argumentos argv. Esto se hace utilizando strdup(), que asigna memoria y copia la cadena
					z++; // Se incrementa el índice z para pasar al siguiente elemento del arreglo argv
					while(comando[i] && comando[i] == ' ') i++; // salteo los espacios que separan a los argumentos del comando
				} while(comando[i] && z < 255);
				argv[z] = NULL; // indica el final de la lista de argumentos, como lo requiere la función execvp().
				
				// trace, chequeo que funciona el parsing
				//for(w=0;w<256 && argv[w];w++) printf("argv[%d]=[%s]\n",w,argv[w]);
				
				int rc = execvp(argv[0], argv);
				printf("comando [%s] no existe!!\n", comando);
				// libero la memoria solicitada por strdup()
				for(w=0; w<256 && argv[w]; w++) free(argv[w]); // se realiza un bucle para liberar la memoria asignada a cada argumento del comando utilizando la función free()
				exit(rc);
			} 
			else {
				// proceso padre, shell
				int estado=0;
				pid_t pid_hijo = wait(&estado);
				printf("PID %d finalizado con retorno %d\n", pid_hijo, estado/256);
			}
		}
	} while(LOOP_GRCHERE);
	return 0;
}

// Algunos comandos:

// ls | mostrará el contenido del directorio actual
// pwd | mostrará la ruta del directorio actual
// echo | su función principal es imprimir texto en la salida estándar

// ps | muestra los procesos en ejecución del usuario actual en formato corto, asociados al terminal
// ps -l | muestra los procesos en ejecución del usuario actual en formato largo, asociados al terminal
// ps ax | muestra TODOS los procesos (de todos los usuarios) en formato corto, incluyendo los que no están asociados al terminal
// ps -ax | similar al anterior
// ps -lax | similar al anterior pero en formato largo
// fin | es un comando personalizado, finaliza la ejecuión del programa



// Este código es similar al anterior con la diferencia de que ahora acepta argumentos.
//	* Se crea un proceso hijo utilizando fork(). El proceso hijo ejecutará el comando ingresado por el usuario utilizando la función execvp(). Antes de eso, se analiza el comando ingresado y se dividen los argumentos para execvp().
//	* Si execvp() falla, el proceso hijo imprimirá un mensaje indicando que el comando no existe y saldrá con el código de retorno de execvp().
//	* El proceso padre espera a que el proceso hijo termine utilizando wait(), y luego imprime el estado de salida del proceso hijo.

// En resumen, este programa permite al usuario ingresar comandos simples como si estuviera usando un intérprete de comandos en la línea de comandos, y los ejecuta utilizando llamadas al sistema fork() y execvp().