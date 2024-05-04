/*
 * abc5.c
 * 
 * padre graba abcedario en mayusculas
 * hijo graba un abcedario en minusculas
 * solo se graba 1 abecedario
 * se usa un sistema de punteros, guardando la posicion
 * el padre graba en posiciones pares y el hijo en posiciones impares
*/

#include <stdio.h>
#include <stdlib.h> // POR ALGÚN MOTIVO, ESTE NO ES NECESARIO.
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h> // POR ALGÚN MOTIVO, ESTE NO ES NECESARIO.
#include <fcntl.h>

int main(int argc, char **argv)
{
	// creo archivo
	int fd = open("abecedario", O_TRUNC | O_CREAT, 0777);
	close(fd);
	
	char letra = 'A', letra_hijo = 'b';
	pid_t pid = fork();

	if ( pid == 0 ) {
		// proceso hijo
		fd = open("abecedario", O_RDWR, 0777);
		long posicion = 1L; // 1L es una buena práctica para indicar que es del tipo 'long'. Este tipo de dato ocupa más espacio en la memoria, lo que permite almacenar números enteros más grandes que un 'int'
		// escribir un abecedario
		while(letra_hijo <= 'z') {
			lseek(fd, posicion, SEEK_SET);
			write(fd, &letra_hijo, 1);
			letra_hijo += 2; // letra_hijo = letra_hijo + 2;
			posicion += 2;
		}
	} 
	else {
		// proceso padre
		fd = open("abecedario", O_RDWR, 0777);
		long posicion = 0L;
		// escribir un abecedario
		while(letra <= 'Z') {
			lseek(fd, posicion, SEEK_SET);
			write(fd, &letra, 1);
			letra += 2;
			posicion += 2;
		}
	}
	close(fd);
	return 0;
}

// Se crea un archivo 'abecedario'
// Se crean 3 variables: 2 char para las letras y 1 pid_t para guardar el pid del fork()
// Hay 2 caminos en el if-else: el del proceso hijo y el del proceso padre
// - El proceso hijo abre el archivo 'abecedario' en modo lectura y escritura (O_RDWR) y se inicializa una variable 'posicion' para rastrear la posición actual en el archivo. Dentro del bucle while, el proceso hijo escribe las letras minúsculas del alfabeto comenzando desde 'b' en posiciones impares en el archivo. Esto se logra utilizando lseek() para mover el puntero de archivo a una posición específica (posicion) y luego escribir la letra en esa posición utilizando write(). Después de escribir la letra, se incrementa la posición en 2 para que la siguiente escritura sea en la posición siguiente impar
// - El proceso padre abre el archivo 'abecedario' en modo lectura y escritura (O_RDWR) y se inicializa una variable 'posicion' para rastrear la posición actual en el archivo. Dentro del bucle while similar al del proceso hijo, el proceso padre escribe las letras mayúsculas del alfabeto comenzando desde 'A' en posiciones pares en el archivo. También utiliza lseek() y write() para escribir las letras en posiciones específicas y luego incrementa la posición en 2 para la siguiente escritura
// Finalmente, se cierra el descriptor de archivo (close(fd)) y se retorna 0, indicando que el programa finalizó correctamente