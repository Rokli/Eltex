#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define SHM_KEY 123
#define SIZE_SHM sizeof(int) 

int main(){

    int shmid = shmget(SHM_KEY, SIZE_SHM, IPC_CREAT | 0666);

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    int *shared_memory = (int *)shmat(shmid, NULL, 0);
    if (shared_memory == (int*)-1) {
      perror("shmat");
      exit(1);
    }

    pid_t pid = fork();

    if(pid == -1){
        perror("fork");
        return 1;
    }
    
    if(pid == 0){
        *shared_memory = 5;
    }else{
        wait(NULL);
        printf("Сообщение из разделяемой памяти: %d\n", *shared_memory);
    }

    shmdt(shared_memory); 
    shmctl(shmid, IPC_RMID, NULL); 
    return 0;
}