#include "Contact.h"

void AddPerson(Tree **tree){

    printf("Введите ID:");
    int id;
    scanf("%d",&id);

    (*tree) = insert((*tree),id);
}

void PrintPhoneBook(Tree *tree){
    preOrderTravers(tree);
}   

void EditContact(Tree *tree){
}

void DeleteContact(Tree *tree){
}

void PrintIndividualContact(Tree* tree){
}