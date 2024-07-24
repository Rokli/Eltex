#include "Models/Contact.h"
#define true 1;
#define false 0;


int main(){
    List *phoneBook = CreateList();
    int flag = true;
    LoadPhoneBook(phoneBook);
    while(flag){
        
        printf("1 - Добавить пользователя\n2 - Вывести список пользователей\n3 - Выйти из телефонной книги\n4 - Редактировать контакт\n5 - Сохранить в файл\n6 - Удалить контакт\n7 - Вывести информацию про отдельного пользователя\n");
        
        int tmp;
        scanf("%d", &tmp);
        fflush(stdin); 

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
            SavePhoneBook(phoneBook);
            break;
        case 6:
            DeleteContact(phoneBook);
            break;
        case 7:
            PrintIndividualContact(phoneBook);
            break;    
        default:
            break;
        }
    }
    DeleteList(&phoneBook);
    return 0;
}