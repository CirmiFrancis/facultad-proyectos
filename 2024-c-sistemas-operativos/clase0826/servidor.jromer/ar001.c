
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define MAXTAMARCHIVO 16000

void buscarLineaDeDatos(char recibe[],char comando[]);
void decodificacionACliente_1(char entrada[],char salida[]);
void decodificacionACliente_2(char entradaSalida[]);
void ejecutarComando(char COMANDO_decode[],char salidaComando[]);

int main(void) 
{
    char lineaDatos[1024]; 
    memset(lineaDatos,'\0',1024);
    
    FILE * fd = fopen("temp","r");
    fread(lineaDatos,1024,1,fd);
    lineaDatos[strlen(lineaDatos)] = '\0';
    fclose(fd);
    
    char nombreARCHIVO[512]; 
    memset(nombreARCHIVO,'\0',512);
    
    buscarLineaDeDatos(lineaDatos,nombreARCHIVO);

    char contenidoArchivo[MAXTAMARCHIVO]; 
    memset(contenidoArchivo,'\0',MAXTAMARCHIVO);

    ejecutarComando(nombreARCHIVO,contenidoArchivo);
    
    // Generar la respuesta
    printf("HTTP/1.1 200 OK\n");
    printf("Content-length: %d\n",strlen(contenidoArchivo)+1024);    
    printf("Content-type: text/html\n\n");
    
    printf("<meta charset= \"utf-8\">\n");
    printf("<html><head><title>Datos Recibidos</title></head><body>");
     
    printf("Datos Recibidos del Servidor Contenido del Archivo %s<br>",nombreARCHIVO);
    printf("<pre>%s</pre>",contenidoArchivo);
    printf("<input type=\"button\" value=\"Anterior\" onClick=\"history.go(-1);\">");
    printf("</body></html>");

    exit(0);
}

void buscarLineaDeDatos(char recibe[],char ARCHIVO[])
{
   int i , j ;
   char * punt = strstr(recibe,"ARCHIVO");
   if (punt != NULL)
   {
     j=0;
     for(i=0 ; punt[i] != '=' ; i++);
     for(i=i+1 ; punt[i] != '&' && punt[i] != '\0' && punt[i] != '\n'; i++)
     { 
           ARCHIVO[j]=punt[i] ;
           j++ ;
     }
     ARCHIVO[j]='\0';
   } 
}              


void ejecutarComando(char archivo[], char contenidoArchivo[])
{
   if (archivo[0] == '\0')
     strcpy(contenidoArchivo,"No Ingreso ningùn nombre de archivo\0");
   else
   {
        int fd = open(archivo,O_RDONLY);
        if (fd == -1)
              strcpy(contenidoArchivo,"Nombre de archivo no existe en el pwd\0");
        else
        {
          int nb = read(fd,contenidoArchivo,MAXTAMARCHIVO);
          //contenidoArchivo[nb] = '\0';
          contenidoArchivo[strlen(contenidoArchivo)] = '\0';
          
//          printf("nb = %d strlen(contenidoArchivo)=%d\n",nb,strlen(contenidoArchivo));
          if ( nb == -1)
             strcpy(contenidoArchivo,"No puede leer el archivo\0");
          else
          {
           if (nb == 0) 
              strcpy(contenidoArchivo,"El archivo està vacìo\0");
           else
             {
              //decodificacionCOMANDO(contenidoArchivo);
              char contenidoArchivo_decode[MAXTAMARCHIVO];
              memset(contenidoArchivo_decode,'\0',MAXTAMARCHIVO);
              //reemplazo ascii por %xx
              decodificacionACliente_1(contenidoArchivo,contenidoArchivo_decode);
              memset(contenidoArchivo,'\0',MAXTAMARCHIVO);
              strcpy(contenidoArchivo,contenidoArchivo_decode);
              //reemplazo \n por <br> 
              //decodificacionACliente_2(contenidoArchivo);
             }
          }
          close(fd);
        }
    }
}

void decodificacionACliente_1(char entrada[], char salida[])
{
 
  int i ;
  int j = 0;
  for (i = 0; i < MAXTAMARCHIVO ; i++)
  {
    salida[j] = entrada[i];   
    if (entrada[i] == '<')
    { 
      salida[j] = '.';  
    }
    j++;   
  }
  salida[j] = '\0';     
}


void decodificacionACliente_2(char entradaSalida[])
{
  char salidaComandoDecode[MAXTAMARCHIVO];
  memset(salidaComandoDecode,'\0',MAXTAMARCHIVO);
  int i ;
  int j = 0 ;
  for(i = 0 ; entradaSalida[i] != '\0';i++)
  {
    for( ; entradaSalida[i] != '\n';i++,j++)
     {
        salidaComandoDecode[j] = entradaSalida[i];
     }
     strcat(salidaComandoDecode,"<br>");
     j+=4;
  }
  j++;
  salidaComandoDecode[j] = '\0';
  memset(entradaSalida,'\0',MAXTAMARCHIVO);
  strcpy(entradaSalida,salidaComandoDecode);
}
