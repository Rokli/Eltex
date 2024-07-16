#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

#define MAX_LENTGH 32
#define false 0
#define true 1

void displayPermissions(mode_t currentMode) {

    printf("Численное представление прав доступа:%o\n", currentMode & 0777);
    
    printf("Битовое представление прав доступа:");

    for (int i = 8; i >= 0; i--)
        printf("%u", ((currentMode & 0777) >> i) & 1);
    printf("\n");

    printf("Буквенное представление прав доступа:");

    printf((currentMode & S_IRUSR) ? "r" : "-");
    printf((currentMode & S_IWUSR) ? "w" : "-");
    printf((currentMode & S_IXUSR) ? "x" : "-");
    printf((currentMode & S_IRGRP) ? "r" : "-");
    printf((currentMode & S_IWGRP) ? "w" : "-");
    printf((currentMode & S_IXGRP) ? "x" : "-");
    printf((currentMode & S_IROTH) ? "r" : "-");
    printf((currentMode & S_IWOTH) ? "w" : "-");
    printf((currentMode & S_IXOTH) ? "x" : "-");
    printf("\n");
}

mode_t ConvertMode(mode_t currentMode, char target, char operation,char action){
    
    mode_t actionMask;
    mode_t mask = 0;
    
    switch (action)
    {
    case 'r':
        actionMask =  S_IRUSR | S_IRGRP |S_IROTH; 
        break;
    case 'w':
        actionMask = S_IWUSR | S_IWGRP | S_IWOTH;
        break;
    case 'x':
        actionMask = S_IXUSR | S_IXGRP | S_IXOTH;
        break;
    default:
        break;
    }

    if(target == 'a' || target == 'u') mask |= actionMask & (S_IRUSR | S_IWUSR | S_IXUSR); 
    if(target == 'a' || target == 'g') mask |= actionMask & (S_IRUSR | S_IWUSR | S_IXUSR); 
    if(target == 'a' || target == 'o') mask |= actionMask & (S_IROTH | S_IWOTH | S_IXOTH); 
    
    switch(operation){
        case '+':
            currentMode  |= mask;
            break;
        case '-':
            currentMode  &= ~mask;
            break;
        case '=':
            if(target == 'a'){
                currentMode = (currentMode & ~0777) | mask;
            }
            else{
                if(target == 'u') currentMode = (currentMode & ~0700) | (mask & 0700);
                if(target == 'g') currentMode = (currentMode & ~0070) | (mask & 0070);
                if(target == 'o') currentMode = (currentMode & ~0007) | (mask & 0007);
            }
            break;
        default:
            break;
    }
    return currentMode;
}

mode_t stringDivide(mode_t currentMode){
    char signatureTarget[MAX_LENTGH], signatureOperation[MAX_LENTGH], signatureAction[MAX_LENTGH];

    printf("Введите тип пользователя:");
    scanf("%s",&signatureTarget);
    
    printf("Введите тип операции:");
    scanf("%s",&signatureOperation);

    printf("Введите тип прав:");
    scanf("%s",&signatureAction);


    for(int i = 0; i < strlen(signatureTarget); i++){

        printf("%d",strlen(signatureTarget));

        if(strlen(signatureTarget) == 0) break;
        
        for(int j = 0; j < strlen(signatureAction); j++){

            if(strlen(signatureAction) == 0) break;

            currentMode = ConvertMode(currentMode,signatureTarget[i],signatureOperation[0],signatureAction[j]);

        }
    }

    return currentMode;
}


void convertLetters(){
    char access[MAX_LENTGH];
    unsigned int permission = 0;

    printf("Введите права доступа (буквенное или цифровое обозначение): ");
    scanf("%s", access);
    printf("\n");

    if (access[0] >= '0' && access[0] <= '7') {
        sscanf(access, "%o", &permission);
    } else {
        for(int i = 0; i < strlen(access); i++){
            if (access[i] == 'r') {
                permission |= 4;
            }
            if (access[i] == 'w') {
                permission |= 2;
            }
            if (access[i] == 'x') {
                permission |= 1;
            }
        }
    }
    displayPermissions(permission);
}
int main(){
    struct stat fileStat;
    char filename[MAX_LENTGH];

    printf("Введите имя файла:");
    scanf("%s",&filename);

    stat(filename,&fileStat);
    
    mode_t currentMode = fileStat.st_mode;
    displayPermissions(currentMode);

    int flag = true;

    while(flag){
        printf("\nВыберите действие:\n1 - Изменить права доступа файла\n2 - Ввести права доступа\n3 - Вывести права\n4 - Выйти из программы\n");
        
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                currentMode = stringDivide(currentMode);
                break;
            case 2: 
                convertLetters();
                break;
            case 3:
                displayPermissions(currentMode);
                break;
            case 4:
                flag = false;
                break;
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
                break;
        }
    }
    
    return 0;
}