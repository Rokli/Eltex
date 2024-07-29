#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_LENGTH_CHAR 128

void stop(int semid) {
    struct sembuf stop = {0, -1, 0}; 
    semop(semid, &stop, 1);
}

void start(int semid) {
    struct sembuf start = {0, 1, 0}; 
    semop(semid, &start, 1);
}

int main(int argc, char *argv[]) {
    key_t key = ftok("/etc/fstab", getpid());; 
    int semid = semget(key, 3, IPC_CREAT | 0666); 
    
    semctl(semid, 0, SETVAL, 1); 
    
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
        close(pipe_fd[0]); 
        while (1) { 
            sleep(1);
            stop(semid); 

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

            srand(time(NULL)); 
            int random_number = rand() % 100; 
            write(pipe_fd[1], &random_number, sizeof(random_number));
            start(semid);
        }
        close(pipe_fd[1]); 
        return 0;
    } else { 
        close(pipe_fd[1]); 
        while (1) { 
            sleep(2);
            stop(semid);
            FILE *file = fopen("random_numbers.txt", "a");
            if (file == NULL) {
                perror("Файл не открылся");
                exit(1); 
            }

            int received_number;
            read(pipe_fd[0], &received_number, sizeof(received_number));
            fprintf(file, "%d\n", received_number);
            
            fclose(file); 

            start(semid);
        }
        wait(NULL); 
        close(pipe_fd[0]); 
    }
    semctl(semid, 0, IPC_RMID);
    return 0;
}
