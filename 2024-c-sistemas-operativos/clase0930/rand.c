/*
 * rand.c
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
 * Genero numeros pseudo-random en un rango de valores enteros
 * para compilar:
 * $ gcc -Wall -o rand rand.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// genera numeros enteros pseudo-ramdom entre min y max, ambos inclusive
int irnd(int min,int max);

int main(int argc, char **argv) {
	srand(time(NULL));
	int i=0;
	while(i<10) {
		printf("#%d=%d \tirnd(%d,%d)\t=\t%d\n",i,rand(),i*10,i*100,irnd(i*10,i*100));
		i++;
	}
	return 0;
}

// genera numeros enteros pseudo-ramdom entre min y max, ambos inclusive
int irnd(int min,int max) {
	int r = max - min + 1;
	//printf("r=%d\n",r);
	return (rand() % r) + min;
}
