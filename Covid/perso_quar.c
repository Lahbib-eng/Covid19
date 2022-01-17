#include <windows.h>
#include<stdio.h>                   // printf,scanf etc
#include<conio.h>                   //delay(),getch(),gotoxy(),etc.
#include <stdlib.h>
#include<string.h>                  //strcmp(),strcpy(),strlen(),etc
#include<time.h>
#include<dos.h>
#include"perso_quar.h"
char contamination[][10]= {"vrai","faux","provenance"};
FILE *fp,*ft,*fs,*fl,*lieu_file;
int x;
char findpers;
struct lieu l;
struct datte datte;
struct hopital a;
struct patient p;
void menu_quar()
{
    system("cls");
    /*******************************************************/
    int choix2 =0 ;
    do
    {
        printf("=====================================================================================\n");
        printf("*--------------------------------Voici le Menu N°3----------------------------------*\n");
        printf("=====================================================================================\n\n");
        printf("01 | Ajout d'une personne en quarantaine\n");
        printf("02 | Affichage des personnes en quarantaine.\n");
        printf("03 | Recherche d'une personne en quarantaine.\n");
        printf("04 | Suppression d'une personne du quarantaine.\n");
        printf("05 | Affichage des liste de lieux confinement d'etat disponible.\n");
        printf("06 | date.\n");
        printf("07 | lieu.\n");
        printf("08 | Affectation dans un lieu.\n");
        printf("09 | Quitter.\n");
        printf("Saisir Votre choix SVP : \n");
        scanf("%d",&choix2);
        /*********************************************/

        if (choix2 < 1 || choix2 > 9)
        {
            printf("\votre choix doit etre entre [1..8]\n");
            printf("Cliquez Pour continuer SVP");
            getch();
            system("cls");
        }
    }
    while (choix2 < 1 || choix2 > 8);

    switch(choix2)
    {
    case 1:
        ajout_quar();
        break;
    case 2:
        liste_quar();

        break;
    case 3:
        recherche_quar();

        break;
    case 4:
        supp_quar();
        break;
    case 5:
        liste_cont();
        break;
    case 6:
        date(); //
        break;
    case 7:
        createlieufile(); //
        break;
    case 8:
        affect_lieu();
        break;
    case 9:
        exit(0);

        break;


    default:
    {
        printf("resaisir votre choix\n");
        if(getch())
            menu_quar();
    }

    }
}



void ajout_quar(void)    //fonction d'ajout des hopitaux
{
    system("cls");
    //int i;

    printf("***************contamination introduite**************\n");

    printf("1. vrai\n"); // si oui

    printf("2. faux\n"); //si la contamination est locale

    printf("3. provenance\n"); //s'il arrive d'un autre pays

    printf("4. retour au menu\n");


    printf("Enter your choice:\n");
    scanf("%d",&x);
    if(x==4)//retour au menu principale

        menu_quar() ;
    system("cls");
    fp=fopen("quar.dat","ab+");
    if(getdata_pers()==1)
    {
        p.cont=contamination[x-1];
        fseek(fp,0,SEEK_END);
        fwrite(&p,sizeof(p),1,fp);
        fclose(fp);

        printf("enregistrement validee\n");

        printf("enregistrer plus?(Y / N):\n");
        if(getch()=='n')
            menu_quar();
        else
            system("cls");
        ajout_quar();
    }
}
void supp_quar()    //suppression de la fichier fp
{
    system("cls");
    int d;
    char another='y';
    while(another=='y')  //si l'utilisateur va supprimer une aute fois
    {
        system("cls");

        printf("Entrer l'ID du personne a supprime:");
        scanf("%d",&d);
        fp=fopen("quar.dat","rb+");
        rewind(fp);
        while(fread(&p,sizeof(p),1,fp)==1)
        {
            if(p.cin==d)
            {
                printf("cet personne existe");
                printf("nom du personne %s",p.nom);
                findpers='t';
            }
        }
        if(findpers!='t')
        {
            printf("aucun enregistrement trouvée\n");
            if(getch())
                menu_quar();
        }
        if(findpers=='t' )
        {
            printf("voulez vous vraiment supprimer?(Y/N):");
            if(getch()=='y')
            {
                ft=fopen("tester.dat","wb+");  //fichier temporelle pour la suppression
                rewind(fp);
                while(fread(&p,sizeof(p),1,fp)==1)
                {
                    if(p.cin!=d)
                    {
                        fseek(ft,0,SEEK_CUR);
                        fwrite(&p,sizeof(p),1,ft); //ecrire tous dans fichier temporelle sauf ceux qui on va surpprimer
                    }
                }
                fclose(ft);
                fclose(fp);
                remove("quar.dat");
                rename("tester.dat","quar.dat"); //copier tous de la fichier temprelle dans fp sauf ceux qui on va supprimer
                fp=fopen("quar.dat","rb+");
                if(findpers=='t')
                {
                    printf("suppression validee\n");
                    printf("voulez vous supprimer encore une fois?(Y/N)\n");
                }
            }
            else
                menu_quar();
            fflush(stdin);
            another=getch();
        }
    }
    menu_quar();
}
void recherche_quar()
{
    system("cls");
    int d=0;
    printf("*****************************RECHERCHE PERSONNE EN QUARANTAINE*********************************");
    printf("chercher par nom\n");
    fp=fopen("quar.dat","rb+"); //ouvrir la fichier
    rewind(fp);   //placer le pointeur au debut de la fichier
    char s[15];
    system("cls");
    printf("****chercher par nom****\n");

    printf("entrer le nom du personne:\n");
    scanf("%s",s);

    while(fread(&p,sizeof(p),1,fp)==1)
    {
        if(strcmp(p.nom,(s))==0) //tester si p.name est le meme que s ou non
        {
            printf("cet personne existe\n");
            printf("Nom:%s\n",p.nom);
            printf("Prenom:%s\n",p.prenom);
            printf("Age:%d\n",p.age);
            printf("Adresse:%s\n",p.adr);
            printf("Maladie:%s\n",p.maladie);
            d++;
        }

    }
    if(d==0)
    {
        printf("\n cet personne n'existe pas");
    }
    printf("voulez vous chercher une autre fois?(Y/N)");
    if(getch()=='y')
        recherche_quar();
    else
    {
        menu_quar();



        getch();
        recherche_quar();
    }
    fclose(fp);
}

void liste_quar(void)  //liste des hopitaux
{
    int j;
    system("cls");
    printf("*********************************liste des hopitaux*****************************\n");
    printf("CONTAMINATION       \n");
    j=4;
    fp=fopen("quar.dat","rb");
    while(fread(&p,sizeof(p),1,fp)==1)
    {
        printf("%s||\n",p.cont);
        printf("|CIN\n");
        printf("%d|| \n",p.cin);
        printf("nom\n");
        printf("%s||\n",p.nom);
        printf("prenom\n");
        printf("%s||\n",p.prenom);
        printf("adresse\n");
        printf("%s\n",p.adr);
        printf("maladie\n");
        printf("%s\n",p.maladie);
        printf("%d\n",p.age);
        j++;
    }
    fclose(fp);
    returnfunc_quar();
}
void modif_quar(void)  //modification des informations des personnes en quarantine
{
    system("cls");
    int c=0;
    int d;
    printf("****MODIFIER LES INFORMATIONS DU PERSONNE EN QUARANTAINE****\n");
    char another='y';
    while(another=='y')
    {
        system("cls");
        printf("Entrer l'ID du personne:\n");
        scanf("%d",&d);
        fp=fopen("quar.dat","rb+");
        while(fread(&p,sizeof(p),1,fp)==1)
        {
            if(checkid_pers(d)==0)
            {
                printf("cet personne existe dans la liste\n");
                printf("l'ID du personne:%d\n",p.cin);
                printf("le nom:%s\n",p.nom);
                printf("Entrer un nouveau nom:\n");
                scanf("%s",p.nom);
                printf("Entrer une nouvelle adresse:\n");
                scanf("%s",p.adr);
                printf("entrer un nouveau age :\n");
                scanf("%d",&p.age);
                printf("Entrer une nouvelle maladie:\n");
                scanf("%s",p.maladie);
                printf("les informations sont modifies\n");
                fseek(fp,ftell(fp)-sizeof(p),0);
                fwrite(&p,sizeof(p),1,fp);
                fclose(fp);
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
    returnfunc_quar();
}
void returnfunc_quar(void)
{
    {
        printf(" taper entrer pour retourner au menu\n");
    }
a:
    if(getch()==13) //permettre l'utilisation du bouton entrer seulement
        menu_quar();
    else
        goto a;
}
int getdata_pers()
{
    int t;
    printf("entrer les informations au dessous\n");
    printf("Contamination:\n");
    printf("%s",contamination[x-1]);
    printf("\n cin du personne:\n");
    scanf("%d",&t);
    if(checkid_pers(t) == 0)
    {
        printf("\acet personne est deja en quarantine\a");
        getch();
        menu_quar();
        return 0;
    }
    // pour verifier apres si le personne est en quarantaine
    p.cin=t;

    printf("nom:\n");
    scanf("%s",p.nom);
    printf("prenom:\n");
    scanf("%s",p.prenom);
    printf("adresse:\n");
    scanf("%s",p.adr);
    do
    {
        printf("age:\n");
        scanf("%d",&p.age);
    }
    while (p.age<0);
    return 1;
}
void liste_cont()
{
    int j;
    system("cls");
    printf("*********************************liste du liste de confinement d'etat disponible*****************************\n");

    j=4;
    fl=fopen("lieu.dat","rb");
    while(fread(&l,sizeof(l),1,fl)==1)
    {
        printf("adresse:%s\n",l.adresse_lieu);
        printf("capacitee du lieu:\n");
        printf("%d\n",l.cap_lieu);
        printf("le nom du lieu\n");
        printf("%s\n",l.nom_lieu);

        j++;
    }
    fclose(fl);
    returnfunc_quar();
}
int checkid_pers(int t)  //tester si le personne est deja en quarantine
{
    rewind(fp);
    while(fread(&p,sizeof(p),1,fp)==1)
        if(p.cin==t)
            return 0;  //returns 0 si le personne est en quarantine
    return 1; //return 1 si non
}
void date(void)  //fonction qui retourne les dates du debit et du fin du confinement
{
    int t;

    system("cls");
    printf("********************************date de debut et du fin du confinement**************************\n");

    printf(" 1. chercher la date avec CIN\n");

    printf(" 2. tous les dattes du l'ensemble des personnes en confinement\n");

    printf("Entrer votre choix:\n");
    switch(getch())
    {
    case '1':  //personne confiné
    {
        system("cls");
        SYSTEMTIME stime;
        int c=0;
        char another='y';
        while(another=='y')
        {
            system("cls");


            printf("Entrer la cin du personne:\n");
            scanf("%d",&t);
            fp=fopen("quar.dat","rb");
            fs=fopen("date.dat","ab+");
            if(checkid_pers(t)==0) //personne qui est confiné
            {

                printf("cet personne existe\n");

                printf("Son nom est %s\n",p.nom);
                GetSystemTime(&stime);
                printf("Date du debut du confinement=%d-%d-%d\n",stime.wDay,stime.wMonth,stime.wYear);
                p.deb.dd=stime.wDay;
                p.deb.mm=stime.wMonth;
                p.deb.yy=stime.wYear;
                p.fin.dd=p.deb.dd+PERIODE;   //pour la date du fin du confinement
                p.fin.mm=p.deb.mm;
                p.fin.yy=p.deb.yy;
                if(p.fin.dd>30)
                {
                    p.fin.mm+=p.fin.dd/30;
                    p.fin.dd-=30;

                }
                if(p.fin.mm>12)
                {
                    p.fin.yy+=p.fin.mm/12;
                    p.fin.mm-=12;

                }

                printf("Date du fin du confinement:%d-%d-%d\n",p.fin.dd,p.fin.mm,p.fin.yy);
                fseek(fs,sizeof(p),SEEK_END);
                fwrite(&p,sizeof(p),1,fs);
                fclose(fs);
                c=1;
            }
            if(c==0)
            {
                printf("aucun enregistrement trouvee\n");
            }
            printf("voulez vous chercher un autre date(Y/N):\n");
            fflush(stdin);
            another=getche();
            fclose(fp);
        }

        break;
    }
    case '2':
    {
        system("cls");
        int j=4;
        printf("DATE DU DEBUT DU CONFINEMENT      | DATE DU FIN DU CONFINEMENT\n");
        fs=fopen("date.dat","rb");
        while(fread(&p,sizeof(p),1,fs)==1)
        {

            printf("%d-%d-%d                             |",p.deb.dd,p.deb.mm,p.deb.yy );

            printf("%d-%d-%d\n",p.fin.dd,p.fin.mm,p.fin.yy);
            j++;

        }
        fclose(fs);
        returnfunc_quar();
    }
    default:

        printf("\nchoix incorrect\n!");
        getch();
        date();
        break;
    }

    returnfunc_quar();

}
void createlieufile() // creation du fichier et afficher le lieu du confinement
{
    lieu_file=fopen("lieu.dat", "w+");
    if(lieu_file == NULL)
    {
        fprintf(stderr, "\nError opend file\n");
        exit (1);
    }
    typedef struct lieu lieu;
    lieu lieu1 = {"ariana",20,"yassmine"};
    lieu lieu2 = {"beja",20,"ramsam"};
    lieu lieu3 = {"ben arous",20,"golf royal"};
    lieu lieu4 = {"bizerte",20,"sidi salem"};
    lieu lieu5 = {"gabes",20,"villa jasmin"};
    lieu lieu6 = {"jendouba",20,"La Cigale Tabarka"};
    lieu lieu7 = { "kairouan",20,"la kasbah"};
    lieu lieu8 = { "kasserine",20,"dorra hotel"};
    lieu lieu9 = { "kebili",20,"L'Oasis"};
    lieu lieu10 = { "kef",20,"les pins"};
    lieu lieu11 = {"mahdia",20,"Mahdia Palace Thalasso"};
    lieu lieu12 = { "manouba",20,"aziza"};
    lieu lieu13 = { "medenine",20,"Royal Garden Palace"};
    lieu lieu14 = { "monastir",20,"Amir Palace Hotel"};
    lieu lieu15 = { "nabeul",20,"Palmyra Club Nabeul"};
    lieu lieu16 = { "sfax",20,"Movenpick Hotel Sfax "};
    lieu lieu17 = { "sidi bouzid",20,"Residence EL CASTILLO"};
    lieu lieu18 = { "siliana",20,"Coquette maison "};
    lieu lieu19 = { "sousse",20,"hotel paris"};
    lieu lieu20 = { "tataouine",20,"hotel dakyanus"};
    lieu lieu21 = { "tozeur",20,"la palmeraie"};
    lieu lieu22 = { "gafsa",20,"jugurtha palace"};
    lieu lieu23 = { "tunis",20,"dar el jeld"};
    lieu lieu24 = { "zaghouan",20,"les nymphes"};

// write struct to file
    fwrite (&lieu1, sizeof(lieu), 1, lieu_file);
    fwrite (&lieu2, sizeof(lieu), 1, lieu_file);
    fwrite (&lieu3, sizeof(lieu), 1, lieu_file);
    fwrite (&lieu4, sizeof(lieu), 1, lieu_file);
    fwrite (&lieu5, sizeof(lieu), 1, lieu_file);
    fwrite (&lieu6, sizeof(lieu), 1, lieu_file);
    fwrite (&lieu7, sizeof(lieu), 1, lieu_file);
    fwrite (&lieu8, sizeof(lieu), 1, lieu_file);
    fwrite (&lieu9, sizeof(lieu), 1, lieu_file);
    fwrite (&lieu10, sizeof(lieu), 1, lieu_file);
    fwrite (&lieu11, sizeof(lieu), 1, lieu_file);
    fwrite (&lieu12, sizeof(lieu), 1, lieu_file);
    fwrite (&lieu13, sizeof(lieu), 1, lieu_file);
    fwrite (&lieu14, sizeof(lieu), 1, lieu_file);
    fwrite (&lieu15, sizeof(lieu), 1, lieu_file);
    fwrite (&lieu16, sizeof(lieu), 1, lieu_file);
    fwrite (&lieu17, sizeof(lieu), 1, lieu_file);
    fwrite (&lieu18, sizeof(lieu), 1, lieu_file);
    fwrite (&lieu19, sizeof(lieu), 1, lieu_file);
    fwrite (&lieu20, sizeof(lieu), 1, lieu_file);
    fwrite (&lieu21, sizeof(lieu), 1, lieu_file);
    fwrite (&lieu22, sizeof(lieu), 1, lieu_file);
    fwrite (&lieu23, sizeof(lieu), 1, lieu_file);
    fwrite (&lieu24, sizeof(lieu), 1, lieu_file);
    printf("contents to file written successfully !\n");

// close file
    fclose (lieu_file);
    lieu_file=fopen("lieu.dat", "rb+");
    rewind(lieu_file);
    system("cls");
    while(fread(&l,sizeof(lieu),1,lieu_file)==1)
    {

        printf ("l'adresse du personne est :  %s  \n",p.adr);


        if(strcmp(l.adresse_lieu,(p.adr))==0)
        {
            printf(" %s \n",l.nom_lieu);
        }


        printf("\n");

    }
    fclose (lieu_file);

}
void affect_lieu(void)  //  affecter les personnes dans le lieu le plus proche
{
    system("cls");
    int c=0;
    int d;
    printf("****MODIFIER LES INFORMATIONS DU PERSONNE EN QUARANTAINE****\n");
    char another='y';
    while(another=='y')
    {
        system("cls");
        printf("Entrer l'ID du personne:\n");
        scanf("%d",&d);
        fp=fopen("quar.dat","rb+");
        fl=fopen("lieu.dat","rb+");
        while(fread(&p,sizeof(p),1,fp)==1)
        {
            if(checkid_pers(d)==0)
            {
                printf("cet personne existe dans la liste\n");
                printf("l'ID du personne:%d\n",p.cin);
                printf("le nom:%s\n",p.nom);

                if (p.adr==l.adresse_lieu)
                {
                    printf(l.nom_lieu);
                }
                d++;
                l.cap_lieu--;
                printf("cet personne est affectee avec succes\n");
                fseek(fp,ftell(fp)-sizeof(p),0);
                fwrite(&p,sizeof(p),1,fp);
                fclose(fp);
                c=1;
            }
            if(c==0)
            {
                printf("cet personne n'existe pas\n");
            }
        }
        printf("voulez vous affecter une autre personne?(Y/N)");
        fflush(stdin);
        another=getch() ;
    }
    returnfunc_quar();
}

int verifierchar (char s[])
{
    int t=1,i;
    for (i=0; s[i]!='\0'; i++)
    {
        if (((s[i]>='a') &&(s[i]<='z')) ||((s[i]>='A') && (s[i]<='Z')))
            t=-1;
    }
    return t;
}

