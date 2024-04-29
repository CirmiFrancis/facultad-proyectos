/*
 * swap2.c
 * 
 * swap que SI funciona
*/

#include <stdio.h>
#include <stdlib.h>

void swap(int *,int *);

int main(int argc, char **argv)
{
	int a = 7;
	int b = 8;
	printf("antes   a=%d b=%d\n",a,b);
	swap(&a,&b);
	printf("despues a=%d b=%d\n",a,b);
	printf("____en main_______________________\n");
	printf(" &a=%p &b=%p a=%d b=%d\n",&a,&b,a,b);
	return 0;
}

void swap(int *a,int *b) {
	int x = *a;
	*a = *b;
	*b = x;
	printf("____en la funcion swap_______________________\n");
	printf(" a=%p b=%p *a=%d *b=%d\n",a,b,*a,*b);
	printf("&a=%p &b=%p\n",&a,&b);
}