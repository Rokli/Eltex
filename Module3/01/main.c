#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

float calculateSquareArea(float sideLength) {
    return sideLength * sideLength;
}

int main(int argc, char *argv[]) {

    int sides[argc-1],pid;

    for(int i = 1; i < argc; i++){
        sides[i-1] = atoi(argv[i]);
    }

    switch (pid = fork()) {
        case -1:
            perror("fork"); 
            exit(1); 
        case 0:
            printf("Процесс-потомок:\n");
        default:
                printf("Это процесс-родитель:\n");
}
    return 0;
}