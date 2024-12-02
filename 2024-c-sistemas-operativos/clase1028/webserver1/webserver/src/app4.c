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
 * app4 simple app demo
 * toda la app orientada a servicios, retorna mensajes en json
 * 
 * Forma de compilacion:
 * $ gcc -fPIC -Wall -g -c -o cgi.o cgi.c -I . -L .
 * $ gcc -fPIC -Wall -g -c -o util.o util.c -I . -L .
 * $ gcc -fPIC -Wall -g -c -o app4.o app4.c  -I . -L . 
 * $ gcc -fPIC -shared -Wl,-soname,libapp4.so -o libapp4.so app4.o util.o cgi.o -lc 
 * $ mv -f libapp4.so ../lib
 * $ rm *.o
 * 
 * Uso script app4.sh
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>
#include <cgi.h>

struct login_t {
	char usuario[32];
	char clave[32];
	long sid; // session id
	long long llogin; // ultimo login
};
typedef struct login_t login;
login *milog = NULL;
login usr[2] = {{"grchere","grc",0L,0LL},{"jromer","juan",0L,0LL}};
int nlog = 0;
int nusr = 2;

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
	int nlog = 10; // cantidad maxima de usuarios conectados al mismo tiempo
	milog = (login *) malloc(sizeof(login)*nlog);
	memset(milog,0,sizeof(login)*nlog);
	return NULL;
}
void app_fin(void *buffer,long *largo) { // puntero a funcion final de aplicaicon void f_fin(void *,long *);
	// libero memoria
	if ( milog ) { free(milog);milog=NULL;nlog=0; }
}
void app_get(void *buffer,long *largo,clave_valor *pserver,clave_valor *papp,peticion *pet,respuesta *ret) {
	int bloque = 1024,tam_salida=bloque;
	char *salida = (char *) malloc(bloque);
	memset(salida,0,tam_salida);
	if ( strcmp(pet->recurso,"/app4.login") == 0 ) {
		char slogin[32];
		char sclave[32];
		printf("app_get(4): pet->cuerpo=[%s]\n",(char *) pet->cuerpo);
		cgi_extraer(slogin,32,"login",(char *) pet->cuerpo);
		cgi_extraer(sclave,32,"clave",(char *) pet->cuerpo);
		printf("app_get(3): usuario=[%s] clave[%s]\n",slogin,sclave);
		
		// verifico si el usuario y la clave es correcta
		int i,login_ok=0;
		for(i=0;!login_ok && i<nusr;i++) {
			if ( strcmp(usr[i].usuario,slogin) == 0 && strcmp(usr[i].clave,sclave) == 0 ) {
				login_ok = 1;
			}
		}
		if ( login_ok ) {
			// usuario-clave ok!
			login *p = milog;
			i=0;
			int login_lleno = 1;
			for(i=0;login_lleno && i<nlog;i++,p++) {
				if ( !p->usuario[0] ) {
					login_lleno = 0;
					strcpy(p->usuario,slogin);
					strcpy(p->clave,sclave);
					p->sid = i; // aqui usar generador de sid
					p->llogin = cgi_fecha_en_millis();
				}
			}
			if ( login_lleno ) {
				// rayos, ya se logearon todos los usuarios! no se acepta a mas nadie
				strcpy(salida,"{\"ret\":1,\"errorm\":\"Demasiado usuarios logeados!\"}");
			} else {
				// todo ok!
				sprintf(salida,"{\"ret\":0,\"sid\":%ld,\"llogin\":%lld}",p->sid,p->llogin);
			}
			
		} else {
			// usuario-clave no existe!
			strcpy(salida,"{\"ret\":1,\"errorm\":\"Usuario o clave erronea!\"}");
		}
		
	}
	if ( strcmp(pet->recurso,"/app4.logoff") == 0 ) {
		char ssid[64];
		printf("app_get(4): pet->cuerpo=[%s]\n",(char *) pet->cuerpo);
		cgi_extraer(ssid,64,"sid",(char *) pet->cuerpo);
		printf("app_get(4): sid=[%s]\n",ssid);
		long long mysid = atoll(ssid);
		
		int i,logoff_ok=0;
		login *p = milog;
		for(i=0;!logoff_ok && i<nlog;i++,p++) {
			if ( p->sid == mysid ) {
				logoff_ok = 1;
				memset(p,0,sizeof(login)); // limpio datos de login 
			}
		}
		
		if ( logoff_ok ) {
			// todo ok
			strcpy(salida,"{\"ret\":0}");
		} else {
			// sid no existe!
			strcpy(salida,"{\"ret\":1,\"errorm\":\"Session ID no existe!\"}");
		}

	}
	ret->cuerpo = salida;
	ret->largo = strlen(salida)+1;
	util_agregar_content(ret->cabecera,ret->largo);
	util_agregar(ret->cabecera,"Content-Type","application/json");
}
