/*
 * escritor.c
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
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
	mensaje m;
	m.tipo = 1L; // nro de cola de mensaje
	int n=0,ret;
	do {
		// genero datos de venta
		m.venta.fecha.dia = irnd(1,31);
		m.venta.fecha.mes = irnd(1,12);
		m.venta.fecha.anio = 2024;
		m.venta.monto = (double) irnd(10000000,100000000)/100.0;
		m.venta.sucursal = irnd(1,10);
		ret = msgsnd(cola,&m,sizeof(t_venta),0); // msgsnd bloqueante, 4to argumento en cero
		n++;
		printf("Envie registro venta #%d, msgsnd retorna %d\n",n,ret);
	} while(ret != -1);	
	printf("fin escritor!\n");	
	return 0;
}

