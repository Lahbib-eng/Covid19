
#ifndef hopital_h
#define hopital_h
typedef struct
{
    int id;
    char nom_hopital[20];
    int nbr[20];
    char need[20][20];
    float need_money ;
} besoin;
typedef struct
{
    int id;
    char h_name[30];
    char need[30][30];
    float need_money ;
} hopital;
//liste simplement chainée
/*typedef struct{
    int id;
    char h_name[100];
    char need[30];
}hopital;*/
typedef struct cellule cellule;
struct cellule
{
    besoin e;
    cellule *suiv;
};
int creer_liste_besoin(besoin BE[],int n,cellule **l);
void Afficher_liste_besoin(cellule *l);
cellule* ajouter_liste_hopital(cellule* N);
void ajouter_besoin(cellule* l,int x,char bes[30]);
void supprimer_besoin(cellule* l,int x,char bes[30]);
void Afficher_liste_dons(cellule *l,int x);
void supprimer_montant(cellule* l,int x,float m);
void Menu4(cellule*);
#endif // hopital_h

