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
    while (head != NULL && head->priority != priority) {
        head = head->next;
    }
    return head;
}

void deleteNth(Queue **head, int priority) {
    if (*head == NULL) {
        return;
    }
    
    if ((*head)->priority == priority) {
        Queue *temp = *head;
        *head = (*head)->next;
        printMessage(temp->_message, temp->priority);
        free(temp);
        return;
    }

    Queue *prev = *head;
    while (prev->next != NULL && prev->next->priority != priority) {
        prev = prev->next;
    }
    if (prev->next != NULL) {
        Queue *elm = prev->next;
        prev->next = elm->next;
        printMessage(elm->_message, elm->priority);
        free(elm);
    }
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