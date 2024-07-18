#include "WorkWithOperations.h"


void Counting(int operation){

    void *handle;
    char *error;
    int count;
    double result;
    typedef double (*operations)(int, double []);

    printf("Введите количество чисел:");
    scanf("%d",&count);

    double numbers[count];
    for (int i = 0; i < count; i++) {
        scanf("%lf", &numbers[i]);
    }

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return;
    }

    switch (operation) {
        case 1:
            handle = dlopen("libsumm.so", RTLD_LAZY);
            operations Summ = (operations)dlsym(handle, "Summ");
            result = Summ(count, numbers);
            dlclose(handle);
            break;
        case 2:
            handle = dlopen("libdifference.so", RTLD_LAZY);
            operations Difference = (operations)dlsym(handle, "Difference");
            result = Difference(count, numbers);
            dlclose(handle);
            break;
        case 3:
            handle = dlopen("libmultiplication.so", RTLD_LAZY);
            operations Multiplication = (operations)dlsym(handle, "Multiplication");
            result = Multiplication(count, numbers);
            dlclose(handle);
            break;
        case 4:
            handle = dlopen("libdivision.so", RTLD_LAZY);
            operations Division = (operations)dlsym(handle, "Division");
            result = Division(count, numbers);
            dlclose(handle);
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
