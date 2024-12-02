#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
   printf("HTTP/1.1 200 OK\n");
   printf("Content-type: text/html\n\n");

   printf("<meta charset= \"utf-8\">\n");
   printf("Acceso al Servidor Ver Archivos del pwd del Servidor<br>\n"); 
   printf("---------------------------------------<br>\n");
   printf("<HTML><BODY>\n");
   printf("<form method=\"POST\" action=\"ar001.cgi\">\n");
printf("<INPUT TYPE=\"HIDDEN\" ID=\"MISDATOS\" NAME=\"MISDATOS\" VALUE=\"SI\"/>"); 
   printf("<br>\n");
   printf("<label for=\"ARCHIVO\">Ingrese el nombre de un archivo:</label>\n");
   printf("<INPUT TYPE=\"text\" id=\"ARCHIVO\" NAME=\"ARCHIVO\"><br>\n");
    
 printf("<input type=\"button\" value=\"Anterior\" onClick=\"history.go(-1);\">");
   printf("<input type=\"submit\" value=\"Enviar\"/><br>\n");
   printf("</form></body></html>\n");

   return 0;
 }
