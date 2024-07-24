#ifndef list_h
#define list_h

#include "Person.h"
#include <stdlib.h>

typedef struct _Node {
    unsigned int id;
    Person value;
    struct _Node *next;
    struct _Node *prev; 
} Node;

typedef struct List {
    Node *head;
    Node *tail;
} List;

List* CreateList();

void insert(List *list, int index,Person person);

void DeleteList(List **list);

void pushBack(List *list, Person value);

Node* getNth(List *list, int index);

Person deleteNth(List *list, int index);

unsigned int findId(List *list);

void printPerson(Person person);

void printList(List *list, void (*fun)(Person));

unsigned int addId(List* list);

#endif