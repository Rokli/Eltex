#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define true 1
#define false 0
#define N 512

typedef struct
{
    char vkontakte[N];
    char ok[N];
    char facebook[N];
}socialNetwork;

typedef struct{
    char homePhone[N];
    char workPhone[N];
}mobilephone;
typedef struct{
    int id;
    char name[N];
    char surname [N];
    char patronymic[N];
    char post[N];
    mobilephone numberPhone;
    char email[N];
    socialNetwork socialNetwork;
}Person;

Person CreatePerson(){
    Person person;

    printf("Введите имя:");
    scanf("%s", &person.name);

    printf("Введите фамилию:");
    scanf("%s", &person.surname);

    printf("Введите отчество:");
    scanf("%s", &person.patronymic);

    return person;
}
void AddPerson(Person phoneBook[N]){
    Person person = CreatePerson();
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
void PrintPhoneBook(Person phoneBook[]){
    for(int i = 0;i < N; i++){
        if(phoneBook[i].id != 0) printf("\nID:%d\nИмя:%s",phoneBook[i].id,phoneBook[i].name);
    }
    printf("\n");
}
int FindContactId(Person phoneBook[]){
    int id = 0;
    printf("Введите ID пользователя:");
    scanf("%d",&id);
    for(int i; i < N; i++){
        if(phoneBook[i].id == id) break;
    }
    if(id == 0){
        printf("Нет такого ID");
        return false;
    }
    return id;
}
void EditSocialNetwork(Person phoneBook[N],int id){
    printf("\nСоциальные сети:%s\t%s\t%s",phoneBook[id].socialNetwork.vkontakte,phoneBook[id].socialNetwork.ok,phoneBook[id].socialNetwork.facebook);
    printf("\n1 - Изменить ВК\t2 - Изменить Одноклассники\t3 - Изменить Фейсбук\n");
    int tmp;
    scanf("%d", &tmp);
    getchar();
    printf("Введите новое значение:");
    switch (tmp)
    {
    case 1:
        scanf("%s", &phoneBook[id].socialNetwork.vkontakte);
        break;
    case 2:
        scanf("%s", &phoneBook[id].socialNetwork.ok);
        break;
    case 3:
        scanf("%s", &phoneBook[id].socialNetwork.facebook);
        break;
    default:
        break;
    }
}
void EditMobilePhone(Person phoneBook[N],int id){
    printf("\nНомера::%s\t%s",phoneBook[id].numberPhone.homePhone,phoneBook[id].numberPhone.workPhone);
    printf("\n1 - Изменить домашний номер\t2 - Изменить рабочий номер");
    int tmp;
    scanf("%d", &tmp);
    getchar();
    printf("Введите новое значение:");
    switch (tmp)
    {
    case 1:
        scanf("%s", &phoneBook[id].numberPhone.homePhone);
        break;
    case 2:
        scanf("%s", &phoneBook[id].numberPhone.workPhone);
        break;
    default:
        break;
    }
}
void PrintContact(Person phoneBook[]){
    int id = FindContactId(phoneBook)-1;
    if(id == -1) return;
    printf("ID:%d\nИмя:%s\nФамилия:%s\nОтчество%s\nДолжность:%s\nНомер телефона:%s\nЭлектронная почта:%s\nСоциальная сеть:%s,%s,%s\n",
    phoneBook[id].id,phoneBook[id].name,phoneBook[id].surname,phoneBook[id].patronymic
    ,phoneBook[id].post,phoneBook[id].numberPhone,phoneBook[id].email,phoneBook[id].socialNetwork.facebook,phoneBook[id].socialNetwork.ok,phoneBook[id].socialNetwork.vkontakte);
}
void PrintContactId(Person phoneBook[], int id){
    printf("ID:%d\nИмя:%s\nФамилия:%s\nОтчество%s\nДолжность:%s\nНомер телефона:%s,%s\nЭлектронная почта:%s\nСоциальная сеть:%s,%s,%s\n",
    phoneBook[id].id,phoneBook[id].name,phoneBook[id].surname,phoneBook[id].patronymic
    ,phoneBook[id].post,phoneBook[id].numberPhone.homePhone,phoneBook[id].numberPhone.workPhone,phoneBook[id].email,phoneBook[id].socialNetwork.facebook,phoneBook[id].socialNetwork.ok,phoneBook[id].socialNetwork.vkontakte);
}
void EditContact(Person phoneBook[N]){
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
        EditMobilePhone(phoneBook,id);
        break;
    case 6:
        scanf("%s", &phoneBook[id].email);
        break;
    case 7:
        EditSocialNetwork(phoneBook,id);
        break;
    default:
        break;
    }
}
void DeleteContact(Person phoneBook[N]){
    int id = FindContactId(phoneBook) - 1;
    if(id == -1) return;
    memset(phoneBook[id].name,0,N);
    memset(phoneBook[id].surname,0,N);
    memset(phoneBook[id].patronymic,0,N);
    memset(phoneBook[id].post,0,N);
    memset(phoneBook[id].numberPhone.homePhone,0,N);
    memset(phoneBook[id].numberPhone.workPhone,0,N);
    memset(phoneBook[id].email,0,N);
    memset(phoneBook[id].socialNetwork.facebook,0,N);
    memset(phoneBook[id].socialNetwork.ok,0,N);
    memset(phoneBook[id].socialNetwork.vkontakte,0,N);
    phoneBook[id].id = 0;
}
void PrintIndividualContact(Person phoneBook[N]){
    int id = FindContactId(phoneBook) - 1;
    if(id == -1) return;
    PrintContactId(phoneBook,id);
}
int main(void){
    Person phoneBook[N];
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
            EditContact(phoneBook);
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