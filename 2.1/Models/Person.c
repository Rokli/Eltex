#include "Person.h"

Person CreatePerson() {
    Person person;

    printf("Введите имя:");
    scanf("%s", person.name);

    printf("Введите фамилию:");
    scanf("%s", person.surname);

    printf("Введите отчество:");
    scanf("%s", person.patronymic);

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