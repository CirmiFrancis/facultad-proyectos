/*
 * pipe5.c
 * 
 * $ gcc -Wall -o pipe5 pipe5.c
 * Idem pipe4 sin usar variable fd2
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
	int fd = open("salida.txt", O_WRONLY|O_CREAT|O_TRUNC, 0666);
	dup2(fd,5); // 5 => fd
	char *buf1 = "Hola Mundo!\n";
	int bw = write(5,buf1,strlen(buf1));
	//perror("error write ");
	printf("grabe %d bytes\n",bw);
	close(5);
	return 0;
}
