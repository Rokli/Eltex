#ifndef queue_h
#define queue_h

#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 128

typedef struct {
    char text[MAX_LENGTH];
}Message;

typedef struct Queue{
    int priority;
    Message _message;
    struct Queue *next;
}Queue;

Message createMessage();

void push(Queue **head, int priority,Message _message);

Queue* getNth(Queue* head, int n);

void deleteNth(Queue **head, int priority) ;

void deleteQueue(Queue **head);

void printLinkedList(Queue *head);

int getMessageMinPriority(Queue* head, int priority);

int getMessageMaxPriority(Queue *head);

#endif
