//server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

#include "server.h"

#define SIZEMENSAJEPARACLIENTE 16000

//--------------------------------------------------------------------
void getMETODO(char fuente[], char metodo[],int limite);
void getEXTENSIONNOMBREINDEX(char recibido[] ,char extension[], int limite);
void getNOMBREINDEX(char recibido[], char nombreIndexHtml[],int limite);
void getCONTENIDOIndexHtml(char contenidoIndexHtml[],char nombreIndexHtml[]);

void metodoGET(char recibido[],char extension[],char mensajeParaCliente[]);
void metodoPOST(char recibido[],char extension[],char mensajeParaCliente[]);
void resuelvePipeDupExec(char recibido[],char mensajeParaCliente[],char lineaDatos[]);
void buscarDatosRecibidosDelFormulario(char recibido[],char lineaDatos[],int limite);
//-----------------------------------------------------------------
int main()
 {

    const char *remoteHost      = REMOTEHOST;
    int remotePort              = REMOTEPORT;

    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
  
    // Crear socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(remoteHost);
    address.sin_port = htons(remotePort);
    printf("socket %d\n",server_fd);
    if (server_fd == -1) exit(0);
        
    // Enlazar y escuchar
    int err = bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    printf("bind %d\n",err);
    if (err == -1) exit(0);
    
    err = listen(server_fd, 3);
    printf("listen %d\n",err);
    if (err == -1) exit(0);
       
    printf(" ***** esperando conexion del cliente *****\n");
    while (1)
    {
         char recibido[1024] ;
         new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
          if (new_socket == -1)
          {
            printf("accept rechazo la peticion del cliente %d\n\n",new_socket);
            exit(0);
          }
       
          //-- lee peticion del cliente
          int nb = recv(new_socket,recibido,1024,0);
          recibido[nb] = '\0';
         
          if (recibido[0] != '\0')
          {
            // busca en el mensaje recibido si es GET o POST
            char metodo[8]; memset(metodo,'\0',8);
            getMETODO(recibido,metodo,strlen(recibido)); 

            // busca en el mensaje recibido si es GET o POST
            char extension[8] ;          
            getEXTENSIONNOMBREINDEX(recibido,extension,strlen(recibido));

            char mensajeParaCliente[SIZEMENSAJEPARACLIENTE];
            memset(mensajeParaCliente,'\0',SIZEMENSAJEPARACLIENTE);
              
            if (!strncmp(metodo,"GET",3) && strncmp(extension,"ico",3))
            {
              printf("accept OK su cliente %d le envio este mensaje\n",new_socket);
              printf("%s\n",recibido);
              metodoGET(recibido,extension,mensajeParaCliente);
              send(new_socket,mensajeParaCliente,strlen(mensajeParaCliente),0);
              printf(" ***** esperando conexion del cliente *****\n");
            }
            if (!strncmp(metodo,"POST",4))
            {
              printf("accept OK su cliente %d le envio este mensaje\n",new_socket);
              printf("%s\n",recibido);
              metodoPOST(recibido,extension,mensajeParaCliente);
              send(new_socket,mensajeParaCliente,strlen(mensajeParaCliente),0);
              printf(" ***** esperando conexion del cliente *****\n");          
            }
          }  
          close(new_socket);          
    }
    exit(0);
}

void metodoGET(char recibido[],char extension[],
               char mensajeParaCliente[])
{
  if (!strncmp(extension,"html",4))
  {
    char nombreIndexHtml[1024] ; 
    char contenidoIndexHtml[SIZEMENSAJEPARACLIENTE];
    // -- busca nombre del archivo indexHtml
    memset(nombreIndexHtml,'\0',1024);
    getNOMBREINDEX(recibido, nombreIndexHtml,strlen(recibido));
         
    //-- lee archivo indexHtml
    memset(contenidoIndexHtml,'\0',SIZEMENSAJEPARACLIENTE);              
    getCONTENIDOIndexHtml(contenidoIndexHtml,nombreIndexHtml);
    strcpy(mensajeParaCliente,contenidoIndexHtml);
    strcat(mensajeParaCliente,"\0");
  }
  
  if (!strncmp(extension,"cgi",3))
  { 
    resuelvePipeDupExec(recibido,mensajeParaCliente,"\0"); // \0 es lineaDatos 
  }
}          

void metodoPOST(char recibido[],char extension[],char mensajeParaCliente[])
{
   char lineaDatos[8096] ; memset(lineaDatos,'\0',8096);
   buscarDatosRecibidosDelFormulario(recibido,lineaDatos,strlen(recibido));
   if (lineaDatos[0]!='\0')
      printf("*** Mis Datos son: %s\n",lineaDatos);
   if (!strncmp(extension,"cgi",3))
   { 
       resuelvePipeDupExec(recibido,mensajeParaCliente,lineaDatos); 
   }
}         

void resuelvePipeDupExec(char recibido[],char mensajeParaCliente[],char lineaDatos[])
{ 
     // -- busca nombre del archivo cgi
     char pathCGI[128] ; memset(pathCGI,'\0',128);
     strcpy(pathCGI,PATHCGI);
     char nombreCGI[128] ;  memset(nombreCGI,'\0',128);
     getNOMBREINDEX(recibido, nombreCGI,strlen(recibido));

     strcat(pathCGI,nombreCGI);
     strcat(pathCGI,"\0");
   
     //-------------------------------------------------------------
     int pw[2] ; pipe(pw);
     pid_t pid = fork();
     if ( pid > 0)
     {
       close(pw[1]);
       if (lineaDatos[0] != '\0')
       {
         FILE * fd = fopen("temp","w");
         fwrite(lineaDatos,strlen(lineaDatos),1,fd);
         fclose(fd);
       }
       waitpid(pid,NULL,0);
     }
     else
     { 
       if (pid == 0) 
       {
         close(pw[0]);
         int defout = dup(1);
         dup2(pw[1],1);
         execl(pathCGI,pathCGI,NULL);
         printf("\n********** ERROR execl ************\n");
         dup2(defout,1);
         close(defout);
         exit(0);
        }
      }
     
     char strpipe[8092*2] ; memset(strpipe,'\0',8092*2);
     while(read(pw[0],strpipe,8092*2));
     printf("cgi envio strpipe ---> \n%s\n",strpipe);
     //strcat(strpipe,"\0");
     strcpy(mensajeParaCliente,strpipe);
}

void getCONTENIDOIndexHtml(char contenidoIndexHtml[],char nombreIndexHtml[])
{
  int fd = open(nombreIndexHtml,O_RDONLY);
  if ( fd == -1 )
     printf(" *** Error en open %s ***\n",nombreIndexHtml);
  else
     {
         int nb = read(fd,contenidoIndexHtml,SIZEMENSAJEPARACLIENTE);
         if ( nb == -1 )
              printf(" *** Error en read %s  ***\n",nombreIndexHtml);
         else
              contenidoIndexHtml[nb] = '\0';
         close(fd);
     }
}

void getMETODO(char recibido[], char metodo[],int limite)
{
   int i ; int j = 0 ;
   for(i = 0 ; i < limite && recibido[i] != '\n'; i++)
   {
      metodo[j] = recibido[i];
      j++;
   }
   metodo[j-1] = '\0';
}

void getNOMBREINDEX(char recibido[], char nombreIndexHtml[],int limite)
{
   int i ; int j = 0 ;
   for(i = 0 ; i < limite && recibido[i] != '/'; i++);
   for(i = i+1 ; i < limite && (recibido[i] != ' ' && recibido[i] != '?'); i++)
   {
      nombreIndexHtml[j] = recibido[i];
      j++;
   }
   nombreIndexHtml[j] = '\0';
}

void getEXTENSIONNOMBREINDEX(char recibido[],char extension[],int limite)
{
   int i ; int j = 0 ;
   for(i = 0 ; i < limite && recibido[i] != '/'; i++);
   for(i = i+1 ; i < limite && recibido[i] != '.'; i++);
   for(i = i+1 ; i < limite && (recibido[i] != ' ' && recibido[i] != '?'); i++)
   {
      extension[j] = recibido[i];
      j++;
   }
   extension[j] = '\0';
}

void buscarDatosRecibidosDelFormulario(char recibido[],char lineaDatos[],int limite)
{
   char length[10] ; memset(length,'\0',10);
   char * punt = strstr(recibido,"Content-Length:");
   if (punt == NULL)
      strcpy(lineaDatos,"No encuentra Content-Length:\0");
   else
   { 
     int i    ;
     for(i = 1 ; punt[i] != ':' ; i++);
     i += 2;
     int j = 0;
     for(i = i; punt[i] != '\n' ; i++) 
     {
       length[j] = punt[i];
       j++;
     }
     length[j]='\0';
     int len = atoi(length);
     if (len == 0)
       strcpy(lineaDatos,"*** NO HAY DATOS DE FORMULARIO ***\0");
     else
     {   
       char * punt = strstr(recibido,"MISDATOS");
       if (punt == NULL)
          strcpy(lineaDatos,"*** NO HAY MISDATOS ***\0");
       else
         {
             //printf("** punt = %s\n",punt);
             int i ;
             for(i=0;punt[i]!='\0';i++)
                lineaDatos[i]=punt[i];
             lineaDatos[i]='\0';              
        //   strcpy(lineaDatos,punt);
        //   strcat(lineaDatos,'\0');          
         }
     }
   }
}


