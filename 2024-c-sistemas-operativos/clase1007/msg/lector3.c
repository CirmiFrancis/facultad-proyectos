/*
 * lector3.c
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
 * lector2 cola de mensajes no bloqueante con msg_noerror para truncar
 * ultimo mensaje
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "data.h"

int main(int argc, char **argv) {
	int cola = msgget(0xA,0);
	if ( cola == -1 ) { 
		printf("Error en aperta de cola de mensajes\n");
		return 2;
	}
	mensaje2 m;
	m.tipo = 1L; // nro de cola de mensaje
	int n=0,ret;
	char m2[13];
	do {
		memset(&m.msg,0,12); // m.msg = 0
		ret = msgrcv(cola,&m,12,1L,IPC_NOWAIT); // msgrcv bloqueante, lee de cola #1, 5to argumento IPC_NOWAIT, trunca sin dar error
		if ( ret != -1 ) {
			memset(m2,0,13); // m2=0
			memcpy(m2,&m.msg[0],12); // m2 = m.msg
			n++;
			printf("Lei registro #%d %s\n",n,m2);
		} else printf("Error en lectura, ret=%d\n",ret);
	} while(ret != -1);	
	printf("fin lector!\n");	
	return 0;
}

