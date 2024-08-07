#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_LENGTH_CHAR 128

volatile sig_atomic_t access_flag = 0; 

void sigusr1_handler(int signum) {
    access_flag = 1; 
}

void sigusr2_handler(int signum) {
    access_flag = 0; 
}

int main(int argc, char *argv[]) {
    signal(SIGUSR1, sigusr1_handler);
    signal(SIGUSR2, sigusr2_handler);
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
            while (!access_flag) {
                pause(); 
            }

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
            if (write(pipe_fd[1], &random_number, sizeof(random_number)) == -1) {
                perror("write");
                return 1;
            }

            sleep(2);
        }
        close(pipe_fd[1]); 
        return 0;
    } else { 
        close(pipe_fd[1]); 
        while (1) { 
            kill(pid, SIGUSR1); 

            int received_number;

            FILE *file = fopen("random_numbers.txt", "a");
            if (file == NULL) {
                perror("Файл не открылся");
                exit(1); 
            }

            if (read(pipe_fd[0], &received_number, sizeof(received_number)) == -1) {
                perror("read");
                return 1;
            }

            fprintf(file, "%d\n", received_number);
            
            fclose(file); 
            kill(pid, SIGUSR2);
            sleep(3);
        }
        wait(NULL); 
        close(pipe_fd[0]); 
    }

    return 0;
}
