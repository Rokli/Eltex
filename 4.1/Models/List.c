#include "List.h"

List* CreateList() {

    List *tmp = (List*) malloc(sizeof(List));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;

    return tmp;
}

void DeleteList(List **list) {
    Node *tmp = (*list)->head;
    Node *next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}

void pushBack(List *list, Person value) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(3);
    }
    tmp->value = value;
    tmp->next = NULL;
    tmp->prev = list->tail;
    
    if (list->tail) {
        list->tail->next = tmp;
    }
    list->tail = tmp;
 
    if (list->head == NULL) {
        list->head = tmp;
    }
    tmp->id = findId(list);
    list->size++;
}

unsigned int findId(List *list){
    Node *tmp = list->head;
    int id = 0;
    while (tmp->next != NULL) {
        tmp = tmp->next;
        id++;
    }
 
    return id;
}
Node* getNth(List *list, int index) {
    Node *tmp = list->head;
    int id = 0;
 
    while (tmp->next != NULL) {
        if(tmp->id == index) break;
        tmp = tmp->next;
        id++;
    }
 
    return tmp;
}
 
Person deleteNth(List *list, int index) {
    Node *elm = NULL;
    Person tmp;
    elm = getNth(list, index);
    if (elm == NULL) {
        exit(5);
    }
    if (elm->prev) {
        elm->prev->next = elm->next;
    }
    if (elm->next) {
        elm->next->prev = elm->prev;
    }
    tmp = elm->value;
 
    if (!elm->prev) {
        list->head = elm->next;
    }
    if (!elm->next) {
        list->tail = elm->prev;
    }
 
    free(elm);
 
    list->size--;
 
    return tmp;
}

void printInt(Person person) {
    printf("Имя:%s\nФамилия:%s\nОтчество:%s\nДолжность:%s\nДомашний номер:%s\nРабочий номер:%s\nПочта:%s\n",
        person.name,person.surname,person.patronymic,person.post,person.numberPhone.homePhone,person.numberPhone.workPhone,person.email);
    
    printf("Социальные сети:\n");
    for(int i = 0; i < 5; i++){
        printf("%d:%s,%s\n",i+1,person.socialNetwork[i].name,person.socialNetwork[i].address);
    }
}

void printList(List *list, void (*fun)(Person)) {
    Node *tmp = list->head;
    while (tmp) {
        printf("-------------\n");
        printf("ID:%d\n",tmp->id);
        fun(tmp->value);
        tmp = tmp->next;
        printf("-------------\n");
    }
    printf("\n");
}