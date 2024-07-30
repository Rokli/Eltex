#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <wait.h>
#include <time.h>

#define MAX_LENGTH_CHAR 128

union semun {
    int val; /* значение для SETVAL */
    struct semid_ds *buf; /* буферы для IPC_STAT, IPC_SET */
    unsigned short *array; /* массивы для GETALL, SETALL */
                           /* часть, особенная для Linux: */
    struct seminfo *__buf; /* буфер для IPC_INFO */
};

void P(int semid){
    struct sembuf lock_res = {0, -1, 0};
    semop(semid, &lock_res, 1);
}

void V(int semid){
    struct sembuf rel_res = {0, 1, 0};
    semop(semid, &rel_res, 1);
}
int main(int argc, char *argv[]) {
    key_t key = ftok("module3", getpid());
    int semid;
    semid = semget(key, 0, 0666 | IPC_CREAT);

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
        srand(time(NULL));
        close(pipe_fd[0]); 
        while (1) { 
            sleep(2);
            P(semid);
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

            int random_number = rand() % 500;
            write(pipe_fd[1], &random_number, sizeof(random_number));
            V(semid);
        }
        close(pipe_fd[1]); 
        return 0;
    } else { 
        close(pipe_fd[1]); 
        while (1) { 
            sleep(3);
            P(semid);
            int received_number;

            FILE *file = fopen("random_numbers.txt", "a");
            if (file == NULL) {
                perror("Файл не открылся");
                exit(1); 
            }

            read(pipe_fd[0], &received_number, sizeof(received_number));
            fprintf(file, "%d\n", received_number);
            
            fclose(file); 
            
            V(semid);
        }
        wait(NULL); 
        close(pipe_fd[0]); 
    }

    return 0;
}
