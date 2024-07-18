#include <dlfcn.h>
#include <stdio.h>
#include "Models/List.h"
#define true 1;
#define false 0;


int main(){
    List *phoneBook = CreateList();
    int flag = true;
    void *handle;
    char *error;
    typedef void (*operations)(List *phoneBook);
    typedef void (*deleteOperation)(List **list);
    handle = dlopen("libdynamic.so", RTLD_LAZY);

    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        return 1;
    }


    while(flag){
        
        printf("1 - Добавить пользователя\t2 - Вывести список пользователей\n3 - Выйти из телефонной книги\t4 - Редактировать контакт\n5 - Удалить контакт\t6 - Вывести информацию про отдельного пользователя\n");
        
        int tmp;
        scanf("%d", &tmp);
        fflush(stdin); 

        switch (tmp)
        {
        case 1:
            operations AddPerson = (operations)dlsym(handle, "AddPerson");
            AddPerson(phoneBook);
            break;
        case 2:
            operations PrintPhoneBook = (operations)dlsym(handle, "PrintPhoneBook");
            PrintPhoneBook(phoneBook);
            break;
        case 3:
            flag = false;
            break;
        case 4:
            operations EditContact = (operations)dlsym(handle, "EditContact");
            EditContact(phoneBook);
            break;
        case 5:
            operations DeleteContact = (operations)dlsym(handle, "DeleteContact");
            DeleteContact(phoneBook);
            break;
        case 6:
            operations PrintIndividualContact = (operations)dlsym(handle, "PrintIndividualContact");
            PrintIndividualContact(phoneBook);
            break;    
        default:
            break;
        }
    }
    deleteOperation DeleteList = (deleteOperation)dlsym(handle, "DeleteList");
    DeleteList(&phoneBook);
    return 0;
}