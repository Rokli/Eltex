#include "Models/Contact.h"

#define false 0
#define true 1

int main(){

    Tree *tree = NULL;
    int flag = true;

    while(flag){
     
        printf("1 - Добавить пользователя\t2 - Вывести список пользователей\n3 - Выйти из телефонной книги\t4 - Редактировать контакт\n5 - Удалить контакт\t6 - Вывести информацию про отдельного пользователя\n");
     
        int tmp;
        scanf("%d", &tmp);
        fflush(stdin); 

        switch (tmp)
        {
            case 1:
                AddPerson(&tree);
                break;
            case 2:
                PrintPhoneBook(tree);
                break;
            // case 3:
            //     flag = false;
            //     break;
            // case 4:
            //     EditContact(phoneBook);
            //     break;
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