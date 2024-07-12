#include "WorkWithOperations.h"


double Counting(int operation){
    
    operationStruct operations[] = {
        {"Сложение", Summ},
        {"Разность", Difference},
        {"Умножение", Multiplication},
        {"Деление", Division}
    };

    int count;

    printf("Введите количество чисел:");
    scanf("%d",&count);

    double numbers[count];
    for (int i = 0; i < count; i++) {
        scanf("%lf", &numbers[i]);
    }

    return operations[operation - 1].func(count,numbers);
}


void Menu(){

    int choice; 

    while(choice != 5){

        printf("1 - Сумма\n2 - Разность\n3 - Умножение\n4 - Деление\n5 - Выход\n");
        printf("Введите номер операции: ");

        scanf("%d", &choice);
        getchar();

        if (choice != 5) {
            double result = Counting(choice);
            printf("Ответ: %lf\n", result);
        } 
    } 
}
