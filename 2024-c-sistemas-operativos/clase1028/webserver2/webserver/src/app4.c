/*
 * app4.c
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
 * app4 aplicacion muy simple orientada a servicios json
 * 
 * $ gcc -fPIC -Wall -g -c -o cgi.o cgi.c -I . -L .
 * $ gcc -fPIC -Wall -g -c -o util.o util.c -I . -L .
 * $ gcc -fPIC -Wall -g -c -o app4.o app4.c  -I . -L . 
 * $ gcc -fPIC -shared -Wl,-soname,libapp4.so -o libapp4.so app4.o util.o cgi.o -lc 
 * $ mv -f libapp4.so ../lib
 * $ rm *.o
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>
#include <cgi.h>

FILE *f = NULL, *fcmd = NULL;

void *app_ini(clave_valor *pserver,clave_valor *papp,long *largo); // puntero a funcion inicial de aplicacion  void *f_init(long *);
void app_fin(void *buffer,long *largo); // puntero a funcion final de aplicaicon void f_fin(void *,long *);
void app_get(void *buffer,long *largo,clave_valor *pserver,clave_valor *papp,peticion *pet,respuesta *ret);
/*
int main(int argc, char **argv)
{
	// hacer pruebas aqui y ejecutar desde linea de comandos
	return 0;
}
*/
// esta app no desea compartir/exponer ningun buffer al servidor
void *app_ini(clave_valor *pserver,clave_valor *papp,long *largo) { // puntero a funcion inicial de aplicacion  void *f_init(long *);
	printf("app_ini(4): inicio\n");
	f = fopen("../data/nombres","w");
	fcmd = fopen("../data/comando","w");
	return NULL;
}
void app_fin(void *buffer,long *largo) { // puntero a funcion final de aplicaicon void f_fin(void *,long *);
	// no hago nada, no tengo ningun buffer, asi que buffer debe ser NULL y largo 0L
	fclose(f);
	fclose(fcmd);
	printf("app_fin(4): fin\n");
}
void app_get(void *buffer,long *largo,clave_valor *pserver,clave_valor *papp,peticion *pet,respuesta *ret) {
	int bloque = 1024,tam_salida=bloque;
	char *salida = (char *) malloc(bloque);
	memset(salida,0,tam_salida);
	if ( strcmp(pet->recurso,"/app4.hola") == 0 ) {
		char usuario[200];
		memset(usuario,0,200);
		printf("app_get(4): pet->cuerpo=[%s]\n",(char *) pet->cuerpo);
		cgi_extraer(usuario,200,"usuario",(char *) pet->cuerpo);
		sprintf(salida,"{\"saludo\":\"Hola %s\"}",usuario);
		printf("app_get(4): salida=[%s]\n",salida);
	}
	if ( strcmp(pet->recurso,"/app4.agregar") == 0 ) {
		char usuario[200];
		memset(usuario,0,200);
		printf("app_get(4): pet->cuerpo=[%s]\n",(char *) pet->cuerpo);
		cgi_extraer(usuario,200,"usuario",(char *) pet->cuerpo);
		fprintf(f,"%s\n",usuario);
		sprintf(salida,"{\"saludo\":\"%s agregado ok!\"}",usuario);
	}
	if ( strcmp(pet->recurso,"/app4.ejecutar") == 0 ) {
		char usuario[200];
		memset(usuario,0,200);
		printf("app_get(4): pet->cuerpo=[%s]\n",(char *) pet->cuerpo);
		cgi_extraer(usuario,200,"usuario",(char *) pet->cuerpo);
		char *p = usuario;
		while(*p) { if ( *p == '+' ) *p=' ';p++; }
		
		FILE *ff = popen(usuario,"r");
		char b[512];
		while(fgets(b,512,ff) != NULL) {
			fprintf(fcmd,"%s",b);
		}
		fclose(ff);
		sprintf(salida,"{\"saludo\":\"(%s) ejecutado ok!\"}",usuario);
	}
	
	ret->cuerpo = salida;
	ret->largo = strlen(salida); // ATENCION, no enviar \0 atras de json xq javascript no lo parsea
	util_agregar_content(ret->cabecera,ret->largo);
	util_agregar(ret->cabecera,"Content-Type","application/json");
}
