#include "Contact.h"


void AddPerson(List *phoneBook){
    Person person = CreatePerson();
    pushBack(phoneBook,person);
}

void PrintPhoneBook(List *phoneBook){
    printList(phoneBook,printInt);
}   


void EditContact(List *phoneBook){
    
}