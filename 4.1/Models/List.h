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
    size_t size;
    Node *head;
    Node *tail;
} List;

List* CreateList();

void DeleteList(List **list);

void pushBack(List *list, Person value);

Node* getNth(List *list, int index);

Person deleteNth(List *list, int index);

unsigned int findId(List *list);

void printInt(Person person);

void printList(List *list, void (*fun)(Person));

#endif