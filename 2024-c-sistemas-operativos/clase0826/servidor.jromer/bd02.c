#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
   printf("HTTP/1.1 200 OK\n");
   printf("Content-type: text/html\n\n");

   printf("<meta charset= \"utf-8\">\n");
   printf("Acceso a bases de datos Mariadb/Mysql<br>\n"); 
   printf("-----------------------------------------------<br>\n");
   printf("<HTML><BODY>\n");
   printf("<form method=\"POST\" action=\"bd002.cgi\">\n");
   printf("<INPUT TYPE=\"HIDDEN\" ID=\"MISDATOS\" NAME=\"MISDATOS\" VALUE=\"SI\"/> SGBD  Mysql/Mariadb<br>\n");

   printf("<label for=\"USERNAME\">Ingrese usuario:</label>\n");
   printf("<INPUT TYPE=\"text\" id=\"USERNAME\" NAME=\"USERNAME\"><br>\n");

   printf("<label for=\"USERPASS\">Ingrese contrseña:</label>\n");
   printf("<INPUT TYPE=\"PASSWORD\" id=\"USERPASS\" NAME=\"USERPASS\"><br>\n");

   printf("<label for=\"VERBD\">Mostrar BD</label>\n");
   printf("<INPUT TYPE=\"CHECKBOX\" ID=\"VERBD\" NAME=\"VERBD\" VALUE=\"SI\"/> <br>\n");

   printf("<label for=\"NAMEBDCATALOGO\">Si es necesario ingrese el nombre de una BD de catálogo:</label>\n");
   printf("<INPUT TYPE=\"TEXT\" ID=\"NAMEBDCATALOGO\"  NAME=\"NAMEBDCATALOGO\"><br>\n"); 

   printf("<label for=\"VERTAB\">Mostrar Tablas</label>\n");
  printf("<INPUT TYPE=\"CHECKBOX\" ID=\"VERTAB\" NAME=\"VERTAB\" VALUE=\"SI\"/> <br>\n");

   printf("<label for=\"NAMEBDUSUARIO\">Ingrese el nombre de una BD de usuario:</label>\n");
  printf("<INPUT TYPE=\"TEXT\" id=\"NAMEBDUSUARIO\"  NAME=\"NAMEBDUSUARIO\"><br>\n"); 

   printf("<label for=\"VERATTR\">Mostrar Atributos</label>\n");
  printf("<INPUT TYPE=\"CHECKBOX\" ID=\"VERATTR\" NAME=\"VERATTR\" VALUE=\"SI\"/> <br>\n");

   printf("<label for=\"NAMETAB\">Ingrese nombre de la tabla:</label>\n");
  printf("<INPUT TYPE=\"TEXT\" id=\"NAMETAB\" NAME=\"NAMETAB\"><br>\n");

   printf("<label for=\"SQL\">Ingrese una sentencia SQL:</label>\n");
  printf("<INPUT TYPE=\"TEXT\" id=\"SQL\" NAME=\"SQL\"><br>\n");

 printf("<input type=\"button\" value=\"Anterior\" onClick=\"history.go(-1);\">");
  printf("<input type=\"submit\" value=\"Enviar\"/><br>\n");
  printf("</form></body></html>\n");

  exit(0);
 }
