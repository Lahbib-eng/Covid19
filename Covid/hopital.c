#include<string.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include "hopital.h"
/*int creer_liste_besoin(besoin BE[],int n,cellule **l){

	int i;
	*l=NULL;
	cellule *p,*q;
	for(i=0;i<n;i++)
	{
		p=(cellule*)malloc(sizeof(cellule));
		p->e.nom_hopital=(char*)malloc(sizeof(char));
	    strcpy(p->e.nom_hopital,BE[i].nom_hopital);
	    p->e.need=(char*)malloc(sizeof(char));
	    strcpy(p->e.need,BE[i].need);
		p->suiv=NULL;
		if(*l==NULL)
		{
			*l=p;
			q=p;
		}
		else
		{
			q->suiv=p;
			q=p;
		}
	}
return n;
}
*/
//ajouter un besoin
cellule* ajouter_liste_hopital(cellule* liste)
{
    FILE* hopital_file;
    hopital_file=fopen("hopital.dat", "r");
    hopital hop;
    cellule *N;

	while(fread(&hop, sizeof(hopital), 1, hopital_file)){
    N=(cellule*)malloc(sizeof(cellule));
    N->e.id=hop.id;
    N->e.need_money=hop.need_money;
	strcpy(N->e.nom_hopital,hop.h_name);
//	N->e.need=(besoin*)malloc(sizeof(besoin));
	  for(int i=0; i<5;i++){
        if(strcmp(hop.need[i], "")){
            strcpy(N->e.need[i],hop.need[i]);
        }
      }
     N->suiv=liste;
     liste=N;

	}
	fclose(hopital_file);
  return N;

}

// afficher la liste des besoin
void Afficher_liste_besoin(cellule *l)
{
	if(l==NULL)
	{
		printf("aucun element n'existe dans la liste !!\n");
	}
	else
	{
		while(l!=NULL)
		{
            printf("l'hopital numéro: %d\n",l->e.id);
			printf("l'hopital: %s\n",l->e.nom_hopital);
			printf("le montant :  %f\n",l->e.need_money);
			 printf("les besoins sont:\n");
                for(int i=0; i<6;i++){
                  if(strcmp(l->e.need[i], "")!=1){
                            printf(" %s \n",l->e.need[i]);

                  }

                }
	    	printf("\n");
	    	l=l->suiv;
		}
	}
}
void ajouter_besoin(cellule* l,int x,char bes[30]){

	if(l==NULL)
	{
		printf("aucun element n'existe dans la liste !!\n");
	}
	else
	{
		while(l!=NULL)
		{
            if(l->e.id==x){
                    strcpy(l->e.need[5],bes);

            }

	    	printf("\n");
	    	l=l->suiv;
		}
	}


}
void supprimer_besoin(cellule* l,int x,char bes[30]){
    int i,trouve=0;
    i=0;
	if(l==NULL)
	{
		printf("aucun element n'existe dans la liste !!\n");
	}
	else
	{
		while(l!=NULL)
		{
            if(l->e.id==x){
                    while(i<6 && trouve==0){
                        if(strcmp(l->e.need[i],bes)==0){
                           strcpy(l->e.need[i],l->e.need[i+1]);
                           if(l->e.need[i+1]){
                           strcpy(l->e.need[i+1],l->e.need[i+2]);
                           }
                           if(l->e.need[i+2]){
                           strcpy(l->e.need[i+2],l->e.need[i+3]);
                           }
                           if(l->e.need[i+3]){
                           strcpy(l->e.need[i+3],l->e.need[i+4]);
                           }
                           if(l->e.need[i+4]){
                           strcpy(l->e.need[i+4],l->e.need[i+5]);
                           }
                           trouve=1;
                           }
              i++;
                    }
                if(trouve==0)
                    printf("Malhereursement !!!");
                else
                printf("merci pour votre gentillesse");

            }
	    	l=l->suiv;
		}

	}


}
void Afficher_liste_dons(cellule *l,int x)
{
	if(l==NULL)
	{
		printf("aucun element n'existe dans la liste !!\n");
	}
	else
	{
		while(l!=NULL)
		{
         if(l->e.id==x){
            printf("l'hopital numéro: %d\n",l->e.id);
			printf("l'hopital: %s\n",l->e.nom_hopital);
			printf("le montant :  %f\n",l->e.need_money);
			 printf("les besoins sont:\n");
                for(int i=0; i<5;i++){
                        if(strcmp(l->e.need[i], "")!=1){
                            printf(" %s \n",l->e.need[i]);
                        }

                }
         }
	    	l=l->suiv;
		}
	}
}
void supprimer_montant(cellule* l,int x,float montant){

	if(l==NULL)
	{
		printf("aucun element n'existe dans la liste !!\n");
	}
	else
	{
		while(l!=NULL)
		{
            if(l->e.id==x){
                    if(l->e.need_money<montant){
                        l->e.need_money=0;
                    }
                    else{
                        l->e.need_money=l->e.need_money-montant;

                    }
                printf("merci pour votre gentillesse");

            }
	    	l=l->suiv;
		}

	}


}

void Menu4(cellule* N)
{

    int choix2;
    do
    {
        printf("=====================================================================================\n");
        printf("*--------------------------------Voici le Menu N�4----------------------------------*\n");
        printf("=====================================================================================\n\n");
        printf("01 |Liste des Hopitaux Publics avec leurs besoins\n");
        printf("02| Ajout d'un Besoin.\n");
        printf("03| faire un  Dons .\n");
        printf("04|***Menu Principal.\n");
        printf("05| Quitter.\n");
        scanf("%d", &choix2);
        system("cls");
        if (choix2 < 1 || choix2 > 6)
        {
            printf("\votre choix doit etre entre [1..6]\n");
            printf("Cliquez Pour continuer SVP");
            getch();
            system("cls");

        }
    }while (choix2 < 1 || choix2 > 6);


        switch (choix2)
        {
        case 1:{
            printf("*--------------------Voici la liste des hopitaux publics avec leurs besoins----------------* \n");
            Afficher_liste_besoin(N);
            getch();
                        system("cls");
                         Menu4(N);
            break;
        }
        case 2:{
            char ch[30];
            int x;
            printf("Donner le besoin a ajouter\n");
            scanf("%s",ch);
            do{  printf("*------------------donner le numero du hopital qui possede ce besoin:---------------*\n");

                    scanf("%i",&x);
            }while(x < 1 || x > 16);
            ajouter_besoin(N,x,ch);
            printf("ajout avec succes\n");
            Afficher_liste_besoin(N);
           printf("Cliquez sur un boutton pour continuer!");
                    getch();
                    system("cls");
                    Menu4(N);
            break;

        }
        int d,x;
        float m;
        char be[30];
        case 3:{

                        printf("Merci pour votre aide\n ");
             do{
            printf("*----------------les type de dons possible:--------------*\n ");
            printf("1-dons en espece : \n");
            printf("2-dons en materiels :\n");
            scanf("%i",&d);
             }while(d<1 || d>2);
             if(d==1){
                 do{
                    printf("choisir le numero d'hopital que voulez vous faire le dons ");
                    scanf("%i",&x);
                 }while( x<1 || x>16);
               printf("donner le montant :\n");
               scanf("%f",&m);
               supprimer_montant(N,x,m);
                Afficher_liste_dons(N, x);
             }
            else{
                do{
                    printf("choisir le numero d'hopital que voulez vous faire le dons ");
                    scanf("%i",&x);
                 }while( x<1 || x>16);

                 printf("donner le besoin: \n");
                 scanf("%s",be);
                 supprimer_besoin(N,x,be);
                 Afficher_liste_dons(N, x);
            }
           getch();
                        system("cls");
                          Menu4(N);
                        break;

        }

        }
}

