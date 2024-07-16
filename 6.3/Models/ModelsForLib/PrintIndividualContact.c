#include "../Contact.h"

void PrintIndividualContact(List* phoneBook){
    printf("Введите ID:\n");

    int id;
    scanf("%d",&id);

    Node* tmp =  getNth(phoneBook,id);
    printf("ID:%d\n",tmp->id);
    printInt(tmp->value);
}