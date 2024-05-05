#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>

main(void) {
    char frase[24] = "Hola Querido Mundo 2012\0";
    pid_t pid;
    int i ;
    for(i = 0 ; i < 23 ; i ++) {
        pid = fork();
        if (pid > 0) {
            printf("%d = %c\n",getpid(),frase[i]);
            break;
        }
    }
    exit(0);
}