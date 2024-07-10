#include <stdio.h>
#include <string.h>
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
    printf("ID пользователя:%d\n",person.id);
    phoneBook[id] = person; 
}
void PrintPhoneBook(struct Person phoneBook[]){
    for(int i = 0;i < N; i++){
        if(phoneBook[i].id != 0) printf("\nID:%d\nИмя:%s",phoneBook[i].id,phoneBook[i].name);
    }
    printf("\n");
}
int FindContactId(struct Person phoneBook[]){
    int id = 0;
    printf("Введите ID пользователя:");
    scanf("%d",&id);
    for(int i; i < N; i++){
        if(phoneBook[i].id == id){
            break;
        }
    }
    if(id == 0){
        printf("Нет такого ID");
        return false;
    }
    return id;
}
void PrintContact(struct Person phoneBook[]){
    int id = FindContactId(phoneBook)-1;
    if(id == -1) return;
    printf("%d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",phoneBook[id].id,phoneBook[id].name,phoneBook[id].surname,phoneBook[id].patronymic
                                            ,phoneBook[id].post,phoneBook[id].numberPhone,phoneBook[id].email,phoneBook[id].socialNetwork);
}
void PrintContactId(struct Person phoneBook[], int id){
    printf("ID:%d\nИмя:%s\nФамилия:%s\nОтчество%s\nДолжность:%s\nНомер телефона:%s\nЭлектронная почта:%s\nСоциальная сеть:%s\n",
    phoneBook[id].id,phoneBook[id].name,phoneBook[id].surname,phoneBook[id].patronymic
    ,phoneBook[id].post,phoneBook[id].numberPhone,phoneBook[id].email,phoneBook[id].socialNetwork);
}
void ChangeContact(struct Person phoneBook[N]){
    int id = FindContactId(phoneBook) - 1;
    if(id == -1) return;
    PrintContactId(phoneBook,id);
    printf("1 - Изменить имя\n2 - Изменить фамилию\n3 - Изменить Отчество\n4 - Изменить должность\n5 - Изменить номер телефона\n6 - Изменить почту\n7 - Изменить социальные сети\n");
    int tmp;
    scanf("%d", &tmp);
    getchar();
    printf("Введите новое значение:");
    switch (tmp)
    {
    case 1:
        scanf("%s", &phoneBook[id].name);
        break;
    case 2:
        scanf("%s", &phoneBook[id].surname);
        break;
    case 3:
        scanf("%s", &phoneBook[id].patronymic);
        break;
    case 4:
        scanf("%s", &phoneBook[id].post);
        break;
    case 5:
        scanf("%s", &phoneBook[id].numberPhone);
        break;
    case 6:
        scanf("%s", &phoneBook[id].email);
        break;
    case 7:
        scanf("%s", &phoneBook[id].socialNetwork);
        break;
    default:
        break;
    }
}
void DeleteContact(struct Person phoneBook[N]){
    int id = FindContactId(phoneBook) - 1;
    if(id == -1) return;
    memset(phoneBook[id].name,0,N);
    memset(phoneBook[id].surname,0,N);
    memset(phoneBook[id].patronymic,0,N);
    memset(phoneBook[id].post,0,N);
    memset(phoneBook[id].numberPhone,0,N);
    memset(phoneBook[id].email,0,N);
    memset(phoneBook[id].socialNetwork,0,N);
    phoneBook[id].id = 0;
}
void PrintIndividualContact(struct Person phoneBook[N]){
    int id = FindContactId(phoneBook) - 1;
    if(id == -1) return;
    PrintContactId(phoneBook,id);
}
int main(void){
    struct Person phoneBook[N];
    int tmp;
    int flag = 1;
    while(flag){
        printf("1 - Добавить пользователя\t2 - Вывести список пользователей\n3 - Выйти из телефонной книги\t4 - Редактировать контакт\n5 - Удалить контакт\t6 - Вывести информацию про отдельного пользователя\n");
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
            break;
        case 4:
            ChangeContact(phoneBook);
            break;
        case 5:
            DeleteContact(phoneBook);
            break;
        case 6:
            PrintIndividualContact(phoneBook);
            break;    
        default:
            break;
        }
    }
}