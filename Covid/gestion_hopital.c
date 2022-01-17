#include<stdio.h>                   // printf,scanf etc
#include<conio.h>                   //delay(),getch(),gotoxy(),etc.
#include <stdlib.h>
#include<string.h>                  //strcmp(),strcpy(),strlen(),etc
#include"gestion_hopital.h"

char catagories[][20]= {"privee","publique","besoin specifique"};
FILE *fm,*fj;
int s;
char findhop;
struct hopital a;

void mainmenu()
{

    system("cls");
    printf("=====================================================================================\n");
    printf("*--------------------------------Voici le Menu N°2----------------------------------*\n");
    printf("=====================================================================================\n\n");
    printf("1 | Ajout d'un nouveau hopital.\n");
    printf("2 | Modification d'un hopital.\n");
    printf("3 | Supprimer un hopital.\n");
    printf("4 | Rechercher Un hopital.\n");
    printf("5 | liste des hopitaux.\n");
    printf("6 | affectation du patient dans un hopital.\n");
    printf("7 | Menu principal.\n");
    printf("8 | Quitter.\n");
    printf("Saisir Votre choix SVP : \n");



    switch(getch())
    {
    case '1':
        ajout_hop();
        break;
    case '2':
        modif_hop();

        break;
    case '3':
        supp_hop();

        break;
    case '4':
        recherche_hop();
        break;
    case '5':
        liste_hop();
        break;
    case '6':
        printf("pas disponible");
    case '7':
        printf("pas disponible"); // affectation
    case '8':
        printf("pas disponible"); // menu principal
    case '9':
        exit(0);
        break;


    default:
    {
        printf("resaisir votre choix\n");
        if(getch())
            mainmenu();
    }

    }
}
void ajout_hop(void)    //fonction d'ajout des hopitaux
{
    system("cls");

    printf("***************CHOISIR UNE CATEGORIE**************\n");

    printf("1. privee\n");

    printf("2. publique\n");

    printf("3. besoin specifique\n");

    printf("4. retour au menu\n");


    printf("Enter your choice:\n");
    scanf("%d",&s);
    if (s==3)
    {
        printf("veuiller saisir le nombre de docteur specialisés :\n");
        scanf("%d",&a.nbdoc);
    }
    if(s==4)//retour au menu principale

        mainmenu() ;
    system("cls");
    fm=fopen("hop.dat","ab+");
    if(getdata()==1)
    {
        a.cat=catagories[s-1];
        fseek(fm,0,SEEK_END);
        fwrite(&a,sizeof(a),1,fm);
        fclose(fm);

        printf("enregistrement validee\n");

        printf("enregistrer plus?(Y / N):\n");
        if(getch()=='n')
            mainmenu();
        else
            system("cls");
        ajout_hop();
    }
}
void supp_hop()    //suppression de la fichier fp
{
    system("cls");
    int d;
    char another='y';
    while(another=='y')  //si l'utilisateur va supprimer une aute fois
    {
        system("cls");

        printf("Entrer l'ID du l'hopital a supprimer:\n");
        scanf("%d",&d);
        fm=fopen("hop.dat","rb+");
        rewind(fm);
        while(fread(&a,sizeof(a),1,fm)==1)
        {
            if(a.id==d)
            {
                printf("l'hopital existe\n");
                printf("nom du l'hopital %s\n",a.nom);
                findhop='t';
            }
        }
        if(findhop!='t')
        {
            printf("aucun enregistrement trouvée\n");
            if(getch())
                mainmenu();
        }
        if(findhop=='t' )
        {
            printf("voulez vous vraiment supprimer?(Y/N):");
            if(getch()=='y')
            {
                fj=fopen("test.dat","wb+");  //fichier temporelle pour la suppression
                rewind(fm);
                while(fread(&a,sizeof(a),1,fm)==1)
                {
                    if(a.id!=d)
                    {
                        fseek(fj,0,SEEK_CUR);
                        fwrite(&a,sizeof(a),1,fj); //ecrire tous dans fichier temporelle sauf ceux qui on va surpprimer
                    }
                }
                fclose(fj);
                fclose(fm);
                remove("hop.dat");
                rename("test.dat","hop.dat"); //copier tous de la fichier temprelle dans fp sauf ceux qui on va supprimer
                fm=fopen("hop.dat","rb+");
                if(findhop=='t')
                {
                    printf("suppression validee\n");
                    printf("voulez vous supprimer encore une fois?(Y/N)\n");
                }
            }
            else
                mainmenu();
            fflush(stdin);
            another=getch();
        }
    }
    mainmenu();
}
void recherche_hop()
{
    system("cls");
    int d=0;
    printf("*****************************RECHERCHE HOPITAL*********************************");
    printf("chercher par nom\n");
    fm=fopen("hop.dat","rb+"); //ouvrir la fichier
    rewind(fm);   //placer le pointeur au debut de la fichier
    char s[15];
    system("cls");
    printf("****chercher par nom****\n");

    printf("entrer le nom du l'hopital:\n");
    scanf("%s",s);

    while(fread(&a,sizeof(a),1,fm)==1)
    {
        if(strcmp(a.nom,(s))==0) //tester si a.name est le meme que s ou non
        {
            printf("l'hopital existe\n");
            printf("Nom:%s\n",a.nom);
            printf("Adresse:%s\n",a.adresse);
            printf("Nombre des lits disponibles:%d\n",a.nb_lits_dispo);
            d++;
        }

    }
    if(d==0)
    {
        printf("\n l'hopital n'existe pas");
    }
    printf("voulez vous chercher une autre fois?(Y/N)");
    if(getch()=='y')
        recherche_hop();
    else
    {
        mainmenu();



        getch();
        recherche_hop();
    }
    fclose(fm);
}

void liste_hop(void)  //liste des hopitaux
{
    int j;
    system("cls");
    printf("*********************************liste des hopitaux*****************************\n");
    printf(" CATEGORIE        ||          ID       ||      NOM       ||    ADRESSE  ||   NOMBRE DE LITS DISPONIBLE   \n");
    j=4;
    fm=fopen("hop.dat","rb");
    while(fread(&a,sizeof(a),1,fm)==1)
    {
        printf("%s          ||",a.cat);
        printf("%d          || ",a.id);
        printf("%s      ||",a.nom);
        printf("%s      ||   ",a.adresse);
        printf("%d         \n",a.nb_lits_dispo);
        printf("nombre du docteurs specifique:%d\n",a.nbdoc);
        j++;
    }
    fclose(fm);
    returnfunc();
}
void modif_hop(void)  //modification des informations des hopitaux
{
    system("cls");
    int c=0;
    int d;
    printf("****MODIFIER LES INFORMATIONS D'UN HOPITAL****\n");
    char another='y';
    while(another=='y')
    {
        system("cls");
        printf("Entrer l'ID du l'hopital:\n");
        scanf("%d",&d);
        fm=fopen("hop.dat","rb+");
        while(fread(&a,sizeof(a),1,fm)==1)
        {
            if(checkid(d)==0)
            {
                printf("l'hopital existe dans la liste\n");
                printf("l'ID de l'hopital:%d\n",a.id);
                printf("le nom du l'hopital est:%s\n",a.nom);
                printf("Entrer un nouveau nom:\n");
                scanf("%s",a.nom);
                printf("Entrer une nouvelle adresse:\n");
                scanf("%s",a.adresse);
                printf("nouveau nombre des lits disponible :\n");
                scanf("%d",&a.nb_lits_dispo);
                printf("les informations sont modifies\n");
                fseek(fm,ftell(fm)-sizeof(a),0);
                fwrite(&a,sizeof(a),1,fm);
                fclose(fm);
                c=1;
            }
            if(c==0)
            {
                printf("l'enregistrement n'existe pas\n");
            }
        }
        printf("modifier un autre enregistrement?(Y/N)");
        fflush(stdin);
        another=getch() ;
    }
    returnfunc();
}
void returnfunc(void)
{
    {
        printf(" taper entrer pour retourner au menu\n");
    }
a:
    if(getch()==13) //permettre l'utilisation du bouton entrer seulement
        mainmenu();
    else
        goto a;
}
int getdata()
{
    int t;
    printf("entrer les informations au dessous\n");
    printf("Category:\n");
    printf("%s",catagories[s-1]);
    printf("\n ID du l'hopital:\n");
    scanf("%d",&t);
    if(checkid(t) == 0)
    {
        printf("\al'hopital existe deja\a");
        getch();
        mainmenu();
        return 0;
    }
    // pour verifier apres si l'hopital existe
    a.id=t;
    printf("nom du l'hopital:\n");
    scanf("%s",a.nom);
    printf("adresse:\n");
    scanf("%s",a.adresse);
    printf("nombre de lits disponibles:\n");
    scanf("%d",&a.nb_lits_dispo);
    return 1;
}
int checkid(int t)  //tester si l'hospital exists dans la liste ou pas
{
    rewind(fm);
    while(fread(&a,sizeof(a),1,fm)==1)
        if(a.id==t)
            return 0;  //returns 0 si l'hopital existe
    return 1; //return 1 si non
}


