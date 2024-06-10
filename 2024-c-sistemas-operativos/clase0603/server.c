/*
 * server.c
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
 * $ gcc -Wall -o server server.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in s;
	s.sin_family = AF_INET;
	s.sin_port = htons(8200); // puerto tcp/ip en donde escuchara peticiones este servidor
	s.sin_addr.s_addr = inet_addr("127.0.0.1"); // direccion local del servidor
	memset(s.sin_zero,0,8); // por culpa de Berkeley!
	socklen_t slen = sizeof(struct sockaddr_in);
	bind(sock,(struct sockaddr *) &s,slen);
	listen(sock,0);
	while(1) {
		int sockcli = accept(sock,(struct sockaddr *) &s,&slen);
		if ( sockcli != -1 ) {
			// tengo un cliente conectado!!
			// espero recibir algo del cliente
			char buffer[512];
			int rbytes = recv(sockcli,buffer,511,0);
			if ( rbytes != -1 ) {
				buffer[rbytes]='\0';
				printf("server: cliente envio [%s]\n",buffer);
				int sbytes = send(sockcli,buffer,rbytes,0);
				printf("server: envie %d bytes a cliente!\n",sbytes);
				// cierro comunicacion
				close(sockcli);
			} else {
				printf("server: error de lectura de cliente\n");
			}
		}
	}
	return 0;
}

