#ifndef _eltpatient_H
#define _eltpatient_H
struct CONTACT
{
    char nom[30];
    char prenom[30];
    char tel[8];
} ;
typedef struct CONTACT CONTACT;

struct PATIENT
{
    char nom[30];
    char prenom[30];
    char adr[30];
    int age;
    char cin[9];
    char contamination[5];
    char etat[10];
    int nbMaladies;
    char maladie[20][20];
    int nbContacts;
    CONTACT *contacts;
} ;
typedef struct PATIENT PATIENT;


#endif // eltcontact
