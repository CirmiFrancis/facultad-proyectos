/*
 * server.c
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

