// Combinación entre código y pseudocódigo, que me paso Fleitas

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>

// Variables globales
int salir = 0;
char letra = 'a';

// Prototipos de funciones
void f_sigusr1(int);
void f_alarm(int);

int main(void) {
    signal(SIGUSR1, f_sigusr1);
    signal(SIGALRM, f_alarm);
    alarm(60); // 1 minuto. Creo que se escribe acá 
    while (!salir) pause();
    return 0;
}

void f_sigusr1(int s) { // Supuestamente no imprime 's'
    if (letra == 'z') letra = 'A';
    else if (letra == 'Z') letra = 'a';
    printf("%c\n", letra);
    letra++;
}

void f_alarm(int s) {
    salir = 1;
}