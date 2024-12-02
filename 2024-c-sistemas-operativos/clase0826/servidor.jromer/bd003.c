#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_post_data(char [], int );

int main(void) 
{
    char post_data[1024]; 
    memset(post_data,'\0',1024);
    
    int len;

    // Obtener la longitud de los datos POST
    char * lenstr = getenv("CONTENT_LENGTH");
    if (lenstr != NULL) {
        len = atoi(lenstr);
    } else {
        len = 0;
    }

    // Leer los datos POST
    if (len > 0) {
        read_post_data(post_data, len);
    }

    // Generar la respuesta
    printf("HTTP/1.1 200 OK\n");
    printf("Content-type: text/html\n\n");
    
    printf("<meta charset= \"utf-8\">\n");
    printf("<html><head><title>Datos Recibidos</title></head><body>");
    printf("<h1>Datos Recibidos</h1>");
    printf("<p>%s %s</p>", post_data,lenstr);
    printf("</body></html>");

    return 0;
}


void read_post_data(char post_data[], int length) {
    int i;
    for (i = 0; i < length; i++) {
        post_data[i] = fgetc(stdin);
    }
    post_data[i] = '\0';
}
