

#include <fcntl.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_NAME "shared_memory"
#define SHM_SIZE 1024
#define SEM_NAME "/my_semaphore"

int counter = 0;

void sigint_handler(int signum) {
  printf("\nПолучен сигнал SIGINT (Ctrl+C)\n");
  printf("Количество обработанных наборов данных: %d\n", counter);
  printf("Завершение программы...\n");
  exit(0);
}

int MaxNum(int *array, int size_array) {
  int max = array[1];
  for (int i = 1; i < size_array; i++) {
    if (array[i] > max) max = array[i];
  }
  return max;
}

int MinNum(int *array, int size_array) {
  int min = array[1];
  for (int i = 1; i < size_array; i++) {
    if (array[i] < min) min = array[i];
  }
  return min;
}

int main() {
  sem_t *semid = sem_open(SEM_NAME_WRITER, O_CREAT | O_EXCL, 0666, 1);
  int *shm_ptr;
  int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);

  if (shm_fd == -1) {
    perror("shm_open");
    exit(1);
  }

  if (ftruncate(shm_fd, SHM_SIZE) == -1) {
    perror("ftruncate");
    exit(1);
  }

  shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (shm_ptr == MAP_FAILED) {
    perror("mmap");
    exit(1);
  }

  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
    return 1;
  }
  if (pid == 0) {
    while (1) {
      sem_wait(semid);
      int size_array = shm_ptr[0];
      shm_ptr[1] = MaxNum(shm_ptr, size_array);
      shm_ptr[2] = MinNum(shm_ptr, size_array);
      printf("Дочерний процесс отработал\n");
      sem_post(semid);
      sleep(1);
    }
  } else {
    signal(SIGINT, sigint_handler);
    for (int i = 0;; i++) {
      int size_array = rand() % 10;
      if (i % 2 == 0) {
        sem_wait(semid);

        for (int i = 1; i < size_array; i++) {
          shm_ptr[i] = rand() % 15;
        }
        shm_ptr[0] = size_array;
        printf("отработал\n");
        sem_post(semid);
      } else {
        sleep(1);
        sem_wait(semid);
        for (int i = 0; i < size_array; i++) {
          printf("Элемент %d: %d\n", i, shm_ptr[i]);
        }
        printf("Максимальное значение:%d\n", shm_ptr[1]);
        printf("Минимальное значение:%d\n", shm_ptr[2]);
        sem_post(semid);
        counter++;
      }
    }

    sem_destroy(semid);
    if (munmap(shm_ptr, SHM_SIZE) == -1) {
      perror("munmap");
      exit(1);
    }

    if (shm_unlink(SHM_NAME) == -1) {
      perror("shm_unlink");
      exit(1);
    }

    return 0;
  }
}