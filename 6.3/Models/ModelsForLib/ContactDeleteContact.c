#include "../Contact.h"

void DeleteContact(List *phoneBook){
    printf("Введите ID:\n");

    int id;
    scanf("%d",&id);

    deleteNth(phoneBook,id);
}