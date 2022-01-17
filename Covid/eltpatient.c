#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include "ctrsaisie.h"
#include "eltprim.h"
#define PATIENT_VIDE_NULL
PATIENT* patientCreer (void)
{
    PATIENT *e;
    e = (PATIENT*) malloc(sizeof(PATIENT));
    return e;
}
/* Lib�ration de m�moire */
void elementDetruire (PATIENT* patient)
{
    free(patient);
}


/* Lecture d'un �l�ment*/
void elementLire(PATIENT* patient)
{
    int i;
    do
    {
        printf(" \nDonnez un nom svp :") ;
        scanf("%s",(patient)->nom);
        if(!isCarac(patient->nom))
        {
            printf("\votre choix doit etre une chaine de caractères\n");
            printf("Cliquez Pour continuer SVP");
            getch();
            system("cls");
        }
    }
    while(!isCarac((patient)->nom));

    do
    {
        printf(" \nDonnez un prenom svp :") ;
        scanf("%s",(patient)->prenom);
        if(!isCarac((patient)->prenom))
        {
            printf("\votre choix doit etre une chaine de caractères\n");
            printf("Cliquez Pour continuer SVP");
            getch();
            system("cls");
        }
    }
    while(!isCarac((patient)->prenom));


    printf(" \nDonnez une adresse svp :") ;
    scanf("%s",(patient)->adr);

    do
    {
        printf(" \nDonnez votre age :") ;
        scanf("%d",&((patient)->age));
        if((patient)->age<0||(patient)->age>100)
        {
            printf("\votre choix doit etre entre [0..100]\n");
            printf("Cliquez Pour continuer SVP");
            getch();
            system("cls");
        }
    }
    while ((patient)->age<0||(patient)->age>100);

    do
    {
        printf(" \nDonnez le numéro CIN :") ;
        scanf("%s",(patient)->cin);
        if (isCIN((patient)->cin) ==  0)
        {
            printf("La CIN doit etre entre [1..9] et de 8 caractères \n");
            printf("Cliquez Pour continuer SVP");
            getch();
            system("cls");
        }
    }
    while(isCIN((patient)->cin) ==  0);

    do {
        printf("\nLa Contamination est introduit ou non ? :");
        scanf("%s",(patient)->contamination);

        if (strcmp((patient)->contamination,"vrai") && strcmp((patient)->contamination,"faux"))
        {
            printf("La champs doit etre vrai ou faux \n");
            printf("Cliquez Pour continuer SVP");
            getch();
            system("cls");
        }
    }
    while(strcmp((patient)->contamination,"vrai") && strcmp((patient)->contamination,"faux"));

    do{
        printf("\nQuel est l'etat du patient ? :") ;
        scanf("%s",(patient)->etat);

        if (strcmp((patient)->etat,"normal") && strcmp((patient)->etat,"critique"))
        {
            printf("La champs doit etre normal ou critique \n");
            printf("Cliquez Pour continuer SVP");
            getch();
            system("cls");
        }
    }
    while(strcmp((patient)->etat,"normal") && strcmp((patient)->etat,"critique"));

    do
    {
        printf("\nCitez le nombre des maladies :") ;
        scanf("%d",&((patient)->nbMaladies));
        if((patient)->nbMaladies<0)
        {
            printf("\votre choix doit etre un entier positif\n");
            printf("Cliquez Pour continuer SVP");
            getch();
            system("cls");
        }
    }
    while((patient)->nbMaladies<0);


    for(i=0; i<(patient)->nbMaladies; i++)
    {
        do
        {
            printf(" \n citez la maladie num %d de ce patient svp : \n",i) ;
            scanf("%s",(patient)->maladie[i]);
            if(!isCarac((patient)->maladie[i]))
            {
                printf("\votre choix doit etre une chaine de caractères\n");
                printf("Cliquez Pour continuer SVP");
                getch();
                system("cls");
            }
        }
        while(!isCarac((patient)->maladie[i]));

    }

    do
    {
        printf("\nCitez le nombre des personnes en contact avec le patient :") ;
        scanf("%d",&((patient)->nbContacts));
        if((patient)->nbContacts<0)
        {
            printf("\votre choix doit etre un entier positif\n");
            printf("Cliquez Pour continuer SVP");
            getch();
            system("cls");
        }
    }
    while((patient)->nbContacts<0);
    CONTACT* contacts = (CONTACT*) malloc((patient)->nbContacts*sizeof(CONTACT));
    for(i=0; i<(patient)->nbContacts; i++)
    {
        printf(" \n Le contact num %d pour le patient %s",i,(patient)->cin);
        do
        {
            printf(" \n citez le nom de contact svp : \n") ;
            scanf("%s",(contacts+i)->nom);
            if(!isCarac((contacts+i)->nom))
            {
                printf("\votre choix doit etre une chaine de caractères\n");
                printf("Cliquez Pour continuer SVP");
                getch();
                system("cls");
            }
        }
        while(!isCarac((contacts+i)->nom));
        do
        {
            printf(" \n citez le prenom de contact svp : \n") ;
            scanf("%s",(contacts+i)->prenom);
            if(!isCarac((contacts+i)->prenom))
            {
                printf("\votre choix doit etre une chaine de caractères\n");
                printf("Cliquez Pour continuer SVP");
                getch();
                system("cls");
            }
        }
        while(!isCarac((contacts+i)->prenom));

        do
        {
            printf(" \n citez le tel de contact svp : \n") ;
            scanf("%s",(contacts+i)->tel);
            if (isCIN((contacts+i)->tel) ==  0)
            {
                printf("Le tel doit etre entre [0..9] et de 8 caractères \n");
                printf("Cliquez Pour continuer SVP");
                getch();
                system("cls");
            }
        }
        while (isCIN((contacts+i)->tel) ==  0);


    }
    patient->contacts = contacts;
}
/* Affichage d'un �l�ment*/
void elementAfficher(PATIENT *patient)
{
    int i;
    printf("\n nom= %s, prenom = %s  ,adresse = %s ,age= %d,CIN= %s ,contamination= %s,ETAT= %s ,\n",patient->nom, patient->prenom,patient->adr,patient->age,patient->cin,patient-> contamination,patient->etat);
    if(patient->nbMaladies>0)
    {
        printf("\n Ce patient a :");
        for(i = 0; i<patient->nbMaladies; i++)
        {
            if(i+1 == patient->nbMaladies)
            {
                printf("%s\n",patient->maladie[i]);
            }
            else
            {
                printf("%s,",patient->maladie[i]);
            }
        }
    }
    else
    {
        printf("\n Ce patient n'a pas des maladies\n");
    }

}
/* Affectation du 2eme argument dans le 1er qui est donc modifi� et pass� par
adresse */
void elementAffecter(PATIENT* e1, PATIENT* e2)
{
    *e1 = *e2 ;
}
/* Copie du contenu du deuxi�me argument dans le premier, les deux
arguments ont des adresses diff�rentes (duplication)*/
void elementCopier(PATIENT *e1, PATIENT* e2)
{
    *e1=*e2;
}
int elementComparer(PATIENT *e1, PATIENT *e2)
{
    return 0;
}

PATIENT* recuperer(LISTE *L, int pos)
{
    NOEUD *elt;
    int i;
    if (estVide(L))
    {
        printf ("\nListe vide");
        return NULL;
    }
    else
    {
        if ((pos < 1) || (pos > L->lg))
        {
            printf ("\nPosition invalide");
            return NULL;
        }
        else
        {
            elt=L->tete;
            for(i=0; i<pos; i++)
            {
                elt=elt->suivant;
            }
            return(elt->patient);
        }
    }
}
void getContacts(LISTE *l,char* cin)
{
    int i;
    if(estVide(l))
    {
        printf("La liste est vide !\n");
    }
    else
    {
        NOEUD *n= chercher_chaine_double("cin",cin,l);
        PATIENT *patient = n->patient;
        if(patient->nbContacts>0)
        {
            printf("\n Ce patient a été en contact avec:");
            CONTACT* contacts;
            contacts = patient->contacts;
            for(i = 0; i<patient->nbContacts; i++)
            {
                printf(" \nLe contact num %d ",i);
                printf(" \n le nom de contact svp : %s",contacts->nom);
                printf(" \n le prenom de contact svp : %s",contacts->prenom);
                printf(" \n le tel de contact svp : %s\n\n",contacts->tel);
            }
        }
        else
        {
            printf("\n Ce patient n'a pas des contacts\n");
        }
    }

}

