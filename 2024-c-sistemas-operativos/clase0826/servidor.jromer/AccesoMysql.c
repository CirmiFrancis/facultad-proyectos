
/*
  Compilacion desde la linea de comandos para crear el progrma objeto AccesoMysql.o
  gcc AccesoMysql.c -Wall -g -c -L/usr/lib/mysql -lmariadbclient 
*/


#include "/usr/include/mariadb/mysql.h"

#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void funcionMysql(const char * host , const char * puerto , const char * username , const char * passname , char dbname[],char query[],char respuesta[])
{
        MYSQL *conn; // variable de conexión para MySQL 
	MYSQL_RES *res; // variable que contendra el resultado de la consuta 
	MYSQL_ROW row; // variable que contendra los campos por cada registro consultado 
        conn = mysql_init(NULL); // inicializacion a nula la conexión 

     //   memset(respuesta,0,1024);

	/* conectar a la base de datos */
	if (!mysql_real_connect(conn, host, username, passname, dbname, 0, NULL, 0))
	{ /* definir los parámetros de la conexión antes establecidos */
		sprintf(respuesta, "%s\n", mysql_error(conn)); /* si hay un error definir cual fue dicho error */
   //               strcat(respuesta,"\0");  
	}
        else
         {
	    /* enviar consulta SQL */
//	    if (mysql_query(conn, "select * from tabla01"))
            if (mysql_query(conn, query))		
              { /* definicion de la consulta y el origen de la conexion */
		sprintf(respuesta, "%s\n", mysql_error(conn));
 //                 strcat(respuesta,"\0");  
	      }
            else
              {
                 res = mysql_use_result(conn);
                 int num_attrib = mysql_num_fields(res);
	         strcat(respuesta,"[");
                 while ((row = mysql_fetch_row(res)) != NULL)
                   { 
                    /* recorrer la variable res con todos los registros obtenidos para su uso */
	            // printf("%s\t%s\t%s \n", row[0],row[1]); /* la variable row se convierte en un arreglo por el numero de campos que hay en la tabla */
                    strcat(respuesta,"( "); 
                    int i ;
                    for (i = 0 ; i < num_attrib ; i++)
                      {                   
                       strcat(respuesta,row[i]);
                       strcat(respuesta," ");
                      }
                    strcat(respuesta,")");     
                   }
                 strcat(respuesta,"]<br>\0");     
               	 mysql_free_result(res);                
              }
            }
        /* se libera la variable res y se cierra la conexión */
	mysql_close(conn);
}

