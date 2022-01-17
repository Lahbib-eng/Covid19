#include <stdio.h>
#include<stdlib.h>
#include <windows.h>
#include <conio.h>
#include "lstpatient.h"
#include "eltpatient.h"
#include "hopital.h"
#include "ctrsaisie.h"
///int difference()

//LISTE * l = NULL;
NOEUD * ll = NULL;
int choix = 1000; //je donne n'importe quelle valeur
void Color(int couleurDuTexte, int couleurDeFond) // fonction d'affichage de couleurs
{
    HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H, couleurDeFond * 16 + couleurDuTexte);
}
int main()
{
    system("color 9");
    int choix1;
    LISTE * l = NULL;
    l = listeCreer();
    do
    {
        printf("==========================================================================================================\n");
        printf("*--------------------------------------------Menu Principale---------------------------------------------*\n");
        printf("==========================================================================================================\n\n");
        printf("1 | Gestion des patients.\n");
        printf("2 | Gestion des hopitaux.\n");
        printf("3 | Gestion des personnes en quarantaines.\n");
        printf("4 | Gestion des dons pour les hopitaux pulics.\n");
        printf("5 | Quitter\n");
        printf(" Saisir Votre choix SVP : \n");
        scanf("%d", & choix1);
        system("cls");
        if (choix1 < 1 || choix1 > 5)
        {
            printf("Le choix doit etre entre 1 et 5!\n");
            printf("Cliquez sur un boutton pour continuer");
            getch();
            system(" color 07");
        }
    }
    while (choix1 < 1 || choix1 > 5);

    switch (choix1)
    {
    case 1: //gestion des patients
    {
        int choix2;
        choix2 = 0;
        while (1)
        {
            do
            {
                printf("=====================================================================================\n");
                printf("*________________________________Voici le Menu N1______________________________\n");
                printf("=====================================================================================\n\n");
                printf("1 | Ajout d'un nouveau patient.\n");
                printf("2 | affichage de la liste des patients.\n");
                printf("3 | Modification d'un etat d'un patient.\n");
                printf("4 | Rechercher Un patient.\n");
                printf("5 | Suppression d'un patient.\n");
                printf("6 | Localisation Geographique.\n");
                printf("7 | Visalisation du reseaux d'un patient.\n");
                printf("8 | Menu principal.\n");
                printf("9 | Quitter.\n");
                printf("Saisir Votre choix SVP : \n");

                scanf("%d", & choix2);
                if (choix2 < 1 || choix2 > 9)
                {
                    printf("\votre choix doit etre entre [1..9]\n");
                    printf("Cliquez Pour continuer SVP");
                    getch();
                    system("cls");
                }
            }
            while (choix2 < 1 || choix2 > 9);
            switch (choix2)
            {
            case 1: //ajout d'un nouveau patient
            {
                //l = listeCreer();
                system("cls");
                liste_ajouter(l);
                printf("patient ajouté avec succès\n");
                printf("*---------------Cliquez sur un boutton pour continuer!---------------*");
                getch();
                system("cls");
                break;
            }
            case 2: //affichage de la liste des patient
            {
                system("cls");
                printf("Voici notre liste des patients :\n");
                listeAfficher(l);
                printf("*---------------Cliquez sur un boutton pour continuer!---------------*");
                getch();
                system("cls");
                break;
            }
            case 3:
            {
                char* cin="";
                do
                {
                    printf("*-------------------------------Donnez votre cin de personne à modifié:------------------------*\n ");
                    scanf("%s", cin);
                    if (isCIN(cin) ==  0)
                    {
                        printf("La CIN doit etre entre [1..9] et de 8 caractères \n");
                        printf("Cliquez Pour continuer SVP");
                        getch();
                        system("cls");
                    }
                }
                while(isCIN(cin) ==  0);

                NOEUD *f;
                f = (NOEUD*) malloc(sizeof(NOEUD));
                f = chercher_chaine_double("cin",cin,l);

                //char *etat;
                do
                {
                    printf("\nQuel est le nouveau etat du patient ? :") ;
                    scanf("%s",f->patient->etat);

                    if (strcmp(f->patient->etat,"normal") && strcmp(f->patient->etat,"critique"))
                    {
                        printf("La champs doit etre normal ou critique \n");
                        printf("Cliquez Pour continuer SVP");
                        getch();
                        system("cls");
                    }
                }
                while(strcmp(f->patient->etat,"normal") && strcmp(f->patient->etat,"critique"));

                printf("Patient est changé avec succès!\n");
                break;
            }
            case 4:
            {
                system("cls");
                printf("Voici le patient que vous etes entrain de chercher : \n");
                char cin[9];
                //int verif = 0,h;
                do
                {
                    system("cls");
                    printf("*-------------------------------Donnez votre cin:------------------------*\n ");
                    scanf("%s", cin);
                    if (isCIN(cin) ==  0)
                    {
                        printf("La CIN doit etre entre [1..9] et de 8 caractères \n");

                    }
                }
                while(isCIN(cin) ==  0);
                /*do {
                  printf("*-------------------------------Donnez votre cin:------------------------* ");
                  scanf("%s", cin);
                  for (h = 0; h < 8; h++) {
                    if (cin[h] < '0' || cin[h] > '9')
                      verif = 1;
                  }
                } while (verif == 1 || strlen(cin) < 8);*/
                NOEUD *f;
                f = (NOEUD*) malloc(sizeof(NOEUD));
                f = chercher_chaine_double("cin",cin,l);
                affiche_recherche_double(f);
                printf("Cliquez Pour continuer SVP");
                getch();
                system("cls");
                break;
            }
            case 5:
            {
                char cin[9];

                do
                {
                    printf("donner la cin du patient a supprimer: ");
                    scanf("%s", cin);
                    if (isCIN(cin) ==  0)
                    {
                        printf("La CIN doit etre entre [1..9] et de 8 caractères \n");
                        printf("Cliquez Pour continuer SVP");
                        getch();
                        system("cls");
                    }
                }
                while(isCIN(cin) ==  0);
                if(supprimer_patient(cin, l))
                {
                    printf("Patient est supprimé avec succès.\n");
                }
                else
                {
                    printf("Echec de suppression !\n");
                }
                printf("Cliquez Pour continuer SVP");
                getch();
                system("cls");
                break;
            }
            case 6:
            {
                system("cls");
                printf("la localisation geographique des patients:");
                printMap(l);
                printf("Cliquez Pour continuer SVP");
                getch();
                system("cls");
                break;
            }
            case 7:
            {
                printf("visualisation du reseau du patient : \n");
                char cin[9];
                do
                {
                    printf("*-------------------------------Donnez votre cin:------------------------*\n ");
                    scanf("%s", cin);
                    if (isCIN(cin) ==  0)
                    {
                        printf("La CIN doit etre entre [1..9] et de 8 caractères \n");

                    }
                }
                while(isCIN(cin) ==  0);
                getContacts(l,cin);
                printf("Cliquez Pour continuer SVP");
                getch();
                system("cls");
                break;
            }
            case 8:
            {
                main();
                break;
            }
            case 9:
            {
                exit(0);
                break;
            }

            }

        }
        break;
    }

    case 2: //gestion des hopitaux
    {
        //int choix2;
        while (1)
        {
               mainmenu();
        }
        break;
    }
    /*******************************************************/
    case 3: //gestion des personnes en quarantaines
    {
        //int choix2;
        while (1)
        {
            menu_quar();
        }
        break;
    }

    /*********************************************/

    case 4:
    {
        FILE* hopital_file;
        hopital_file=fopen("hopital.dat", "w");
        if (hopital_file == NULL)
        {
            fprintf(stderr, "\nError opend file\n");
            exit (1);
        }
        hopital hopitale1 = {1, "Hôpital",{"tttttttttttttt","kkkkkkkkkkkk","bbbbbbbbbbbbbb","hhhhhhhhhhhhh","sssssssssssss"},1500};
        hopital hopitale2 = {2, " Hôpital Habib Thameur",{"combinison","gggg","ddddddd","hhhhhhhh","ggggggggggggg"},2550};
        hopital hopitale3 = {3, "Hôpital Aziza Othman",{"bavette","ggggggg","eeeeeeeee","dddddddd","nnnnnnnn"}};
        hopital hopitale4 = {4, "Hôpital La Rabta",{"combinison","ggggggg","eeeeeeeee","dddddddd","nnnnnnnn"}};
        hopital hopitale5 = {5, "Institut Salah Azaiez",{"bavette","ggggggg","eeeeeeeee","dddddddd","nnnnnnnn"}};
        hopital hopitale6 = {6, "Institut Hedi Raies",{"","ggggggg","eeeeeeeee","dddddddd","nnnnnnnn"}};
        hopital hopitale7 = {7, "InstitutNationalNeurologie",{"combinison","ggggggg","eeeeeeeee","dddddddd","nnnnnnnn"}};
        hopital hopitale8 = {8, "Institut Mohamed Kassab",{"bavette","ggggggg","eeeeeeeee","dddddddd","nnnnnnnn"}};
        hopital hopitale9 = {9, "Centre de Maternité",{"combinison","ggggggg","eeeeeeeee","dddddddd","nnnnnnnn"}};
        hopital hopitale10 = {10, "HôpitaldePneumo-Phtisiologie",{"bavette","ggggggg","eeeeeeeee","dddddddd","nnnnnnnn"}};
        hopital hopitale11 = {11, "Hôpital Razi",{"tttttttttttttt","ggggggg","eeeeeeeee","dddddddd","nnnnnnnn"}};
        hopital hopitale12 = {12, "Hôpital Sahloul",{"combinison","ggggggg","eeeeeeeee","dddddddd","nnnnnnnn"}};
        hopital hopitale13 = {13, "Hôpital Farhat Hached",{"bavette","ggggggg","eeeeeeeee","dddddddd","nnnnnnnn"}};
        hopital hopitale14 = {14, "Hôpital Fattouma Bourguiba",{"combinison","ggggggg","eeeeeeeee","dddddddd","nnnnnnnn"}};
        hopital hopitale15 = {15, "Hôpital Hédi Chaker",{"bavette","ggggggg","eeeeeeeee","dddddddd","nnnnnnnn"}};
        hopital hopitale16 = {16, "Hôpital Habib Bourguiba",{"combinison","ggggggg","eeeeeeeee","dddddddd","nnnnnnnn"}};

        fwrite (&hopitale1, sizeof(hopital), 1, hopital_file);
        fwrite (&hopitale2, sizeof(hopital), 1, hopital_file);
        fwrite (&hopitale3, sizeof(hopital), 1, hopital_file);
        fwrite (&hopitale4, sizeof(hopital), 1, hopital_file);
        fwrite (&hopitale5, sizeof(hopital), 1, hopital_file);
        fwrite (&hopitale6, sizeof(hopital), 1, hopital_file);
        fwrite (&hopitale7, sizeof(hopital), 1, hopital_file);
        fwrite (&hopitale8, sizeof(hopital), 1, hopital_file);
        fwrite (&hopitale9, sizeof(hopital), 1, hopital_file);
        fwrite (&hopitale10, sizeof(hopital), 1, hopital_file);
        fwrite (&hopitale11, sizeof(hopital), 1, hopital_file);
        fwrite (&hopitale12, sizeof(hopital), 1, hopital_file);
        fwrite (&hopitale13, sizeof(hopital), 1, hopital_file);
        fwrite (&hopitale14, sizeof(hopital), 1, hopital_file);
        fwrite (&hopitale15, sizeof(hopital), 1, hopital_file);
        fwrite (&hopitale16, sizeof(hopital), 1, hopital_file);
        printf("contents to file written successfully !\n");
        fclose (hopital_file);
        cellule* N=NULL;
        N=ajouter_liste_hopital(N);
        Menu4(N);

    }

    case 5:
    {
        printf("*-----------------------------Merci pour votre visite A la prochaine---------------------------*\n\n\n");
        break;
    }

    }
}


