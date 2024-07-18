#include "WorkWithOperations.h"


void Counting(int operation){
    
    int count;
    double result;

    printf("Введите количество чисел:");
    scanf("%d",&count);

    double numbers[count];
    for (int i = 0; i < count; i++) {
        scanf("%lf", &numbers[i]);
    }

    switch (operation) {
        case 1:
            result = Summ(count, numbers);
            break;
        case 2:
            result = Difference(count, numbers);
            break;
        case 3:
            result = Multiplication(count, numbers);
            break;
        case 4:
            result = Division(count, numbers);
            break;
        default:
            printf("Неверный выбор операции!\n");
            return;
        }
    printf("Ответ: %lf\n", result);
}


void Menu(){

    int choice; 

    while(choice != 5){

        printf("1 - Сумма\n2 - Разность\n3 - Умножение\n4 - Деление\n5 - Выход\n");
        printf("Введите номер операции: ");

        scanf("%d", &choice);
        getchar();

        if (choice != 5) {
            Counting(choice);
        } 
    } 
}
