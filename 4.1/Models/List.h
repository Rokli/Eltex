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

void* popFront(List *list);

void pushBack(List *list, Person value);

void* popBack(List *list);

Node* getNth(List *list, size_t index);

void insert(List *list, size_t index, Person value);

void* deleteNth(DblLinkedList *list, size_t index);
#endif