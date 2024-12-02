/*
  Compilacion desde la linea de comandos
  gcc AccesoPostgresql.c -Wall -g -c -lpq -I/usr/include/postgresql/ 
*/

#include <string.h>
#include "/usr/include/postgresql/libpq-fe.h"

#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>


void funcionPostgresql(const char * host ,
                       const char * puerto ,
                       const char * username ,
                       const char * userpass ,
                       char dbname[],char query[],char respuesta[])
{
   PGconn *conn;
   PGresult *res;
   int i,j;
   conn = PQsetdbLogin(host,puerto,NULL,NULL,dbname,username,userpass);
   if (PQstatus(conn) != CONNECTION_BAD)
    {
     // printf("funcionPostgresql dice %s %s\n",bufnomb,bufquery);
      res = PQexec(conn, query);
      if (res != NULL && PGRES_TUPLES_OK == PQresultStatus(res))
         { 
           strcat(respuesta,"[");                     
           for (i = 0 ; i <= PQntuples(res)-1;  i++)
             {
                strcat(respuesta,"( ");                     
                for (j = 0 ; j < PQnfields(res); j++)
                    {
                      strcat(respuesta,PQgetvalue(res,i,j));
                      strcat(respuesta," ");                     
                    }
                strcat(respuesta,")");
             }
             strcat(respuesta,"]<br>\0");                
             PQclear(res);
         }
    }
    else
    {
      strcat(respuesta," *** Fallo conexion postgresql ***\n");
    }
    PQfinish(conn);
}

