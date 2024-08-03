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

#define SEM_NAME_READER "/myreader"
#define SEM_NAME "/mysem"
#define MAX_LENGTH_CHAR 128
#define MAX_FORK 4

int main(int argc, char *argv[]) {
  sem_t *sema_reader;
  sem_t *sema_write;

  if ((sema_reader = sem_open(SEM_NAME, O_CREAT, 0600, MAX_FORK)) ==
      SEM_FAILED) {
    perror("sem_open reader");
    exit(1);
  }

  if ((sema_write = sem_open(SEM_NAME_READER, O_CREAT, 0600, 1)) ==
      SEM_FAILED) {
    perror("sem_open writer");
    exit(1);
  }

  if (argc != 2) {
    printf("Usage: %s <количество чисел>\n", argv[0]);
    return 1;
  }

  int max_numbers = atoi(argv[1]);
  int pipe_fd[2];

  if (pipe(pipe_fd) == -1) {
    perror("pipe");
    return 1;
  }

  for (int j = 0; j < MAX_FORK; j++) {
    pid_t pid = fork();
    if (pid < 0) {
      perror("fork");
      return 1;
    }

    if (pid == 0) {
      srand(getpid() ^ time(NULL));
      close(pipe_fd[0]);

      for (int i = 0; i < max_numbers; i++) {
        sem_wait(sema_reader);
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
          exit(1);
        }
        sem_post(sema_reader);
        sem_post(sema_write);
        usleep(1000);
      }

      close(pipe_fd[1]);
      exit(0);
    }
  }
  close(pipe_fd[1]);

  for (int i = 0; i < MAX_FORK+1; i++) {
    sem_wait(sema_write);
    sem_wait(sema_reader);
    int received_number;

    if (read(pipe_fd[0], &received_number, sizeof(int)) == -1) {
      perror("read");
      return 1;
    }

    FILE *file = fopen("random_numbers.txt", "a");
    if (file == NULL) {
      perror("Файл не открылся");
      exit(1);
    }

    fprintf(file, "%d\n", received_number);
    fclose(file);
    sem_post(sema_reader);
  }

  for (int j = 0; j < MAX_FORK; j++) {
    wait(NULL);
  }

  close(pipe_fd[0]);

  sem_close(sema_reader);
  sem_close(sema_write);
  sem_unlink(SEM_NAME);
  sem_unlink(SEM_NAME_READER);

  return 0;
}