/*
 * raid.c
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
 * Simulador RAID entre tres archivos usando un archivo de paridad
 * usando xor
 * reconstruccion de archivo perdido a partir de los otros dos
 * 
 * Forma de compilacion:
 * $ gcc -Wall -o raid raid.c
 * 
 * Forma de uso:
 * $ ./raid
 * 
 * Puede utilizar comando linux xxd para ver contenido binario de los
 * archivos:
 * 
 * $ xxd <archivo>
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// arma menu y devuelve opcion elegida
int menu(const char *titulo,const char *opciones[]);
// funcion generica para ingreso de datos
void ingreso(char *buffer,int size);
// pide confirmacion al usuario
int ingreso_sino(char *msg);
// ingresa un numero entero
int ingreso_int();

struct data_file {
	char archivo[3][256]; // archivo 1, archivo 2 y archivo de paridad
	int tamanio; // tama#o de cada archivo en bytes
	void *buffer[3]; // puntero a buffer de archivos de tamanio bytes cada uno
	FILE *f[3];
	unsigned char eliminado[3];
};

// funciones 
void hago_paridad(void *to,void *from1,void *from2,int tamanio);

int main(int argc, char **argv) {
	const char *opc[5] = { "Crear Archivos", "Grabar en archivo", "Borrar Archivo", "Recuperar Archivo", NULL };
	int opcion=0,i,nelim;
	struct data_file d;
	memset(&d,0,sizeof(struct data_file)); // d=0
	
	do {
		opcion = menu("SIMULADOR ALGORITMO RAID",opc);
		switch(opcion) {
			case 1: // crear archivos
				printf("Se asume al archivo #2 como archivo de paridad\n");
				for(i=0;i<3;i++) {
					printf("Ingrese Nombre Archivo #%d:",i);
					ingreso(d.archivo[i],256);
				}
				printf("Ingrese (en bytes) tamaño de cada archivo:");
				d.tamanio = ingreso_int();
				for(i=0;i<3;i++) {
					if ( d.buffer[i] ) free(d.buffer[i]); 
					d.buffer[i] = malloc(d.tamanio);
					memset(d.buffer[i],0,d.tamanio); // buffer[i]=0
					d.eliminado[i] = ' ';
				}
				//
				hago_paridad(d.buffer[2],d.buffer[0],d.buffer[1],d.tamanio);
				// grabo archivos
				for(i=0;i<3;i++) { 
					d.f[i] = fopen(d.archivo[i],"wb");
					fwrite(d.buffer[i],d.tamanio,1,d.f[i]);
					fclose(d.f[i]);
				}
				break;
			case 2:  // grabar archivos
				if ( d.eliminado[0] == 'x' || d.eliminado[1] == 'x' ) {
					printf("Error!, no puede grabar si hay un archivo eliminado!\nRecupere el archivo y luego grabe\n");
					break;
				}
				printf("Archivo #0: [%s] eliminado[%c]\n",d.archivo[0],d.eliminado[0]);
				printf("Archivo #1: [%s] eliminado[%c]\n",d.archivo[1],d.eliminado[1]);
				printf("Ingrese #archivo en donde quiere grabar (0-1):");
				i = ingreso_int();
				if ( d.eliminado[i] == 'x' ) {
					printf("Error!, no puede grabar en archivo eliminado!\n");
					break;
				}
				printf("Ingrese posicion en donde grabar (0-%d):",d.tamanio-1);
				int pos = ingreso_int();
				char tmp[100];
				printf("Ingrese texto a grabar (max 100 caracteres):");
				ingreso(tmp,100);
				memcpy(d.buffer[i]+pos,tmp,strlen(tmp)+1);
				hago_paridad(d.buffer[2],d.buffer[0],d.buffer[1],d.tamanio);
				
				d.f[i] = fopen(d.archivo[i],"r+b");
				d.f[2] = fopen(d.archivo[2],"r+b");
				fwrite(d.buffer[i],d.tamanio,1,d.f[i]);
				fwrite(d.buffer[2],d.tamanio,1,d.f[2]);
				fclose(d.f[i]);
				fclose(d.f[2]);
				break;
			case 3: // borrar archivo
				nelim=0;
				for(i=0;i<3;i++) { 
					printf("Archivo #%d: [%s] eliminado[%c]\n",i,d.archivo[i],d.eliminado[i]);
					if ( d.eliminado[i] == 'x' ) nelim++;
				}
				if ( nelim > 0 ) {
					printf("Error!, no puede eliminar mas de dos archivos!\n");
					break;
				}
				printf("Ingrese #archivo que quiere borrar (0-2):");
				i = ingreso_int();
				memset(d.buffer[i],0,d.tamanio); // buffer[i]=0
				remove(d.archivo[i]); // rm d.archivo[i]
				d.eliminado[i]='x';
				break;
			case 4: // recuperar archivo
				nelim = -1;
				for(i=0;i<3;i++) { 
					printf("Archivo #%d: [%s] eliminado[%c]\n",i,d.archivo[i],d.eliminado[i]);
					if ( d.eliminado[i] == 'x' ) nelim=i;
				}
				if ( nelim == -1 ) {
					printf("Error!, no hay archivos para recuperar!\n");
					break;
				}
				i = nelim;
				switch(i) {
					case 0:
						hago_paridad(d.buffer[0],d.buffer[1],d.buffer[2],d.tamanio);
						break;
					case 1:
						hago_paridad(d.buffer[1],d.buffer[0],d.buffer[2],d.tamanio);
						break;
					case 2:
						hago_paridad(d.buffer[2],d.buffer[0],d.buffer[1],d.tamanio);
						break;
				}
				d.f[i] = fopen(d.archivo[i],"wb");
				fwrite(d.buffer[i],d.tamanio,1,d.f[i]);
				fclose(d.f[i]);
				d.eliminado[i]=' ';
				printf("Archivo [%s] recuperado!\n",d.archivo[i]);
				break;
			case 99:
				if ( !ingreso_sino("Realmente quiere salir?") ) opcion = 0;
				break;
		}
	} while(opcion != 99);
	
	// libero memoria
	for(i=0;i<3;i++) {
		if ( d.buffer[i] ) free(d.buffer[i]);
	}
	
	return 0;
}

// arma menu y devuelve opcion elegida
int menu(const char *titulo,const char *opciones[]) {
	int op,i,opp=0;
	do {
		op=1;i=0;
		printf("\t\t%s\n",titulo);
		while(opciones[i]) {
			printf("\t%2.0d. %s\n",op,opciones[i]);
			op++;i++;
		}
		printf("\t99. Salir\n");
		printf("Ingrese su opcion:");
		opp=ingreso_int();
		if ( opp == 99 ) return 99;
	} while(opp <= 0 || opp > (op-1));
	return opp;
}

// funcion generica para ingreso de datos
void ingreso(char *buffer,int size) {
	fgets(buffer,size,stdin);
	buffer[strlen(buffer)-1]='\0';
}

// ingresar si / no
int ingreso_sino(char *msg) {
	char rta[4];
	do {
		printf("%s (si/no)",msg);
		ingreso(rta,4);
	} while(!(strcasecmp(rta,"si") == 0 || strcasecmp(rta,"no") == 0));
	if ( strcasecmp(rta,"si") == 0 ) return 1;
	else return 0;
}

int ingreso_int() {
	char codigo[20];
	ingreso(codigo,20);
	return atoi(codigo);
}

// to = from1 xor from2
void hago_paridad(void *to,void *from1,void *from2,int tamanio) {
	int i=0;
	while(i<tamanio) {
		unsigned char c,d,e;
		memcpy(&c,from1,1);
		memcpy(&d,from2,1);
		e = c ^ d; // e = c xor d;
		memcpy(to,&e,1); // *to = e
		to++;from1++;from2++;i++;
	}
}
