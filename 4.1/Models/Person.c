#include "Person.h"


Person CreatePerson(){

    Person person;

    printf("Введите имя:");
    scanf("%s",&person.name);

    printf("Введите фамилию:");
    scanf("%s",&person.surname);

    printf("Введите отчество:");
    scanf("%s",&person.patronymic);

    return person;
}

Person EditNumberPhone(Person person){
    
    printf("Домашний номер:%s\nРабочий номер:%s\n", person.numberPhone.homePhone,person.numberPhone.workPhone);

    printf("1 - Изменить домашний номер\n2 - Изменить рабочий номер");

    int tmp;
    scanf("%d\n", &tmp);

    printf("Введите новый номер:");

    switch (tmp)
    {
    case 1:
        scanf("%s",&person.numberPhone.homePhone);
        break;
    case 2:
        scanf("%s",&person.numberPhone.workPhone);
        break;
    default:
        printf("Нет такой операции");
        break;
    }
    return person;
}

Person EditSocialNetworks(Person person){
    
    printf("Введите какой хотите изменить:");
    int tmp;
    scanf("%d", &tmp);

    if( 0 <= tmp < 5){

        printf("Введите имя:");
        scanf("%s",&person.socialNetwork[tmp].name);

        printf("Введите адрес:");
        scanf("%s",&person.socialNetwork[tmp].address);
    }else{
        printf("Нет такой социальной сети\n");
    }

    return person;
}
Person EditPerson(Person person){
    
    printf("ID:%d\nИмя:%s\nФамилия:%s\nОтчество:%s\nДолжность:%s\nДомашний номер:%s\nРабочий номер:%s\nПочта:%s\n",
        person.id+1,person.name,person.surname,person.patronymic,person.post,person.numberPhone.homePhone,person.numberPhone.workPhone,person.email);
    
    printf("Социальные сети:\n");
    for(int i = 0; i < 5; i++){
        printf("%d:%s,%s",i+1,person.socialNetwork[i].name,person.socialNetwork[i].address);
    }

    
    printf("\n1 - Изменить имя\n2 - Изменить фамилию\n3 - Изменить Отчество\n4 - Изменить должность\n5 - Изменить номер телефона\n6 - Изменить почту\n7 - Изменить социальные сети\n");
    int tmp;
    scanf("%d", &tmp);
    getchar();

    if( tmp != 7 || tmp != 5)printf("Введите новое значение:");
    
    switch (tmp)
    {
    case 1:
        scanf("%s", &person.name);
        break;
    case 2:
        scanf("%s", &person.surname);
        break;
    case 3:
        scanf("%s", &person.patronymic);
        break;
    case 4:
        scanf("%s", &person.post);
        break;
    case 5:
        person = EditNumberPhone(person);
        break;
    case 6:
        scanf("%s", &person.email);
        break;
    case 7:
        person = EditSocialNetworks(person);
        break;
    default:
        printf("Такой операции нет\n");
        break;
    }

    return person;
}
