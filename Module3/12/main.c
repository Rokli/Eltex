#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define KEY 123
#define SIZE_SHM sizeof(int)

void P(int semid) {
  struct sembuf lock_res = {0, -1, 0};
  semop(semid, &lock_res, 1);
}

void V(int semid) {
  struct sembuf rel_res = {0, 1, 0};
  semop(semid, &rel_res, 1);
}

int MaxNum(int *array,int size_array) {
  int max = array[1];
  for (int i = 1; i < size_array; i++) {
    if (array[i] > max) max = array[i];
  }
  return max;
}

int MinNum(int *array,int size_array) {
  int min = array[1];
  for (int i = 1; i < size_array; i++) {
    if (array[i] < min) min = array[i];
  }
  return min;
}

int main() {
  int semid = semget(KEY, 1, IPC_CREAT | 0666);
  int shmid = shmget(KEY, SIZE_SHM, IPC_CREAT | 0666);

  semctl(semid, 0, SETVAL, 1);

  if (shmid == -1) {
    perror("shmget");
    exit(1);
  }

  int *shared_memory = (int *)shmat(shmid, NULL, 0);
  if (shared_memory == (int *)-1) {
    perror("shmat");
    exit(1);
  }

  pid_t pid = fork();

  if (pid == -1) {
    perror("fork");
    return 1;
  }

  srand(time(NULL));
  
  if (pid == 0) {
    while(1){
        P(semid);
        int size_array = shared_memory[0];
        shared_memory[1] = MaxNum(shared_memory,size_array);
        shared_memory[2] = MinNum(shared_memory,size_array);
        printf("Дочерний процесс отработал\n");
        V(semid);
        sleep(1);
    }

  } else {
    for (int i = 0;; i++) {
       int size_array = rand() % 10;
      if (i%2 == 0) {
        P(semid);
       

        for (int i = 1; i < size_array; i++) {
          shared_memory[i] = rand() % 15;
        }
        shared_memory[i] = size_array;
        printf("отработал\n");
        V(semid);
      } else {

        sleep(1);
        P(semid);
        for (int i = 0; i < size_array; i++) {
          printf("Элемент %d: %d\n", i, shared_memory[i]);
        }
        printf("Максимальное значение:%d\n",shared_memory[1]);
        printf("Минимальное значение:%d\n",shared_memory[2]);
        V(semid);
      }

      
    }
  }

  shmdt(shared_memory);
  shmctl(shmid, IPC_RMID, NULL);
  return 0;
}