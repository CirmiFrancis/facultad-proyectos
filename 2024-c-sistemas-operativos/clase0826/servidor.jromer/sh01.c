#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
   printf("HTTP/1.1 200 OK\n");
   printf("Content-type: text/html\n\n");

   printf("<meta charset= \"utf-8\">\n");
   printf("Acceso al Servidor Linux<br>\n"); 
   printf("---------------------------------------<br>\n");
   printf("<HTML><BODY>\n");
   printf("<form method=\"POST\" action=\"sh001.cgi\">\n");
   printf("<INPUT TYPE=\"HIDDEN\" ID=\"MISDATOS\" NAME=\"MISDATOS\" VALUE=\"SI\"/> Linea de comandos Linux <br>\n");
   printf("<label for=\"COMANDO\">Ingrese comando:</label>\n");
   printf("<INPUT TYPE=\"text\" id=\"COMANDO\" NAME=\"COMANDO\"><br>\n");
    
 printf("<input type=\"button\" value=\"Anterior\" onClick=\"history.go(-1);\">");
   printf("<input type=\"submit\" value=\"Enviar\"/><br>\n");
   printf("</form></body></html>\n");

   return 0;
 }
