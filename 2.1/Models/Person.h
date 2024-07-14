#ifndef Person_h
#define Person_h

#include <stdio.h>
#include <string.h>
#define N 512


typedef struct{
    char vkontakte[N];
    char ok[N];
    char facebook[N];
} socialNetwork;

typedef struct{
    char homePhone[N];
    char workPhone[N];
}mobilephone;

typedef struct {
    int id;
    char name[N];
    char surname[N];
    char patronymic[N];
    char post[N];
    mobilephone numberPhone;
    char email[N];
    socialNetwork socialNetwork;
} Person;

Person CreatePerson();  

void AddPerson(Person phoneBook[N]);  

void EditMobilePhone(Person phoneBook[N],int id);

void EditSocialNetwork(Person phoneBook[N],int id);

#endif  
