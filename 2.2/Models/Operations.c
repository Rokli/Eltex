#include "Operations.h"

double Summ(int count, double numbers[] ){
    int result = 0;

    for(int i = 0; i < count; i++){
        result += numbers[i];
    }

    return result;
}

double Difference(int count, double numbers[]){
    int result = 0;

    for(int i = 0; i < count; i++){
        result -= numbers[i];
    }

    return result;
}   

double Multiplication(int count, double numbers[]){
    int result = numbers[0];

    for(int i = 1; i < count; i++){
        result *= numbers[i];
    }

    return result;
}
double Division(int count, double numbers[]){
    int result = numbers[0];
    
    for(int i = 1; i < count; i++){
        if(numbers[i] == 0){
            printf("На ноль делить нельзя, деление прекращено\n");
            break;
        }
        result /= numbers[i];
    }

    return result;
}
