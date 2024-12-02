/*
 * wmififo.c
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
 * Simple escritor en ./mififo
 * Previamente crear ./mififo con $ mkfifo mififo
 * compilar:
 * $ gcc -Wall -o wmififo wmififo.c rand.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "data.h"

int main(int argc, char **argv)
{
	printf("main(%s): voy a abrir ./mififo\n",argv[0]);
	int fd = open("mififo",O_WRONLY); // <longitud de mensaje><mensaje>
	printf("main(%s):  abri ./mififo fd=%d\n",argv[0],fd);
	t_venta venta;
	int i;
	int largo = sizeof(t_venta);
	for(i=0;i<50;i++) {
		// genero datos de venta
		venta.fecha.dia = irnd(1,31);
		venta.fecha.mes = irnd(1,12);
		venta.fecha.anio = 2024;
		venta.monto = (double) irnd(10000000,100000000)/100.0;
		venta.sucursal = irnd(1,10);
		printf("main(%s): voy a grabar en ./mififo\n",argv[0]);
		int n1 = write(fd,&largo,sizeof(int));
		printf("main(%s): voy a grabar en ./mififo\n",argv[0]);
		int n2 = write(fd,&venta,sizeof(t_venta));
		printf("main(%s): grabe %d bytes en ./mififo, %d bytes en ./mififo\n",argv[0],n2,n1);
	}
	close(fd);
	return 0;
}

