#include "Contact.h"


void AddPerson(List *phoneBook){
    Person person = CreatePerson();
    if(phoneBook->head == NULL){
        pushBack(phoneBook,person);
    }else{
        insert(phoneBook,addId(phoneBook),person);
    }
}

void PrintPhoneBook(List *phoneBook){
    // SortList(phoneBook);
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

void SavePhoneBook(List* phoneBook){
    SaveList(phoneBook);
}