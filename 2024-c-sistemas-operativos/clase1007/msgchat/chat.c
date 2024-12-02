/*
 * chat.c
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
 * cola de mensajes chat 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include "data.h"

int main(int argc, char **argv) {
	printf("main(): Requiere cola de mensajes 0xA previamente creada\n");
	printf("main(): Requiere dos archivos fifo's previamente creados\n");
	printf("main(): Tipee 'fin' para terminar chat\n");
	printf("main(): $ chat <fifoE> <fifoR>\n");
	if ( argc != 3 ) {
		printf("forma de uso:\n$ chat <fifoE> <fifoR>\n"); exit(1);
	}
	int cola = msgget(0xA,0);
	if ( cola == -1 ) { 
		printf("Error en aperta de cola de mensajes\n");
		return 2;
	}
	mensaje m;
	pid_t escritor = fork();
	if ( escritor  ) {
		pid_t lector = fork();
		if ( lector ) {
			printf("main(): espero por finalizacion de procesos\n");
			wait(0);
			wait(0);
			printf("main(): fin!\n");
		} else {
			// lector
			int fd = open(argv[2],O_RDONLY);
			pid_t p;
			read(fd,&p,sizeof(pid_t));
			close(fd);
			
			m.tipo = (long) p; // nro de cola de mensaje
			int ret;
			do {
				ret = msgrcv(cola,&m,64,m.tipo,0); // msgrcv bloqueante, lee de cola #1, 5to argumento IPC_NOWAIT
				if ( ret != -1 ) {
					printf("<%s",m.msg);
					if ( strncmp(m.msg,"fin",3) == 0 ) ret=-1;
				} else printf("Error en lectura, ret=%d\n",ret);
			} while(ret != -1);	
			printf("fin lector!\n");	
			
		}
	} else {
		// escritor
		int fd = open(argv[1],O_WRONLY);
		pid_t p = getpid();
		write(fd,&p,sizeof(pid_t));
		close(fd);

		m.tipo = (long) getpid(); // nro de cola de mensaje
		int ret;
		do {
			printf(">");fgets(m.msg,64,stdin);
			ret = msgsnd(cola,&m,64,0); // msgsnd NO bloqueante, 4to argumento IPC_NOWAIT
			if ( strncmp(m.msg,"fin",3) == 0 ) ret=-1;
		} while(ret != -1);	
		printf("fin escritor!\n");	
	}
	return 0;
}

