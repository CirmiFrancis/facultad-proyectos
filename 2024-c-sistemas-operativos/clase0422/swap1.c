/*
 * swap1.c
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