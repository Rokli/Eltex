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
int IdValue(char *name){

    if(strcmp(name,"ID") == 0) return 0;

    if(strcmp(name,"NAME") == 0) return 1;

    if(strcmp(name,"SURNAME") == 0) return 2;

    if(strcmp(name,"PATRONYMIC") == 0) return 3;

    if(strcmp(name,"POST") == 0) return 4;

    if(strcmp(name,"EMAIL") == 0) return 5;

    if(strcmp(name,"HOMEPHONE") == 0) return 6;

    if(strcmp(name,"WORKPHONE") == 0) return 7;

    return -1;

}
void LoadPhoneBook(List* phoneBook){

    Person person;

    char* fileName =  "phonebook.txt";
    char str[MAX_LENGTH_CHAR];
    FILE *fp = fopen(fileName, "r");

    while((fscanf(fp, "%s", str))!=EOF)
    {
        if(strcmp(str, "{") == 0) continue;
        if(strcmp(str, "}") == 0){
            if(phoneBook->head == NULL){
                pushBack(phoneBook,person,person.id);
            }else{
                insert(phoneBook,person.id,person);
            }
            continue;
        }
        char *name = strtok(str,":");
        char *value = strtok(NULL,":");
        if(name != NULL && value != NULL){
            switch (IdValue(name))
            {
                case 0:
                    person.id = atoi(value);
                case 1:
                    strcpy(person.name,value);
                    break;
                case 2:
                    strcpy(person.surname,value);
                    break;
                case 3:
                    strcpy(person.patronymic,value);
                    break;
                case 4:
                    strcpy(person.post,value);
                    break;
                case 5:
                    strcpy(person.email,value);
                    break;
                case 6:
                    strcpy(person.numberPhone.homePhone,value);
                    break;
                case 7:
                    strcpy(person.numberPhone.workPhone,value);
                    break;
                default:
                    break;
            }
        }
    }

    fclose(fp);
}