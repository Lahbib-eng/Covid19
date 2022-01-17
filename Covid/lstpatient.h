#ifndef _LstPatient_H
#define _LstPatient_H
#include "ELTPRIM.h"
#include "eltpatient.h"

struct NOEUD
{
    PATIENT *patient;
    PATIENT *lstpersonne;
    struct NOEUD *precedent;
    struct NOEUD *suivant;
};
typedef struct NOEUD NOEUD;

typedef struct
{
    NOEUD *tete;
    NOEUD *queue;
    int lg;
} LISTE;
LISTE* listeCreer(void);
NOEUD* noeudCreer(PATIENT *e);
void listeDetruire(LISTE);
int estVide(LISTE*);
int estSaturee(LISTE*);
int listeTaille(LISTE*);
PATIENT *recuperer(LISTE*, int);
int inserer(LISTE, PATIENT,int);
int supprimer (LISTE *L, int pos );
void listeAfficher(LISTE*);
LISTE* listeCopier(LISTE*);
int listeComparer(LISTE*, LISTE*);
LISTE* liste_ajouter(LISTE *l);
NOEUD *chercher_chaine_double(char*, char*, LISTE *LP);
void affiche_recherche_double(NOEUD*);
int supprimer_patient(char*,LISTE*);
void getContacts(LISTE*,char*);
void printMap(LISTE *);
#endif


