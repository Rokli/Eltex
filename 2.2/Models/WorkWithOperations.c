#include "WorkWithOperations.h"


int Counting(int operation){
    
    int firstValue;
    int secondValue;
    int result;

    printf("Введите первый аргумент: ");
    scanf("%d", &firstValue);

    printf("Введите второй аргумент: ");
    scanf("%d", &secondValue);

    switch (operation) {
        case 1:
            result = Summ(firstValue, secondValue);
            break;
        case 2:
            result = Difference(firstValue, secondValue);
            break;
        case 3:
            result = Multiplication(firstValue, secondValue);
            break;
        case 4:
            if (secondValue == 0) {
                printf("Ошибка: деление на ноль!\n");
                return 0; 
            } else {
                result = Division(firstValue, secondValue);
            }
            break;
        default:
            printf("Неверный выбор операции!\n");
            return 0;
    }

    return result;
}


void Menu(){

     int choice; 

    while(choice != 5){
        printf("1 - Сумма\n2 - Разность\n3 - Умножение\n4 - Деление\n5 - Выход\n");
        printf("Введите номер операции: ");
        scanf("%d", &choice);
        getchar();
        if (choice != 5) {
            int result = Counting(choice);
            printf("Ответ: %d\n", result);
        } 
    } 
}
