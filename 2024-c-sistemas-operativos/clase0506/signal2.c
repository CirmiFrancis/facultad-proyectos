/*
 * signal2.c
 * 
 * padre crea hijos en abanico y cada hijo escribe 5 letras del abecedario
 * cuando recibe SIGUSR1 que envio el padre a todo el grupo
 * cada hijo le envia al padre distintos tipos de senales para indicar que esta listo para recibir SIGUSR1
 * el padre ignora SIGUSR1 para no recibir el mismo dicha senal
 * el padre recibe todas las senales que envian los hijos
 * los hijos solo reciben SIGUSR1, el resto de senales heredadas hacen su labor por defecto en los hijos
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

void sig_usr1(int signo);
void sig_usr2(int signo);

char letra='a';
int nprocOk = 0;

int main(int argc, char **argv)
{
	signal(SIGUSR1,SIG_IGN);
	signal(SIGUSR2,sig_usr2);
	signal(SIGPIPE,sig_usr2);
	signal(SIGALRM,sig_usr2);
	signal(SIGFPE,sig_usr2);
	signal(SIGCONT,sig_usr2);
	int i;
	printf("main(): PID %d\n",getpid());
	for(i=0;i<5;i++) {
		pid_t pid = fork();
		if ( pid == 0 ) {
			signal(SIGUSR1,sig_usr1);
			signal(SIGUSR2,SIG_DFL);
			signal(SIGPIPE,SIG_DFL);
			signal(SIGALRM,SIG_DFL);
			signal(SIGFPE,SIG_DFL);
			signal(SIGCONT,SIG_DFL);
			letra+=(i*5);
			pid_t ppid = getppid();
			pid_t mipid = getpid();
			printf("proceso %d hijo de %d creado y bloqueado en pause()!\n",mipid,ppid);
			switch(i) {
				case 0:
					kill(ppid,SIGUSR2);
					break;
				case 1:
					kill(ppid,SIGPIPE);
					break;
				case 2:
					kill(ppid,SIGALRM);
					break;
				case 3:
					kill(ppid,SIGFPE);
					break;
				case 4:
					kill(ppid,SIGCONT);
					break;
				default:
					printf("proceso %d hijo de %d i=%d NO ENVIE signal!\n",mipid,ppid,i);
					break;
			}
			
			pause();
			printf("proceso %d hijo de %d fin!\n",getpid(),getppid());
			return 0;
		}
	}
	// padre espera por el ok de todos los hijos
	while(nprocOk < 5) sleep(1);
	sleep(1);// para asegurarme que todos los hijos estan bloqueados en pause()
	printf("main(): recibi nprocOk=%d ok de todos los procesos hijos\n",nprocOk);
	printf("main(): envio SIGUSR1 a todo el grupo de procesos\n");
	kill(0,SIGUSR1);
	printf("main(): entro en loop wait()\n");
	pid_t pidh;
	int nfin=0;
	while(nfin < 5 && (pidh=wait(NULL)) > 0) {
		printf("main(): PID %d ha finalizado!\n",pidh);
		nfin++;
	}
	printf("main(): fin!\n");
	return 0;
}

void sig_usr1(int signo) {
	int i;
	pid_t pid = getpid();
	for(i=0;i<5;i++,letra++) printf("sig_usr1(%d): PID %d letra=%c\n",signo,pid,letra);
}

void sig_usr2(int signo) {
	printf("sig_usr2(%d): PID %d nprocOk=%d\n",signo,getpid(),++nprocOk);
}