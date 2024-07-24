#ifndef person_h
#define person_h

#include <stdio.h>
#include <string.h>

#define MAX_LENGTH_CHAR 128
#define MAX_LENGTH_STRUCT 5


typedef struct{
    char name[MAX_LENGTH_CHAR];
    char address[MAX_LENGTH_CHAR];
} socialNetwork;

typedef struct{
    char homePhone[MAX_LENGTH_CHAR];
    char workPhone[MAX_LENGTH_CHAR];
}mobilephone;

typedef struct {
    int id;
    char name[MAX_LENGTH_CHAR];
    char surname[MAX_LENGTH_CHAR];
    char patronymic[MAX_LENGTH_CHAR];
    char post[MAX_LENGTH_CHAR];
    mobilephone numberPhone;
    char email[MAX_LENGTH_CHAR];
    socialNetwork socialNetwork[MAX_LENGTH_STRUCT];
} Person;

Person CreatePerson();

Person EditNumberPhone(Person person);

Person EditSocialNetworks(Person person);

Person EditPerson(Person person);

#endif