#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>

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

int main() {
  int semid = semget(KEY, 2, IPC_CREAT | 0666);

  semctl(semid, 0, SETVAL, MAX_SEM);
  semctl(semid, 1, SETVAL, 0);

  while (1) {
    sleep(1);
    P(semid, 1);
    FILE *file = fopen("random_numbers.txt", "r");
    char name[MAX_LENGTH_CHAR];

    if (!file) {
      perror("Файл не открылся");
      exit(1);
    }

    while (fscanf(file, "%s", name) != EOF) {
      printf("%s\n", name);
    }

    fclose(file);
    fflush(stdout);
  }
  semctl(semid, 1, IPC_RMID);
  return 0;
}
