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
 * $ gcc -Wall -o cliente cliente.c
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
	connect(sock,(struct sockaddr *) &s,slen);
	char buffer[512];
	strcpy(buffer,"ls -l");
	printf("cliente: envio [%s]\n",buffer);
	send(sock,buffer,strlen(buffer),0);
	memset(buffer,0,512);
	int rbytes = recv(sock,buffer,511,0);
	if ( rbytes != -1 ) {
		buffer[rbytes] = '\0';
		printf("cliente: recibi [%s] del servidor\n",buffer);
	} else {
		printf("cliente: Error recibiendo del servidor!\n");
	}
	close(sock);
	printf("cliente: fin!\n");
	return 0;
}

