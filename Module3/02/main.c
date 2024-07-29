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
            char *file = malloc(strlen("./") + strlen(args[1]) + 1);
            strcpy(file, "./");
            strcat(file, args[0]);
            execvp(file, args);
        }else{
            wait(NULL);
        }

    }


    return 0;
}