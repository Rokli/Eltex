#include "WorkWithFile.h"

void SaveList(List* phoneBook) {
    const char* fileName = "phonebook.bin";
    Node* tmp = phoneBook->head;

    FILE *fp = fopen(fileName, "wb"); 

    if (!fp) {
        printf("Не получилось сохранить\n");
        return;
    }

    while (tmp) {
        size_t written = fwrite(&tmp->value, sizeof(Person), 1, fp);
        tmp = tmp->next;
    }

    fclose(fp);
}
void LoadPhoneBook(List* phoneBook) {
    const char* fileName = "phonebook.bin"; 
    FILE *fp = fopen(fileName, "rb"); 

    if (fp == NULL) {
        perror("Заранее сохранённого списка нет");
        return;
    }

    Person person;

    while (fread(&person, sizeof(Person), 1, fp) == 1) {
        if (phoneBook->head == NULL) {
            pushBack(phoneBook, person, person.id); 
        } else {
            insert(phoneBook, person.id, person); 
        }
    }

    fclose(fp); 
}