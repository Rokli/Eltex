#ifndef list_h
#define list_h

#include "Person.h"
#include <stdlib.h>

typedef struct _Node {
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

void pushFront(List *list, Person data);

Person popFront(List *list);

void pushBack(List *list, Person value);

Person popBack(List *list);

Node* getNth(List *list, size_t index);

void insert(List *list, size_t index, Person value);

Person deleteNth(List *list, size_t index);

void printInt(Person person);

void printList(List *list, void (*fun)(Person));
#endif