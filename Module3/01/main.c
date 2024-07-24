#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int calculateSquareArea(int sideLength) {
    return sideLength * sideLength;
}

int main(int argc, char *argv[]) {

    if(argc ==1 ){
        printf("Использование: %s <длина стороны n> ... \n", argv[0]);
        return 1;
    }
    
    int sides[argc-1],pid;
    int middle = argc / 2;

    for(int i = 1; i < argc; i++){
        sides[i-1] = atoi(argv[i]);
    }

    switch (pid = fork()) {
        case -1:
            perror("fork"); 
            exit(1); 
        case 0:
            printf("Процесс-потомок:\n");
            for(int i = 0; i < middle; i++){
                printf("Площадь квадрата:%d\tСторона:%d\n",calculateSquareArea(sides[i]),sides[i]);
            }
            break;
        default:
            printf("Процесс-родитель:\n");
            for(int i = middle; i < argc-1; i++){
                printf("Площадь квадрата:%d\tСторона:%d\n",calculateSquareArea(sides[i]),sides[i]);
            }
            break;
}
    return 0;
}