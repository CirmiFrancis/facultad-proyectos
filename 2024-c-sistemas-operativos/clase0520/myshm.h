#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h> // memoria compartida
#include <sys/sem.h> // semaforos system V  SVR4

int semWait(int sem_id,int sem_num);
int semSignal(int sem_id, int sem_num);
