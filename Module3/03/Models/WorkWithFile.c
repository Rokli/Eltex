#include "WorkWithFile.h"

void SaveList(List* phoneBook){
    char* fileName = "phonebook.txt";
    Node* tmp = phoneBook->head;

    FILE *fp = fopen(fileName, "w");

    if (!fp)
    {
        printf("Не получилось открыть файл\n");
        return;
    }

    while(tmp){
        fprintf(fp,"{\n");
        fprintf(fp, "\tID:%d\n", tmp->value.id);
        fprintf(fp, "\tNAME:%s\n", tmp->value.name);
        fprintf(fp, "\tSURNAME:%s\n", tmp->value.surname);
        fprintf(fp, "\tPATRONYMIC:%s\n", tmp->value.patronymic);
        fprintf(fp, "\tPOST:%s\n", tmp->value.post);
        fprintf(fp, "\tEMAIL:%s\n", tmp->value.email);
        fprintf(fp, "\tHOMEPHONE:%s\n", tmp->value.numberPhone.homePhone);
        fprintf(fp, "\tWORKPHONE:%s\n", tmp->value.numberPhone.workPhone);
        fprintf(fp,"}\n");
        tmp = tmp->next;
    }
    
    fclose(fp);
}
void LoadPhoneBook(List phoneBook){
    
}