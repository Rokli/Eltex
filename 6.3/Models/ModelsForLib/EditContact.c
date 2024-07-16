#include "../Contact.h"

void EditContact(List *phoneBook){

    printf("Введите ID:\n");

    int id;
    scanf("%d",&id);

    Node* tmp = getNth(phoneBook,id);
    tmp->value = EditPerson(tmp->value);
}