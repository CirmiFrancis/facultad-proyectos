/*
 * server_comando.c
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
 * $ gcc -Wall -o serverc server_comando.c
 * servidor socket que recibe comando, lo ejecuta y devuelve la salida
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

int cuento_comando(char *buffer);
void copio_comando(char *args[],int nargs,char *buffer);
void reemplazo(char *buffer,char busco,char reemplazo);

int main(int argc, char **argv) {
	int sock = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in s;
	s.sin_family = AF_INET;
	s.sin_port = htons(8282); // puerto tcp/ip en donde escuchara peticiones este servidor
	s.sin_addr.s_addr = inet_addr("127.0.0.1"); // direccion local del servidor
	memset(s.sin_zero,0,8); // por culpa de Berkeley!
	socklen_t slen = sizeof(struct sockaddr_in);
	bind(sock,(struct sockaddr *) &s,slen);
	printf("server: espendando comandos en 127.0.0.1:8282\n");
	listen(sock,0);
	while(1) {
		int sockcli = accept(sock,(struct sockaddr *) &s,&slen);
		if ( sockcli != -1 ) {
			while(1) { // loop romerizado para atender hasta que el cliente diga "fin"
				// tengo un cliente conectado!!
				// espero recibir algo del cliente
				char buffer[2048];
				int rbytes = recv(sockcli,buffer,2047,0);
				if ( rbytes != -1 ) {
					buffer[rbytes]='\0';
					if ( strncmp(buffer,"fin",3) == 0 ) {
						// el cliente se quiere ir, deja la conexion y deja de enviar comandos
						close(sockcli);
						break;
					}

					// quito caracteres raros del comando
					reemplazo(buffer,'\n',' ');
					reemplazo(buffer,'\r',' ');
					reemplazo(buffer,'\t',' ');

					// envio un comando
					int nc = cuento_comando(buffer);
					if ( nc == 0 ) {
						// comando invalido
						strcpy(buffer,"comando invalido\n");
						send(sockcli,buffer,strlen(buffer),0);
						printf("server: envie 'comando invalido' a cliente\n");
						continue;
					}

					//trace
					//int i=0;
					//while(buffer[i]) { printf("server: buffer[%d]=%c\n",i,buffer[i]);i++; }
					
					char *myargv[nc+1];
					myargv[nc]=NULL;
					copio_comando(myargv,nc+1,buffer);
					
					//trace
					//printf("server: nc=%d\n",nc);
					//for(i=0;i<nc+1;i++) printf("server: myargv[%d]=[%s]\n",i,myargv[i]);
					
					int fd[2];
					pipe(fd);
					if ( fork() ) { // proceso padre lee la salida del proceso hijo
						close(fd[1]);
						char hbuffer[256];
						int n=0;
						while((n=read(fd[0],hbuffer,255))) {
							hbuffer[n]='\0';
							//printf("server: recibi [%s]\n",hbuffer);
							send(sockcli,hbuffer,strlen(hbuffer),0);
						}
						printf("server: espero a fin de hijo\n");
						wait(0);
						close(fd[0]);
					} else {
						dup2(fd[1],STDOUT_FILENO); // stdout <=> fd[1]
						close(fd[0]);
						execvp(myargv[0],myargv);
						printf("Error en ejecucion de comando [%s]\n",myargv[0]);
						close(fd[1]);
						exit(1);
					}
					
				} else {
					printf("server: error de lectura de cliente\n");
					//dejo de atender a cliente y salgo de loop
					close(sockcli);
					break;
				}
			} // fin while(1) de atencion cliente
		} else {
			printf("server: error en accept!\n");
		}
	}
	return 0;
}




// devuelve la cantidad de elementos que necesito para ejecutar el comando con execvp()
// ejemplo:  "ls -l"   devuelve 2
// ejemplo:  "ls     -l    -a" devuelve 3
// ejemplo:  "     ls     " devuelve 1
// ejemplo: "         " devuelve 0
// ejemplo: "" devuelve 0
int cuento_comando(char *buffer) {
	int i=0,nc=0;
	if ( buffer == NULL ) return 0;
	while(buffer[i]) {
		while(buffer[i] && buffer[i] == ' ') i++;
		if ( buffer[i] ) {
			nc++;
			while(buffer[i] && buffer[i] != ' ') i++;
		}
	}
	return nc;
}


/*
 toma el contenido de buffer ej "   ls    -l   "
 y hace lo siguiente:
 args[0] -> "ls"
 args[1] -> "-l"
 es decir, los elementos del arreglo apuntan a cadenas que contienen las partes del comando
*/
void copio_comando(char *args[],int nargs,char *buffer) {
	int i=0,nc=0;
	if ( buffer == NULL ) return;
	while(buffer[i] && nc < nargs) {
		while(buffer[i] && buffer[i] == ' ') i++;
		if ( buffer[i] ) {
			char tcmp[256];
			int z=0;
			while(buffer[i] && z < 256 && buffer[i] != ' ' ) {
				tcmp[z]=buffer[i];
				z++;
				i++;
			}
			tcmp[z]='\0';
			args[nc] = strdup(tcmp);
			nc++;
		}
	}
}

// busco el caracter busco en buffer y lo reemplazo por reemplazo
void reemplazo(char *buffer,char busco,char reemplazo) {
	int i=0;
	if ( buffer == NULL ) return;
	while(buffer[i]) {
		if ( buffer[i] == busco ) buffer[i] = reemplazo;
		i++;
	}
}

