#ifndef operations_h
#define operations_h

#include <stdio.h>
#include <stdarg.h>

#define MAX_LENGTH 128

typedef double (*operationFunc)(int count, double numbers[]);


typedef struct{
    char name[MAX_LENGTH];
    operationFunc func;
}operationStruct;

double Summ( int count, double numbers[] );

double Difference( int count, double numbers[] );

double Multiplication( int count, double numbers[] );

double Division( int count, double numbers[] );

#endif