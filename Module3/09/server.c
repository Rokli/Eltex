#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h> 
#include <fcntl.h> 

#define KEY 20
#define MAX_LENGTH_CHAR 128
#define MAX_SEM 5

void P(int semid, int num_sef) {
  struct sembuf lock_res = {num_sef, -1, 0};
  semop(semid, &lock_res, 1);
}

void V(int semid, int num_sef) {
  struct sembuf rel_res = {num_sef, 1, 0};
  semop(semid, &rel_res, 1);
}

void VClient(int semid) {
  struct sembuf rel_res = {0, 5, 0};
  semop(semid, &rel_res, 1);
}

int main() {
  int semid = semget(KEY, 2, IPC_CREAT | 0666);
  int fd_fifo;
  semctl(semid, 0, SETVAL, MAX_SEM);
  semctl(semid, 1, SETVAL, 0);

  unlink("/fifo0001.1");

  if((mkfifo("/fifo0001.1", 0666)) == -1){

    fprintf(stderr, "Невозможно создать fifo\n");
    perror("123");
    exit(0);

  } 

  while (1) {
    P(semid, 1);
    int received_number;

    if((fd_fifo=open("/fifo0001.1", O_RDWR)) == - 1){
      fprintf(stderr, "Невозможно открыть fifo\n");
      exit(0);
    } 
    if(read(fd_fifo,&received_number,sizeof(int)) == -1);
    // FILE *file = fopen("random_numbers.txt", "a");
    // if (file == NULL) {
    //   perror("Файл не открылся");
    //   exit(1);
    // }

    // fprintf(file, "%d\n", received_number);
    // fclose(file);

    VClient(semid);
  }
  semctl(semid, 1, IPC_RMID);
  return 0;
}
