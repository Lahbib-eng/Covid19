#ifndef _persoquar_H
#define _persoquar_H
#define PERIODE 14

struct lieu    // lieu du  confinement
{
    char* adresse_lieu;
    int cap_lieu;// capacité du lieu
    char* nom_lieu;
};

struct datte
{
    int mm,dd,yy;
};

struct patient
{
    int cin;
    char nom[30];
    char prenom[30];
    char adr[30];
    int age;
    char etat[10];
    char maladie[20][30];
    struct datte deb;
    struct datte fin;
    struct lieu lieu;
    char *cont; //cotamination
};
//typedef struct patient pquar;


struct hopital
{
    int id;
    char nom[20];
    char adresse [20];
    int nb_lits_dispo;
    int nbdoc;
    char *cat; // categories
};


void returnfunc_quar(void);
void main_quar(void);
void ajout_quar(void);
void supp_quar(void);
void modif_quar(void);
void recherche_quar(void);
void liste_quar(void);
void liste_cont(void);
int  getdata_pers();
int  checkid_pers(int);
void menu_quar();
void date(void);
void createlieufile();
void affect_lieu(void);
#endif

