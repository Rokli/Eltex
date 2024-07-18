#ifndef contact_h
#define contact_h

#include "Tree.h"

void AddPerson(Tree **phoneBook);

void PrintPhoneBook(Tree *phoneBook);

void EditContact(Tree **phoneBook);

void DeleteContact(Tree **phoneBook);

void PrintIndividualContact(Tree* phoneBook);

#endif