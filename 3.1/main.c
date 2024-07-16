#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#define MAX_LENTGH 128
#define false 0
#define true 1
void displayPermissions(mode_t permissions) {

    printf("Численное представление прав доступа:%o\n", permissions & 0777);
    
    printf("Битовое представление прав доступа:");

    for (int i = 8; i >= 0; i--) {
    printf("%d", (permissions >> i) & 1);
    }

    printf("\n");

    printf("Буквенное представление прав доступа:");

    printf((permissions & S_IRUSR) ? "r" : "-");
    printf((permissions & S_IWUSR) ? "w" : "-");
    printf((permissions & S_IXUSR) ? "x" : "-");
    printf((permissions & S_IRGRP) ? "r" : "-");
    printf((permissions & S_IWGRP) ? "w" : "-");
    printf((permissions & S_IXGRP) ? "x" : "-");
    printf((permissions & S_IROTH) ? "r" : "-");
    printf((permissions & S_IWOTH) ? "w" : "-");
    printf((permissions & S_IXOTH) ? "x" : "-");
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
            printf("23");
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
        printf("\nВыберите действие:\n1 - Ввести права доступа в буквенном или цифровом обозначении\n2 - Изменить права доступа\n3 - Вывести права\n4 - Выйти из программы\n");
        
        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                char permissions,target = 'u',operation = '-',action = 'r';
                printf("Введите новые права доступа: ");
                scanf("%c", &target);
                // printf("F:");
                // scanf("%c", &operation);
                // printf("F:");
                // scanf("%c", &action);
                currentMode = ConvertMode(currentMode,target,operation,action);
                break;
            case 2: 
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