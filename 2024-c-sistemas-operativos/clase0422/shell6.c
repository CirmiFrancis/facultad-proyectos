/*
 * shell6.c
 * 
 * shell primitivo en foreground
 * soporta argumentos en los comandos y cualquier cantidad de espacios
 * intermedios entre los argumentos del comando
 * 
*/

#include <stdio.h>
#include <stdlib.h> // POR ALGÚN MOTIVO, ESTE NO SE NECESARIO.
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define LOOP_JROMER 1
#define LOOP_GRCHERE strcmp(comando,"fin") != 0

//funciones
void ingreso_comando(const char *prompt,char *cmd,int largo_cmd);
int parsing_comando(char *cmd, char *arg[],int largo_arg);
void trace_parsing(char *arg[],int largo_arg);
void libero_parsing(char *arg[],int largo_arg);
void ejecuto_foreground(char *arg[],int largo_arg);  // ejecuta comando y queda a la espera de la finalizacion del proceso

//funciones para el manejo de se#ales  
void sig_child(int);
void sig_int(int);

int main(int argc, char **args) {
	char comando[256];
	char *argv[256];
	// voy a ejecutar a sig_child() cada vez que reciba la senal SIGCHLD
	signal(SIGCHLD,sig_child);
	signal(SIGINT,sig_int);
	do {
		ingreso_comando("$$>",comando,256);
		int n = parsing_comando(comando,argv,256);
		trace_parsing(argv,n);

		//si no hay comando, vuelvo al prompt
		if ( strcmp(argv[0],"") == 0 ) continue; // presiono ENTER
		
		if ( strcmp(argv[0],"cd") == 0 ) { // comando interno cd
			if ( argv[1] == NULL ) {
				printf("debe indicar directorio!\n");
				continue;
			}
			chdir(argv[1]);
		} else if ( strcmp(comando,"fin") != 0 ) {
			// es un comando a ejecutar!
			ejecuto_foreground(argv,n);
		}
	} while(LOOP_GRCHERE);
	return 0;
}

// implemento funciones

void ingreso_comando(const char *prompt,char *comando,int largo_cmd) {
	printf("%s",prompt);
	fgets(comando,largo_cmd,stdin);
	comando[strlen(comando)-1]='\0'; // reemplaza \n por \0
}

/**
 * cmd comando a parsear, cada comando se separa por espacios
 * arg[] arreglo de punteros a char * por cada parte del comando
 * largo_arg cantidad de elementos que tiene el arreglo arg
 * Devuelve la cantidad de elementos cargados en arg[]
 */
int parsing_comando(char *comando, char *argv[],int largo_arg) {
	int i,ii=0,z=0;
	i=0;
	memset(argv,0,sizeof(char *)*largo_arg);
	//for(w=0;w<largo_arg;w++) argv[w]=NULL;

	// salteo los espacios que separan a los argumentos del comando
	while(comando[i] && comando[i] == ' ') i++;
	do {
		char palabra[256];
		ii=0;
		while(comando[i] && comando[i] != ' ' && ii < 256) {
			palabra[ii] = comando[i];
			i++;ii++;
		}
		palabra[ii]='\0';
		argv[z] = strdup(palabra);
		z++;
		// salteo los espacios que separan a los argumentos del comando
		while(comando[i] && comando[i] == ' ') i++;
	} while(comando[i] && z < 255);
	argv[z] = NULL;
	return z;
}

void trace_parsing(char *argv[],int largo_arg) {
	// trace, chequeo que funciona el parsing
	int w;
	for(w=0;w<largo_arg && argv[w];w++) printf("argv[%d]=[%s]\n",w,argv[w]);
}

/*
 * libero memoria apuntada por cada elemento no nulo de argv[]
 * previamente asignado por strdup()
 */
void libero_parsing(char *argv[],int largo_arg) {
	int w;
	// libero la memoria solicitada por strdup()
	for(w=0;w<largo_arg && argv[w];w++) free(argv[w]);
}

// ejecuta comando y queda a la espera de la finalizacion del proceso
void ejecuto_foreground(char *argv[],int largo_arg) {
	pid_t pid = fork();
	if ( pid == 0 ) {
		// proceso hijo
		// exec
		
		int rc = execvp(argv[0],argv);
		printf("comando [%s] no existe!!\n",argv[0]);

		// libero la memoria solicitada por strdup()
		libero_parsing(argv,largo_arg);
		exit(rc);

	} else {
		// proceso padre, shell
		int estado=0;
		pid_t pid_hijo = wait(&estado);
		printf("PID %d finalizado con retorno %d\n",pid_hijo,estado/256);

		// libero la memoria solicitada por strdup()
		libero_parsing(argv,largo_arg);
	}
} 

// handle de la se#al SIGCHLD
void sig_child(int signo) {
	printf("sig_child(): signo=%d finalizo un proceso hijo\n",signo);
}

// handle de la se#al SIGINT
void sig_int(int signo) {
	printf("sig_int(): signo=%d enviaron se#al de interrupcion\n",signo);
}