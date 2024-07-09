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

struct Person CreatePerson(){
    struct Person person;

    printf("Введите имя:");
    scanf("%s", &person.name);

    printf("Введите фамилию:");
    scanf("%s", &person.surname);

    printf("Введите отчество:");
    scanf("%s", &person.patronymic);

    return person;
}
void AddPerson(struct Person phoneBook[N]){
    struct Person person = CreatePerson();
    int id = 0;
    for (int i = 0; i < N; i++) {
        if (phoneBook[i].id == 0) {
            id = i;
            break;
        }
    }
    if (id == N) {
        printf("Телефонная книга заполнена\n");
        return;
    }
    person.id = id + 1;
    phoneBook[id] = person; 
}
void PrintPhoneBook(struct Person phoneBook[]){
    for(int i = 0; i < N; i++){
        printf("%s",phoneBook[i].name);
    }
    printf("\n");
}
int main(void){
    struct Person phoneBook[N];
    int tmp;
    int flag = 1;
    while(flag){
        printf("1 - Добавить пользователя\t2 - Вывести список пользователей\n3 - Выйти из телефонной книги\t4 - Редактировать контакт\n");
        scanf("%d", &tmp);
        getchar();
        switch (tmp)
        {
        case 1:
            AddPerson(phoneBook);
            break;
        case 2:
            PrintPhoneBook(phoneBook);
            break;
        case 3:
            flag = false;
        case 4:
            printf("4");
            break;
        default:
            break;
        }
    }
}