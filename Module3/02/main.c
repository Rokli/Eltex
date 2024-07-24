#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define BUFFER_SIZE 128 




int main(){

    char input[BUFFER_SIZE]; 

    while(1){
        printf(">>");

        fgets(input, BUFFER_SIZE, stdin);
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0) {
            printf("Выход из интерпретатора.\n");
            break;
        }

        char *args[10]; 
        int i = 0;

        char *token = strtok(input, " ");
        while (token != NULL && i < 10) {
            args[i] = token;
            token = strtok(NULL, " ");
            i++;
        }

        args[i] = NULL; 

        int pid;
        pid = fork();

        if(pid == 0){
            if (strcmp(args[0], "sum") == 0) {
                execvp("./sum", args);
            } else if (strcmp(args[0], "concat") == 0) {
                execvp("./concat", args);
            } else if (strcmp(args[0], "max") == 0) {
                execvp("./max", args);
            } else {
                printf("Неизвестная команда.\n");
            }
        }else{
            wait(NULL);
        }

    }


    return 0;
}