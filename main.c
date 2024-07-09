#include <stdio.h>
#include <stdlib.h> 
#define true 1
#define false 0
#define N 512

struct Person {
    int id;
    char name[N];
    char surname [N];
    char patronymic[N];
    char post[N];
    char numberPhone[N];
    char email[N];
    char socialNetwork[N];
};

struct Person AddPerson(){
    struct Person person;

    printf("Введите имя:");
    scanf("%s", &person.name);

    printf("Введите фамилию:");
    scanf("%s", &person.surname);

    printf("Введите отчество:");
    scanf("%s", &person.patronymic);

    return person;
}
void PrintPhoneBook(struct Person phoneBook[N]){
    printf("%s",phoneBook[1].name);
}
int main(void){
    struct Person phoneBook[N];
    char tmp[1];
    int flag = 1;
    while(flag){
        printf("1 - Добавить пользователя \t 2- Вывести список пользователей\n3 - Выйти из телефонной книги\n");
        scanf("%c", &tmp);
        fflush(stdin);
        switch (atoi(tmp))
        {
        case 1:
            phoneBook[1] = AddPerson();
            break;
        case 2:
            PrintPhoneBook(phoneBook);
            break;
        case 3:
            flag = false;
        default:
            break;
        }
    }
}