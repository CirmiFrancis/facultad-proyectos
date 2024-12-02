#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

#include "server.h"

void funcionMysql(const char * host , const char * puerto , const char * username , const char * passname , char dbname[],char query[],char respuesta[]);
void buscarLineaDeDatos(char*,char[],char[],char[],char[],char[],char[],char[],char[], char[]);
void decodificacionSqlPOST(char [], char[]);
void consulta(         const char * host,
                        const char * port,
                        const char * username,
                        const char * userpass,           
                        char NAMEBD[] , 
                        char SQL_consulta[], 
                        char SQL_respuesta[]);
void armarResultadoQuery(char [],char [],const char * , const char *);

//---------------------------------------------------
int main(void) 
{

    const char * remote_host_mysql = REMOTEHOSTMariadb;
    const char * remote_port_mysql = REMOTEPORTMariadb ;

    char lineaDatos[8092]; 
    memset(lineaDatos,'\0',8092);
    
    FILE * fd = fopen("temp","r");
    fread(lineaDatos,8092,1,fd);
    fclose(fd);

    char mensaje[8092]; 
    armarResultadoQuery(lineaDatos,mensaje,remote_host_mysql,remote_port_mysql);

    // Generar la respuesta
    printf("HTTP/1.1 200 OK\n");
    printf("Content-type: text/html\n\n");
    
    printf("<meta charset= \"utf-8\">\n");
    printf("<html><head><title>Datos Recibidos</title></head>");
    printf("<h1>Datos Recibidos de Mysql/Maridb</h1>");
    printf("<p>%s</p>\n", mensaje);
   // printf("<p>%d</p>\n", strlen(mensaje));  
 printf("<input type=\"button\" value=\"Anterior\" onClick=\"history.go(-1);\">");  
    printf("</body></html>");
    exit(0);
}

void buscarLineaDeDatos(char recibe[],char USERNAME[],char USERPASS[],char VERBD[],char NAMEBDCATALOGO[],char NAMEBDUSUARIO[],char VERTAB[],char VERATTR[], char NAMETAB[],char SQL[])
{
   int i , j ;
   char * punt = strstr(recibe,"USERNAME");
   if (punt != NULL)
   {
     j=0;
     for(i=0 ; punt[i] != '=' ; i++);
     for(i=i+1 ; punt[i] != '&' ; i++)
         { USERNAME[j]=punt[i] ; j++ ; }
     USERNAME[j]='\0';
   }
//-----------------------
   punt = strstr(recibe,"USERPASS");
   if (punt != NULL)
   {
     j=0;
     for(i=0 ; punt[i] != '=' ; i++);
     for(i=i+1 ; punt[i] != '&' ; i++)
         { USERPASS[j]=punt[i] ; j++ ; }
     USERPASS[j]='\0';
   }
//-----------------------
   punt = strstr(recibe,"VERBD");
   if (punt == NULL)
     strcpy(VERBD,"NO\0");
   else
     strcpy(VERBD,"SI\0");
//-----------------------   
   punt = strstr(recibe,"NAMEBDCATALOGO");
   if (punt != NULL)
   {
     j=0;
     for(i=0 ; punt[i] != '=' ; i++);
     for(i=i+1 ; punt[i] != '&' ; i++)
         { NAMEBDCATALOGO[j]=punt[i] ; j++ ; }
     NAMEBDCATALOGO[j]='\0';
   }
//---------------------------
   punt = strstr(recibe,"NAMEBDUSUARIO");
   if (punt != NULL)
   {
     j=0;
     for(i=0 ; punt[i] != '=' ; i++);
     for(i=i+1 ; punt[i] != '&' ; i++)
         { NAMEBDUSUARIO[j]=punt[i] ; j++ ; }
     NAMEBDUSUARIO[j]='\0';
   }
//---------------------------
   punt = strstr(recibe,"VERTAB");
   if (punt == NULL)
     strcpy(VERTAB,"NO\0");
   else
     strcpy(VERTAB,"SI\0");
//-----------------------
   punt = strstr(recibe,"VERATTR");
   if (punt == NULL)
     strcpy(VERATTR,"NO\0");
   else
     strcpy(VERATTR,"SI\0");
//-----------------------
   punt = strstr(recibe,"NAMETAB");
   if (punt != NULL)
   {    
     j=0;
     for(i=0 ; punt[i] != '=' ; i++);
     for(i=i+1 ; punt[i] != '&' ; i++)
         { NAMETAB[j]=punt[i] ; j++ ; }
     NAMETAB[j]='\0';
   }   
//-----------------------
   punt = strstr(recibe,"SQL");
   if (punt != NULL)
   {    
     j=0;
     for(i=0 ; punt[i] != '=' ; i++);
     for(i=i+1 ; punt[i] != '&' && punt[i] != '\0'; i++)
         { SQL[j]=punt[i] ; j++ ; }
     SQL[j]='\0';
   }          
}              

void decodificacionSqlPOST(char SQL[], char SQL_decode[])
{
  //insert into cliente(codcli,nomcli) values (3,'tres');
  //insert into cliente%28codcli%2Cnomcli%29 values %283%2C%27tres%27%29;
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
 
  char codsql[3];
  memset(codsql,0,3);
  int i ;
  int j = 0;
  for (i = 0; SQL[i] != ';' ; i++)
  {
    if (SQL[i] != '%')
    {   
      SQL_decode[j] = SQL[i]; 
      if (SQL[i] == '+')
         SQL_decode[j] = ' ';
      j++;   
    }
    else
    {
       i++;
       codsql[0]=SQL[i];
       i++;
       codsql[1]=SQL[i];
       codsql[2]='\0';
       //encontrar decode de codsql %??
       int k ;
       for(k =0;code[k][0]!='\0' && strncmp(code[k],codsql,2);k++);
       if (!strncmp(code[k],codsql,2))
                SQL_decode[j] = decode[k];
       j++;  
    }
  } 
 // printf("SQL --> %s\n",SQL);
 // printf("SQL_decode --> %s\n",SQL_decode);
}

void consulta(    const char * remote_host,
                        const char * remote_port,
                        const char * username,
                        const char * userpass,           
                        char NAMEBD[] , 
                        char SQL_consulta[], 
                        char SQL_respuesta[])
{
    memset(SQL_respuesta,'\0',1024);
  //printf("consulta--> %s\n",SQL_consulta);
     funcionMysql(remote_host,
                      remote_port,
                      username,
                      userpass,      
                      NAMEBD,
                      SQL_consulta,
                      SQL_respuesta);
  
  //printf("SQL_respuesta-->\n%s\n",SQL_respuesta);
}
//---------------------
void armarResultadoQuery(char recibe[],char mensaje[], const char * host , const char * port)
{
      char VERBD[3]   ; strcpy(VERBD,"NO\0")   ;
      char VERTAB[3]  ; strcpy(VERTAB,"NO\0")  ;
      char VERATTR[3] ; strcpy(VERATTR,"NO\0") ;
      //------------------      
      char USERNAME[512] ; memset(USERNAME,'\0',512) ;
      char USERPASS[512] ; memset(USERPASS,'\0',512) ;
      //----------------
      char NAMEBDCATALOGO[512] ; memset(NAMEBDCATALOGO,'\0',512) ;
      char NAMEBDUSUARIO[512]  ; memset(NAMEBDUSUARIO,'\0',512)  ;
      char NAMETAB[512]        ; memset(NAMETAB,'\0',512)        ;
      char SQL[1024]           ; memset(SQL,'\0',1024)            ;
         
      //busca LINEA DE DATOS
      buscarLineaDeDatos(recibe,USERNAME,USERPASS,
                         VERBD,NAMEBDCATALOGO,NAMEBDUSUARIO,
                         VERTAB,VERATTR,NAMETAB,SQL);

      char SQL_consulta[1024] ;  memset(SQL_consulta,'\0',1024) ;
      char SQL_respuesta_VERBD[1024] ; memset(SQL_respuesta_VERBD,'\0',1024) ;  
      char SQL_respuesta_NAMETAB[1024] ; memset(SQL_respuesta_NAMETAB,'\0',1024);           
      char SQL_respuesta_VERTAB[1024] ; memset(SQL_respuesta_VERTAB,'\0',1024) ;
      char SQL_respuesta_VERATTR[1024] ; memset(SQL_respuesta_VERATTR,'\0',1024) ;                
      char SQL_respuesta_SQL[1024] ; memset(SQL_respuesta_SQL,'\0',1024) ;  
      
       
//---------------------------------------------------------------------
        // Mysql o Mariadb
        
        //strcat(mensaje,"SGBD --> Mariadb/MySql<br>\0");
        if (VERBD[0] == 'S') //MOSTRAR BD
        {
          memset(SQL_consulta,'\0',1024);
          strcpy(SQL_consulta,"select schema_name from schemata\0");
          consulta(host,port,
                           USERNAME,
                           USERPASS,
                           "information_schema\0",
                           SQL_consulta,
                           SQL_respuesta_VERBD);
        }
        if (NAMEBDUSUARIO[0] != '\0' && VERTAB[0] == 'S') //MOSTRAR TABLAS
        {
          memset(SQL_consulta,'\0',1024);
          strcpy(SQL_consulta,"select table_name from tables where table_schema = \'");
          strcat(SQL_consulta,NAMEBDUSUARIO);
          strcat(SQL_consulta,"\';\0"); 
          consulta(host,port,
                           USERNAME,
                           USERPASS,
                           "information_schema\0",
                           SQL_consulta,
                           SQL_respuesta_VERTAB);
        }
        if (NAMETAB[0] != '\0') //MOSTRAR ATRIBUTOS DE LA TABLA
        {
          memset(SQL_consulta,'\0',1024);
          strcpy(SQL_consulta,"select column_name from columns where table_name = \'");
          strcat(SQL_consulta,NAMETAB);
          strcat(SQL_consulta,"\' and table_schema = \'");
          strcat(SQL_consulta,NAMEBDUSUARIO);
          strcat(SQL_consulta,"\';\0");
          consulta(host,port,
                   USERNAME,
                   USERPASS,
                   "information_schema\0",
                   SQL_consulta,
                   SQL_respuesta_NAMETAB);
        }
        if (NAMEBDUSUARIO[0] != '\0' && SQL[0] != '\0') //MOSTRAR SQL
        {
          memset(SQL_consulta,'\0',1024);
          strcat(SQL,";");
          decodificacionSqlPOST(SQL, SQL_consulta);
          strcat(SQL_consulta,";\0");
          consulta(host,port,
                   USERNAME,
                   USERPASS,
                   NAMEBDUSUARIO,
                   SQL_consulta,
                   SQL_respuesta_SQL);
        }
      
       strcat(mensaje,"BASES DE DATOS<br>");
       strcat(mensaje,SQL_respuesta_VERBD);
       strcat(mensaje,"<br>TABLAS de ---> ");
       if (VERTAB[0] == 'S')
          {strcat(mensaje,NAMEBDUSUARIO) ; strcat(mensaje,"<br>");}
       strcat(mensaje,SQL_respuesta_VERTAB);
       strcat(mensaje,"<br>ATRIBUTOS de ---> ");
       strcat(mensaje,NAMETAB) ; strcat(mensaje,"<br>");
       strcat(mensaje,SQL_respuesta_NAMETAB);
       strcat(mensaje,"<br>RESPUESTA AL SQL<br>");
       strcat(mensaje,SQL_respuesta_SQL);
//     }
//    }
//    send(idsockc,mensaje,strlen(mensaje),0); 
}

