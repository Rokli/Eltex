#include "Contact.h"


void AddPerson(List *phoneBook){
    Person person = CreatePerson();
    pushFront(phoneBook,person);
    
}

void PrintPhoneBook(List *phoneBook){
    insertionSort(&phoneBook);
    printList(phoneBook,printPerson);
}   


void EditContact(List *phoneBook){

    printf("Введите ID:\n");

    int id;
    scanf("%d",&id);

    Node* tmp = getNth(phoneBook,id);
    tmp->value = EditPerson(tmp->value);
}

void DeleteContact(List *phoneBook){
    printf("Введите ID:\n");

    int id;
    scanf("%d",&id);

    deleteNth(phoneBook,id);
}

void PrintIndividualContact(List* phoneBook){
    printf("Введите ID:\n");

    int id;
    scanf("%d",&id);

    Node* tmp =  getNth(phoneBook,id);
    printf("ID:%d\n",tmp->id);
    printPerson(tmp->value);
}