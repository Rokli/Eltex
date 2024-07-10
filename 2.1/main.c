#include "Models/Contact.h"
#include "Models/Person.h"
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