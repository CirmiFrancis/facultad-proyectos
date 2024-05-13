/*
 * abc5.c
 * 
 * hijo1 graba abcedario en mayusculas
 * hijo2 graba un abcedario en minusculas
 * la secuencia de ejecucion es hijo1 hijo2 hijo1 hijo2 ... 
 * sincronizado con senales
 * 
 * compilar:
 * $ gcc -Wall -o abc5 abc5.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

void sig_usr1(int signo);
void sig_usr2(int signo);
void sig_usr1p(int signo);
void sig_usr2p(int signo);

int hijo1_listo=0,hijo2_listo=0;
int padre_a_hijo1=0, padre_a_hijo2=0;

int main(int argc, char **argv)
{
	signal(SIGUSR1,sig_usr1p);
	signal(SIGUSR2,sig_usr2p);

	// creo archivo
	int fd = open("abecedario",O_TRUNC|O_CREAT,0777);
	close(fd);
	
	printf("main(): inicio\n");

	pid_t pid1,pid2;
	pid1 = fork();
	if ( pid1 == 0 ) { // hijo1
		signal(SIGUSR1,sig_usr1);
		signal(SIGUSR2,SIG_DFL);
		pid_t mipid=getpid(), ppid = getppid();
		printf("PID %d creado!\n",mipid);
		// proceso hijo1
		char letra_hijo1 = 'A';
		fd = open("abecedario",O_RDWR,0777);
		long posicion = 0L;
		// listo para empezar!
		kill(ppid,SIGUSR1);
		// escribir un abecedario
		while(letra_hijo1 <= 'Z') {
			while(!padre_a_hijo1) sleep(1);
			padre_a_hijo1=0;
			lseek(fd,posicion,SEEK_SET);
			write(fd,&letra_hijo1,1);
			printf("PID %d grabe letra %c\n",mipid,letra_hijo1);
			letra_hijo1+=2; // letra_hijo = letra_hijo + 2;
			posicion+=2;
			kill(ppid,SIGUSR1);
		}
		close(fd);
		printf("PID %d fin!\n",mipid);
		exit(0);
	} else {
		// proceso padre
		pid2 = fork();
		if ( pid2 == 0 ) { // hijo2
			signal(SIGUSR2,sig_usr2);
			signal(SIGUSR1,SIG_DFL);
			pid_t mipid=getpid(), ppid = getppid();
			printf("PID %d creado!\n",mipid);
			char letra_hijo2 = 'b';
			fd = open("abecedario",O_RDWR,0777);
			long posicion = 1L;
			// listo para empezar!
			kill(ppid,SIGUSR2);
			// escribir un abecedario
			while(letra_hijo2 <= 'z') {
				while(!padre_a_hijo2) sleep(1);
				padre_a_hijo2=0;
				lseek(fd,posicion,SEEK_SET);
				write(fd,&letra_hijo2,1);
				printf("PID %d grabe letra %c\n",mipid,letra_hijo2);
				letra_hijo2+=2;
				posicion+=2;
				kill(ppid,SIGUSR2);
			}
			close(fd);
			printf("PID %d fin!\n",getpid());
			exit(0);
		}
	}
	// proceso padre
	printf("main(): esperando hijo1 y hijo2\n");
	while(!hijo1_listo) sleep(1);
	while(!hijo2_listo) sleep(1);
	printf("main(): fin espera de hijo1 y hijo2\n");
	
	printf("main(): inicio loop\n");
	char letra='a';
	while(letra<='z') {
		hijo1_listo=hijo2_listo=0;
		// comienza hijo1
		if ( kill(pid1,SIGUSR1) == 0 ) while(!hijo1_listo) sleep(1);
		// comienza hijo2
		if ( kill(pid2,SIGUSR2) == 0 ) while(!hijo2_listo) sleep(1);
		letra+=2;
	}
	printf("main(): fin loop!\n");
	wait(NULL);
	wait(NULL);
	printf("main(): fin padre!\n");
	return 0;
}

void sig_usr1(int signo) {
	// hijo 1 debe producir letra
	padre_a_hijo1=1;
}
void sig_usr2(int signo) {
	// hijo 2 debe producir letra
	padre_a_hijo2=1;
}
void sig_usr1p(int signo) {
	// hijo 1 esta listo para comenzar! (y le aviso al padre)
	hijo1_listo=1;
	printf("main(): recibi Ok para comenzar de hijo1\n");
}
void sig_usr2p(int signo) {
	// hijo 2 esta listo para comenzar! (y le aviso al padre)
	hijo2_listo=1;
	printf("main(): recibi Ok para comenzar de hijo2\n");
}