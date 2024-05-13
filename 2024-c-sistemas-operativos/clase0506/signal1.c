/*
 * signal1.c
 * 
 * Prueba de envio de senal a grupo de procesos kill(0,..)
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

void sig_usr1(int signo);

int main(int argc, char **argv)
{
	int i;
	signal(SIGUSR1,sig_usr1);
	printf("main(): PID %d\n",getpid());
	for(i=0;i<5;i++) {
		pid_t pid = fork();
		if ( pid == 0 ) {
			//signal(SIGUSR1,sig_usr1);
			printf("proceso %d hijo de %d creado y bloqueado en pause()!\n",getpid(),getppid());
			pause();
			printf("proceso %d hijo de %d fin!\n",getpid(),getppid());
			return 0;
		}
	}
	printf("main(): PID %d group %d\n",getpid(),getpgrp());
	printf("main(): envio senal SIGUSR1 luego de esperar 5 segundos\n");
	sleep(5);
	kill(0,SIGUSR1);
	printf("main(): entro en loop wait()\n");
	pid_t pidh;
	while((pidh=wait(NULL)) > 0) printf("main(): PID %d ha finalizado!\n",pidh);
	printf("main(): fin!\n");
	return 0;
}

void sig_usr1(int signo) {
	printf("sig_usr1(%d): PID %d PID group %d\n",signo,getpid(),getpgrp());
}