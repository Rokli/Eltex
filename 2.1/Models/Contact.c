#include "Contact.h"
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

void PrintContactId(Person phoneBook[], int id){
    printf("ID:%d\nИмя:%s\nФамилия:%s\nОтчество%s\nДолжность:%s\nНомер телефона:%s,%s\nЭлектронная почта:%s\nСоциальная сеть:%s,%s,%s\n",
    phoneBook[id].id,phoneBook[id].name,phoneBook[id].surname,phoneBook[id].patronymic
    ,phoneBook[id].post,phoneBook[id].numberPhone.homePhone,phoneBook[id].numberPhone.workPhone,phoneBook[id].email,phoneBook[id].socialNetwork.facebook,phoneBook[id].socialNetwork.ok,phoneBook[id].socialNetwork.vkontakte);
}

void PrintContact(Person phoneBook[]){
    int id = FindContactId(phoneBook)-1;
    if(id == -1) return;
    printf("ID:%d\nИмя:%s\nФамилия:%s\nОтчество%s\nДолжность:%s\nНомер телефона:%s\nЭлектронная почта:%s\nСоциальная сеть:%s,%s,%s\n",
    phoneBook[id].id,phoneBook[id].name,phoneBook[id].surname,phoneBook[id].patronymic
    ,phoneBook[id].post,phoneBook[id].numberPhone,phoneBook[id].email,phoneBook[id].socialNetwork.facebook,phoneBook[id].socialNetwork.ok,phoneBook[id].socialNetwork.vkontakte);
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