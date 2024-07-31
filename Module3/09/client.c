

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>

#define KEY 20
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

  if (semid == -1) {
    perror("semget");
    exit(EXIT_FAILURE);
  }

  while (1) {
    for (int i = 1; i <= MAX_SEM; i++) {
      pid_t pid = fork();
      if (pid == 0) {
        P(semid, 0);
        sleep(2);
        printf("Клиент %d\n", i);
        fflush(stdout);

        if (i == MAX_SEM) {
          V(semid, 1);
          fflush(stdout);
          i = MAX_SEM;
        }
        V(semid, 0);
      }
    }
  }
  semctl(semid, 0, IPC_RMID);
  return 0;
}
