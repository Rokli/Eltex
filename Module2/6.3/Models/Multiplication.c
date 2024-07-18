#include "Operations.h"

double Multiplication(int count, double numbers[]){
    int result = numbers[0];

    for(int i = 1; i < count; i++){
        result *= numbers[i];
    }

    return result;
}