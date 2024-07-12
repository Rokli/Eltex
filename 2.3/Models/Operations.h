#ifndef operations_h
#define operations_h

#include <stdio.h>
#include <stdarg.h>

#define MAX_LENGTH 128

typedef double (*operationFunc)(int amount, ...);


typedef struct{
    char name[MAX_LENGTH];
    operationFunc func;
}operationStruct;

double Summ(int amount, ...);

double Difference(int amount, ...);

double Multiplication(int amount, ...);

double Division(int amount, ...);

double MaxInNumbers( int amount, ...);

double MinInNumbers( int amount, ...);

#endif