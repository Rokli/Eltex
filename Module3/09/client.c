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
#include <string.h>

#define KEY 20
#define MAX_SEM 5
#define MAX_LENGTH_CHAR 128
#define FILE_NAME "random_numbers.txt"

void P(int semid, int num_sef) {
  struct sembuf lock_res = {num_sef, -1, 0};
  semop(semid, &lock_res, 1);
}

void V(int semid, int num_sef) {
  struct sembuf rel_res = {num_sef, 1, 0};
  semop(semid, &rel_res, 1);
}

void ReadFile(){
    FILE *file = fopen(FILE_NAME, "r");
    char name[MAX_LENGTH_CHAR];

    if (!file) {
      perror("Файл не открылся");
      exit(1);
    }

    while (fscanf(file, "%s", name) != EOF) {
      printf("%s\n", name);
    }

    fclose(file);
}
int main() {
  int semid = semget(KEY, 2, IPC_CREAT | 0666);
  int fd_fifo;  
  char *buffer;
  
  if (semid == -1) {
    perror("semget");
    exit(EXIT_FAILURE);
  }

  // if((mkfifo("/tmp/fifo0001.1", O_RDWR)) == -1){

  //   fprintf(stderr, "Невозможно создать fifo\n");

  //   exit(0);

  // } 

  srand(time(NULL));
  while (1) {
    for (int i = 1; i <= MAX_SEM; i++) {
      pid_t pid = fork();
      
      if (pid == 0) {

        P(semid, 0);
        sleep(2);
        ReadFile();
        
        if((fd_fifo=open("/fifo0001.1", O_RDWR)) == - 1){
          fprintf(stderr, "Невозможно открыть fifo\n");
          exit(0);
        } 

        int random_number = rand() % 500;
        char ch = (char)random_number;
        strcpy(buffer,&ch);
        write(fd_fifo,buffer,sizeof(int)); 
        // printf("%d",random_number);

        if (i == MAX_SEM) {
          V(semid, 1);
          i = 1;
        }
        return 0;
      }
    }
  }
  semctl(semid, 0, IPC_RMID);
  return 0;
}
