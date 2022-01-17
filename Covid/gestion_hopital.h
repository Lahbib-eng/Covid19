#ifndef gestion_hopital_h
#define gestion_hopital_h

struct hopital
{   int id;
    char nom[20];
    char adresse [20];
    int nb_lits_dispo;

    int nbdoc;
    char *cat; // categories

};
void returnfunc(void);
void mainmenu();
void ajout_hop(void);
void supp_hop(void);
void modif_hop(void);
void recherche_hop(void);
void liste_hop(void);
int  getdata();
int  checkid(int);




#endif

