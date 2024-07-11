#include "WorkWithOperations.h"


int Counting(int operation){
    
    int count,result = 0;
    

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
            printf("Ответ: %lf\n", result);
        } 
    } 
}
