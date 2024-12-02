#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#define SIZESALIDACOMANDO 16000

void buscarLineaDeDatos(char recibe[],char comando[]);
void decodificacionPOST(char COMANDO[], char COMANDO_decode[]);
void ejecutarComando(char COMANDO_decode[],char salidaComando[]);
void decodificacionCOMANDO(char salidaComando[]);

int main(void) 
{
    char lineaDatos[1024]; 
    memset(lineaDatos,'\0',1024);
    
    FILE * fd = fopen("temp","r");
    fread(lineaDatos,1024,1,fd);
    fclose(fd);

    char comando[1024]; 
    memset(comando,'\0',1024);
    
    char COMANDO_decode[1024]; 
    memset(COMANDO_decode,'\0',1024);
    
    buscarLineaDeDatos(lineaDatos,comando);
    decodificacionPOST(comando,COMANDO_decode);
    
    char salidaComando[SIZESALIDACOMANDO]; 
    memset(salidaComando,'\0',SIZESALIDACOMANDO);

    ejecutarComando(COMANDO_decode,salidaComando);

    // Generar la respuesta
    printf("HTTP/1.1 200 OK\n");
    printf("Content-type: text/html\n\n");
    
    printf("<meta charset= \"utf-8\">\n");
    printf("<html><head><title>Datos Recibidos</title></head><body>");
     
    printf("<h1>Datos Recibidos del Servidor Linux</h1>");
    printf("<p>%s</p>",salidaComando);

    printf("<input type=\"button\" value=\"Anterior\" onClick=\"history.go(-1);\">");
    printf("</body></html>");

    exit(0);
}

void buscarLineaDeDatos(char recibe[],char COMANDO[])
{
   int i , j ;
   char * punt = strstr(recibe,"COMANDO");
   if (punt != NULL)
   {
     j=0;
     for(i=0 ; punt[i] != '=' ; i++);
     for(i=i+1 ; punt[i] != '&' && punt[i] != '\0'; i++)
         { COMANDO[j]=punt[i] ; j++ ; }
     COMANDO[j]='\0';
   } 
}              

void decodificacionPOST(char COMANDO[], char COMANDO_decode[])
{
  char code[32][3];
  memset(code,'\0',32*3);
  char decode[32];
  memset(decode,0,32);
  strcpy(code[0],"27\0"); decode[0] = '\'';
  strcpy(code[1],"28\0"); decode[1] = '(';
  strcpy(code[2],"29\0"); decode[2] = ')';   
  strcpy(code[3],"2C\0"); decode[3] = ',';
  strcpy(code[4],"3B\0"); decode[4] = ';';
  strcpy(code[5],"3D\0"); decode[5] = '=';
 
  char codcom[3];
  memset(codcom,0,3);
  int i ;
  int j = 0;
  for (i = 0; COMANDO[i] != ';' ; i++)
  {
    if (COMANDO[i] != '%')
    {   
      COMANDO_decode[j] = COMANDO[i]; 
      if (COMANDO[i] == '+')
         COMANDO_decode[j] = ' ';
      j++;   
    }
    else
    {
       i++;
       codcom[0]=COMANDO[i];
       i++;
       codcom[1]=COMANDO[i];
       codcom[2]='\0';
       //encontrar decode de codsql %??
       int k ;
       for(k =0;code[k][0]!='\0' && strncmp(code[k],codcom,2);k++);
       if (!strncmp(code[k],codcom,2))
                COMANDO_decode[j] = decode[k];
       j++;  
    }
  } 
}


void ejecutarComando(char comando[], char salidaComando[])
{
   if (comando[0] == '\0')
     strcpy(salidaComando,"No Ingreso ningùn comando\0");
   else
   {
      comando[strlen(comando)] = ' ';
      strcat(comando,"> tempComando\0");
      system(comando);
      int fd = open("tempComando",O_RDONLY);
      if (fd == -1)
         strcpy(salidaComando,"Archivo tempComando no accesible\0");
      else
      { 
           int nb = read(fd,salidaComando,SIZESALIDACOMANDO);
           salidaComando[nb] = '\0';
           if (nb == 0) 
              strcpy(salidaComando,"Comando Invalido\0");
           else
              decodificacionCOMANDO(salidaComando);
       }
       close(fd);
    }
}

void decodificacionCOMANDO(char salidaComando[])
{
  char salidaComandoDecode[SIZESALIDACOMANDO];
  memset(salidaComandoDecode,'\0',SIZESALIDACOMANDO);
  int i ;
  int j = 0 ;
  for(i = 0 ; salidaComando[i] != '\0';i++)
  {
    for( ; salidaComando[i] != '\n';i++,j++)
     {
        salidaComandoDecode[j] = salidaComando[i];
     }
     strcat(salidaComandoDecode,"<br>");
     j+=4;
  }
  j++;
  salidaComandoDecode[j] = '\0';
  memset(salidaComando,'\0',SIZESALIDACOMANDO);
  strcpy(salidaComando,salidaComandoDecode);
}

