#include "Contact.h"

void AddPerson(Tree **phoneBook){

    printf("Введите ID:");
    int id;
    scanf("%d",&id);

   (*phoneBook) = insert((*phoneBook),id);
}

void PrintPhoneBook(Tree *phoneBook){
    preOrderTravers(phoneBook);
}   

void EditContact(Tree **phoneBook){
    printf("Введите ID:");
    int id;
    scanf("%d",&id);

    (*phoneBook) = editNode((*phoneBook),id);
}

void DeleteContact(Tree **phoneBook){
    printf("Введите ID:");
    int id;
    scanf("%d",&id);

    (*phoneBook) = deleteNode((*phoneBook),id);
}

void PrintIndividualContact(Tree* phoneBook){
    printf("Введите ID:");
    int id;
    scanf("%d",&id);

    printOneNode(phoneBook,id);
}