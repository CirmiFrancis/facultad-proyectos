/*
 * swap1.c
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
 * swap que no funciona
 */


#include <stdio.h>
#include <stdlib.h>

void swap(int,int);

int main(int argc, char **argv)
{
	int a = 7;
	int b = 8;
	printf("antes   a=%d b=%d\n",a,b);
	swap(a,b);
	printf("despues a=%d b=%d\n",a,b);
	return 0;
}

void swap(int a,int b) {
	int x = a;
	a = b;
	b = x;
}
