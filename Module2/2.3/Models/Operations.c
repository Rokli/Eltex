#include "Operations.h"

double Summ(int amount, ...){
    double result = 0;

    va_list list;
    va_start(list, amount);

    for (int i = 0; i < amount; i++) {
        result += va_arg(list, double); 
    }

    va_end(list);
    return result;
}

double Difference(int amount, ...){
    double result = 0;

    va_list list;
    va_start(list, amount);

    for (int i = 0; i < amount; i++) {
        result -= va_arg(list, double); 
    }

    va_end(list);
    return result;
}   

double Multiplication(int amount, ...){
    double result = 1;

    va_list list;
    va_start(list, amount);

    for (int i = 0; i < amount; i++) {
        result *= va_arg(list, double); 
    }

    va_end(list);
    return result;
}
double Division(int amount, ...){
    double result = 1;

    va_list list;
    va_start(list, amount);

    for (int i = 0; i < amount; i++) {
        result /= va_arg(list, double); 
    }

    va_end(list);
    return result;
}

double MaxInNumbers( int amount, ... ){
    double max = 0;

    va_list list;
    va_start(list, amount);

    for (int i = 0; i < amount; i++) {
        double tmp = va_arg(list, double);
        if(tmp > max) max = tmp;
    }

    va_end(list);
    return max;
}

double MinInNumbers( int amount, ... ){
    double max = 0;

    va_list list;
    va_start(list, amount);

    for (int i = 0; i < amount; i++) {
        double tmp = va_arg(list, double);
        if(tmp < max) max = tmp;
    }

    va_end(list);
    return max;
}