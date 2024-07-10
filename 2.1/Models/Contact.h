#ifndef Contact_h
#define Contact_h

#include "Person.h"
#define false 0

void PrintPhoneBook(Person phoneBook[]);

int FindContactId(Person phoneBook[]);

void PrintContactId(Person phoneBook[], int id);

void PrintContact(Person phoneBook[]);

void EditContact(Person phoneBook[N]);

void DeleteContact(Person phoneBook[N]);

void PrintIndividualContact(Person phoneBook[N]);

#endif