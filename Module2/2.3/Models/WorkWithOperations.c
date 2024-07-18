#include "WorkWithOperations.h"


double Counting(int operation){
    
    operationStruct operations[] = {
        {"Сложение", Summ},
        {"Разность", Difference},
        {"Умножение", Multiplication},
        {"Деление", Division},
        {"Максимальное число", MaxInNumbers},
        {"Минимальное число", MinInNumbers}
    };

    int count;

    printf("Введите количество чисел:");
    scanf("%d",&count);

    double numbers[count];
    
    for (int i = 0; i < count; i++) {
        scanf("%lf", &numbers[i]);
    }

    int result = 0;

    switch (count)
    {
    case 1:
        result = operations[operation - 1].func(count,numbers[0]);
        break;
    case 2:
        result = operations[operation - 1].func(count,numbers[0],numbers[1]);
        break;
    case 3:
        result = operations[operation - 1].func(count,numbers[0],numbers[1],numbers[2]);
        break;
    case 4:
        result = operations[operation - 1].func(count,numbers[0],numbers[1],numbers[2],numbers[3]);
        break;
    case 5:
        result = operations[operation - 1].func(count,numbers[0],numbers[1],numbers[2],numbers[3],numbers[4]);
        break;
    default:
        break;
    }
    return result;
}


void Menu(){

    int choice; 

    while(choice != 7){

        printf("1 - Сумма\n2 - Разность\n3 - Умножение\n4 - Деление\n5 - Максимальное число\n6 - Минимальное число\n7 - Выход\n");
        printf("Введите номер операции: ");

        scanf("%d", &choice);
        getchar();

        if (choice != 7) {
            double result = Counting(choice);
            printf("Ответ: %lf\n", result);
        } 
    } 
}