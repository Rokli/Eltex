

#include <errno.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define SEM_NAME "/mysem"
#define MAX_LENGTH_CHAR 128

int main(int argc, char *argv[]) {
  sem_t *sema_n;

  sem_close(sema_n);
  sem_unlink(SEM_NAME);

  if ((sema_n = sem_open(SEM_NAME, O_CREAT, 0600, 1)) == SEM_FAILED) {
    perror("sem_open");
    return -1;
  }

  if (argc != 2) {
    printf("main.c: <количество чисел>\n");
    fflush(stdout);
    return 1;
  }

  int max_numbers = atoi(argv[1]);

  int pipe_fd[2];
  if (pipe(pipe_fd) == -1) {
    perror("pipe");
    return 1;
  }

  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
    return 1;
  }

  if (pid == 0) {
    srand(time(NULL));
    close(pipe_fd[0]);
    for (int i = 0; i < max_numbers; i++) {
      sem_wait(sema_n);
      FILE *file = fopen("random_numbers.txt", "r");
      char name[MAX_LENGTH_CHAR];

      if (!file) {
        perror("Файл не открылся");
        exit(1);
      }

      while (fscanf(file, "%s", name) != EOF) {
        printf("%s\n", name);
        fflush(stdout);
      }
      fclose(file);

      int random_number = rand() % 500;
      if (write(pipe_fd[1], &random_number, sizeof(int)) == -1) {
        perror("write");
        return 1;
      }

      sem_post(sema_n);
      usleep(1000);
    }
    close(pipe_fd[1]);
    return 0;
  } else {
    close(pipe_fd[1]);

    for (int i = 0; i < max_numbers; i++) {
      usleep(1000);
      sem_wait(sema_n);
      int received_number;

      FILE *file = fopen("random_numbers.txt", "a");
      if (file == NULL) {
        perror("Файл не открылся");
        exit(1);
      }
      if (read(pipe_fd[0], &received_number, sizeof(int)) == -1) {
        perror("read");
        return 1;
      }

      fprintf(file, "%d\n", received_number);
      fclose(file);
      sem_post(sema_n);
    }
    wait(NULL);
    close(pipe_fd[0]);
    return 0;
  }

  sem_close(sema_n);
  sem_unlink(SEM_NAME);

  return 0;
}
