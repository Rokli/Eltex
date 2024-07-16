#include "Queue.h"

Message createMessage(){
    Message message;
    printf("Введите сообщение:");
    scanf("%s",&message.text);
    return message;
}

int getMessageMinPriority(Queue* head, int priority){

    while (head) {
        if(head->priority >= priority){
            priority = head->priority;
            break;
        } 
        head = head->next;
    }
    
    return priority;
}

void printMessage(Message _message,int priority){
    printf("------------\n");
    printf("Приоритет:%d\nСообщения:%s\n",priority,_message.text);
    printf("------------\n");
}

void push(Queue **head, int priority,Message _message) {

    Queue *tmp = (Queue*) malloc(sizeof(Queue));

    tmp->priority = priority;
    tmp->_message = _message;

    tmp->next = (*head);
    (*head) = tmp;
}

int getMessageMaxPriority(Queue *head){
    int min = 255;

    while (head) {
        if(head->priority < min) min = head->priority;
        head = head->next;
    }

    return min;
}

Queue* getNth(Queue* head, int priority) {
    while (head->next->priority != priority) {
        head = head->next;
    }
    if(head->priority != priority) printf("Такого приоритета нет, вытащен последний добавленный\n");
    return head;
}

void deleteNth(Queue **head, int priority) {
    Queue *prev = getNth(*head, priority);
    Queue *elm  = prev->next;
    printMessage(elm->_message, elm->priority);
    prev->next = elm->next;
    free(elm);

}

void deleteList(Queue **head) {
    Queue* prev = NULL;
    while ((*head)->next) {
        prev = (*head);
        (*head) = (*head)->next;
        free(prev);
    }
    free(*head);
}

void printLinkedList(Queue *head) {
    while (head) {
        printMessage(head->_message,head->priority);
        head = head->next;
    }
    printf("\n");
}