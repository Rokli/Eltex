#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){

    if (argc != 2) {
        printf("Использование: <количество чисел>\n");
        return 1;
    }

    int count = atoi(argv[1]);
    if (count <= 0) {
        printf("Количество числе должно быть больше нуля\n");
        return 1;
    }

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

    if(pid == 0){
        close(pipe_fd[0]); 

        srand(time(NULL)); 
        for (int i = 0; i < count; i++) {
            int random_number = rand() % 100; 
            write(pipe_fd[1], &random_number, sizeof(random_number));
        }

        close(pipe_fd[1]); 
        return 0;
    } else { 
        close(pipe_fd[1]); 

        int received_number;
        for (int i = 0; i < count; i++) {

            FILE *file = fopen("random_numbers.txt", "a");

            if (file == NULL) {
                perror("Файл не открылся");
                return 1;
            }
            
            read(pipe_fd[0], &received_number, sizeof(received_number));
            printf("Полученное число: %d\n", received_number);
            fprintf(file, "%d\n", received_number);

            fclose(file);
        }
        close(pipe_fd[0]); 
    }


    return 0;
}