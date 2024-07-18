#include "List.h"

List* CreateList() {

    List *tmp = (List*) malloc(sizeof(List));
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
}

unsigned int findId(List *list){
    Node *tmp = list->head;
    unsigned int id = 0;
    
    while (tmp != NULL) {
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

    if(elm->id != 0){
        elm->next->id--;
    }
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
 
    return tmp;
}

void printPerson(Person person) {
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

void pushFront(List *list, Person data) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) {
        exit(1);
    }
    tmp->value = data;
    tmp->id = findId(list);
    tmp->next = list->head;
    tmp->prev = NULL;
    if (list->head) {
        list->head->prev = tmp;
    }
    list->head = tmp;
 
    if (list->tail == NULL) {
        list->tail = tmp;
    }

}

Person popFront(List *list) {
    Node *prev;
    Person tmp;
    if (list->head == NULL) {
        exit(2);
    }
 
    prev = list->head;
    list->head = list->head->next;
    if (list->head) {
        list->head->prev = NULL;
    }
    if (prev == list->tail) {
        list->tail = NULL;
    }
    tmp = prev->value;

    free(prev);
 
    return tmp;
}

void insertBeforeElement(List *list, Node* elm, Person value) {
    if (elm == NULL) {
        return;
    }
     
    if (!elm->prev) {
        pushFront(list, value);
        return;
    }
     
    Node *ins = (Node*) malloc(sizeof(Node));
    if (ins == NULL) {
        return;
    }
    
    ins->value = value;
    ins->id = findId(list);
    ins->prev = elm->prev;
    ins->next = elm; // Устанавливаем указатель next для нового элемента
    
    elm->prev->next = ins; // Обновляем указатель next у предыдущего элемента
    elm->prev = ins; // Обновляем указатель prev у текущего элемента
}

int cmp(int idOne, int idTwo) {
    if (idOne > idTwo) {
        return 1;
    } else if (idOne < idTwo) {
        return -1;
    } else {
        return 0;
    }
}
void insertionSort(List **list) {
    List* out = CreateList();
    Node* sorted = NULL;
    Node *unsorted = NULL;
    pushFront(out, popFront((*list)));
    unsorted = (*list)->head;
    while (unsorted) {
        sorted = out->head;      
        while (sorted && !cmp(unsorted->id, sorted->id)) {
            sorted = sorted->next;
        }
        if (sorted) {
            insertBeforeElement(out, sorted, sorted->value);
        } else {
            pushBack(out, unsorted->value);
        }
        unsorted = unsorted->next;
    }
    free(*list);
    *list = out;
}