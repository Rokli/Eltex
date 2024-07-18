#include "Operations.h"


double Summ(int count, double numbers[] ){
    int result = 0;

    for(int i = 0; i < count; i++){
        result += numbers[i];
    }

    return result;
}
