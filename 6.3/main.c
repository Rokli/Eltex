#include "Models/List.h"
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#define true 1;
#define false 0;


int main(){
    List *phoneBook = CreateList();
    int flag = true;
    
    void *handle;
    void (*function)(List *);
    while(flag){
        
        printf("1 - Добавить пользователя\t2 - Вывести список пользователей\n3 - Выйти из телефонной книги\t4 - Редактировать контакт\n5 - Удалить контакт\t6 - Вывести информацию про отдельного пользователя\n");
        
        int tmp;
        scanf("%d", &tmp);
        fflush(stdin); 

        switch (tmp)
        {
        case 1:
            handle = dlopen("./libaddPerson.so", RTLD_LAZY);
            if (!handle) {
                fprintf(stderr, "%s\n", dlerror());
                exit(EXIT_FAILURE);
            }
            function = dlsym(handle, "AddPerson");
            function(phoneBook);
            break;
        case 2:
            handle = dlopen("./libPrintPhoneBook.so", RTLD_LAZY);
            if (!handle) {
                fprintf(stderr, "%s\n", dlerror());
                exit(EXIT_FAILURE);
            }
            function = dlsym(handle, "PrintPhoneBook");
            function(phoneBook);
            break;
        case 3:
            flag = false;
            break;
        case 4:
            handle = dlopen("./libeditPhoneBook.so", RTLD_LAZY);
            if (!handle) {
                fprintf(stderr, "%s\n", dlerror());
                exit(EXIT_FAILURE);
            }
            function = dlsym(handle, "EditContact");
            function(phoneBook);
            break;
        case 5:
            handle = dlopen("./libDeleteContact.so", RTLD_LAZY);
            if (!handle) {
                fprintf(stderr, "%s\n", dlerror());
                exit(EXIT_FAILURE);
            }
            function = dlsym(handle, "DeleteContact");
            function(phoneBook);
            break;
        case 6:
            handle = dlopen("./libDeleteContact.so", RTLD_LAZY);
            if (!handle) {
                fprintf(stderr, "%s\n", dlerror());
                exit(EXIT_FAILURE);
            }
            function = dlsym(handle, "DeleteContact");
            function(phoneBook);
            break;    
        default:
            break;
        }
    }
    return 0;
}