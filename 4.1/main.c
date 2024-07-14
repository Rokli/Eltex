#include "Models/Contact.h"
#define true 1;
#define false 0;


int main(){
    List *phoneBook = CreateList();
    int flag = true;
    
    while(flag){
        
        printf("1 - Добавить пользователя\t2 - Вывести список пользователей\n3 - Выйти из телефонной книги\t4 - Редактировать контакт\n5 - Удалить контакт\t6 - Вывести информацию про отдельного пользователя\n");
        
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
        // case 5:
        //     DeleteContact(phoneBook);
        //     break;
        // case 6:
        //     PrintIndividualContact(phoneBook);
        //     break;    
        default:
            break;
        }
    }

    return 0;
}