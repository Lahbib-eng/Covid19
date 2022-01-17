#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "eltprim.h"

#include "eltpatient.h"

#include "lstpatient.h"

LISTE* listeCreer(void)
{

    LISTE *p;
    p = (LISTE*) malloc(sizeof(LISTE));
    if (!p)
        printf("\nPlus d'espace");
    else
    {
        p -> lg = 0;
        p -> queue = NULL;
        p -> tete = NULL;
    }
    return p;
}
int estVide(LISTE*L)
{
    return (L -> lg == 0);
}
int estSaturee(LISTE*L)
{
    NOEUD *temp;
    int saturee = 1; /* on suppose m�moire satur�e */
    temp = (NOEUD*) malloc(sizeof(NOEUD));
    if (temp != NULL)
    {
        saturee = 0; /* m�moire non satur�e */
        free(temp);
    }
    return saturee;
}
int listeTaille(LISTE*L)
{
    return (L -> lg);
}
LISTE* listeCopier(LISTE*L)
{
    LISTE *LR = listeCreer();
    int i;
    PATIENT *elt;
    for (i = 1; i <= L -> lg; i++)
    {
        elt = patientCreer();
        elementCopier(elt, recuperer(L, i));
        //inserer(LR, elt, i);
    }
    return LR;
}
int listeComparer(LISTE* L1, LISTE* L2)
{
    int test = 1;
    int i = 1;
    if (listeTaille(L1) != listeTaille(L2)) test = 0;
    while ((i <= listeTaille(L1)) && (test))
    {
        if (elementComparer(recuperer(L1, i), recuperer(L2, i)) != 0)
            test = 0;
        i++;
    }
    return test;
}
void listeAfficher(LISTE *l)
{
    if(estVide(l)||!l)
    {
        printf("La liste est vide !\n");
    }
    else
    {
        NOEUD *p = (NOEUD*) malloc(sizeof(NOEUD));
        p = l -> tete;
        while(p!=NULL)
        {
            //printf("\n nom= %s,prenom= %s  , adresse = %s ,age= %d, CIN= %s ,contamination= %s, ETAT= %s , maladie= \n",p->patient->nom, p->patient->prenom,p->patient->adr,p->patient->age,p->patient->cin,p->patient-> contamination,p->patient->etat);
            elementAfficher(p -> patient);
            p = p -> suivant;
        }
    }
}


NOEUD* noeudCreer(PATIENT *e)
{
    NOEUD *n;
    n = (NOEUD*) malloc(sizeof(NOEUD));
    if (!n)
        printf("\nPlus d'espace");
    else
    {

        elementAffecter(  n -> patient, e);

        n -> suivant = NULL;
        n -> precedent = NULL;
    }
    return n;
}
void noeudDetruire(NOEUD *n)
{

    elementDetruire(n -> patient);
    free(n);
}
/*current*/
LISTE* liste_ajouter(LISTE *l)
{
    NOEUD* n = NULL;
    PATIENT *e = NULL;
    int x, i;
    do {
        printf("donner le nombre des patients a ajouter : \n");
        scanf("%d", &x);
        if(x<=0) {
            printf("\votre choix doit etre strictement superieure à 0\n");
            printf("Cliquez Pour continuer SVP");
            getch();
            system("cls");
        }
    }
    while(x<=0);

    l->lg = 0;
    e = (PATIENT*) malloc(x*sizeof(PATIENT));
    n = (NOEUD*) malloc(x*sizeof(NOEUD));
    for (i = 0; i < x; i++)
    {
        printf("INFORMATIONS CONCERNANT PATIENT N %d\n",i);
        elementLire(e+i);
        (n+i)-> patient = e+i;
        (n+i) -> suivant = NULL;
        (n+i)-> precedent = NULL;
        if (i == 0)
        {
            l -> tete = (n+i);
            l -> queue = (n+i);
            l -> lg++;
        }
        else
        {
            l -> queue -> suivant = (n+i);
            (n+i) -> precedent = l -> queue;
            l->queue = (n+i);
            l -> lg++;
        }
    }
    return l;
}
int supprimer(LISTE *L, int pos)
{

    int i;
    int succee = 1;
    NOEUD* p, *q;

    if (estVide(L))
    {
        printf("\nListe vide");
        succee = 0;
    }
    else
    {

        if ((pos < 1) || (pos > L -> lg))
        {
            printf("\nPosition invalide");
            succee = 0;
        }
        else
        {
            if (L -> lg == 1) /* un seul element donc pos == 1*/
            {
                q = L -> tete;
                L -> tete = NULL;
                L -> queue = NULL;
            }
            else
            {
                if (pos == 1) /*suppression en t�te de liste*/
                {
                    q = L -> tete;
                    L -> tete = L -> tete -> suivant;
                    L -> tete -> precedent = NULL;
                }
                else
                {
                    if (pos == L -> lg)
                    {
                        q = L -> queue;
                        L -> queue = L -> queue -> precedent;
                        L -> queue -> suivant = NULL;
                    }
                    else
                    {
                        q = L -> tete;
                        for (i = 1; i < pos; i++)
                        {
                            p = q;
                            q = q -> suivant;
                        }
                        /*q d�signe l��l�ment de rang pos et p son
                        pr�d�cesseur*/

                        q -> suivant -> precedent = p;
                        p -> suivant = q -> suivant;
                    }
                }
            }
            noeudDetruire(q);
            (L -> lg) --;
        }
    }
    return succee;
}
//chercher un patientdans la liste doublement chain�e
NOEUD *chercher_chaine_double(char* critere,char* valeur, LISTE *L)
{
    NOEUD *p;
    int verif = 1;
    if (L == NULL)
    {
        return NULL;
    }
    else
    {
        p = L->tete;

        while (p != NULL)
        {
            if(strcmp(critere,"cin")==0)
            {
                verif = strcmp(p->patient->cin, valeur);
            }
            if(strcmp(critere,"nom")==0)
            {
                verif = strcmp(p->patient->nom, valeur);
            }
            if(strcmp(critere,"prenom")==0)
            {
                verif = strcmp(p->patient->prenom, valeur);
            }
            if(strcmp(critere,"etat")==0)
            {
                verif = strcmp(p->patient->etat, valeur);
            }

            if (verif == 0)
            {
                return p;
            }
            else
            {
                p = p->suivant;
            }
        }

    }
    return p;
}
// afficher la recherche
void affiche_recherche_double(NOEUD*p)
{
    if (p != NULL)
    {
        elementAfficher(p -> patient);
    }
    else
    {
        printf("ce patient n'existe pas dans notre liste\n");
    }
}


int supprimer_patient(char* cin,LISTE* L)
{
    NOEUD *p;
    if (L == NULL)
    {
        return 0;
    }
    else
    {
        p = L->tete;
        while (p != NULL && strcmp(p->patient->cin,cin))
        {
            p = p->suivant;
        }
        printf("HERE0\n");
        p->precedent->suivant = p->suivant;
        printf("HERE1\n");
        return 1;
    }
}

void printMap(LISTE *l)
{
    if(estVide(l)||(!l))
    {
        printf("La Liste est vide !");
    }
    else
    {

        NOEUD *p = (NOEUD*) malloc(sizeof(NOEUD));
        p = l->tete;
        int bizerte=0,tunis=0,ariana=0,sfax=0,jendouba=0,beja=0,tataouine=0,sousse=0,mounastir=0,mahdia=0,gabes=0,siliana=0,manouba=0,kasserine=0,sidiBouzid=0,kebili=0,tozeur=0,gafsa=0,benArous=0,zaghouan=0,nabeul=0,kairouan=0,medenine=0,kef=0,djerba=0;

        while(p!=NULL)
        {
            if(strcmp(p->patient->adr,"bizerte")==0)
            {
                bizerte++;
            }
            else if (strcmp(p->patient->adr,"tunis")==0)
            {
                tunis++;
            }
            else if (strcmp(p->patient->adr,"ariana")==0)
            {
                ariana++;
            }
            else if (strcmp(p->patient->adr,"sfax")==0)
            {
                sfax++;
            }
            else if (strcmp(p->patient->adr,"jendouba")==0)
            {
                jendouba++;
            }
            else if (strcmp(p->patient->adr,"beja")==0)
            {
                beja++;
            }
            else if (strcmp(p->patient->adr,"tataouine")==0)
            {
                tataouine++;
            }
            else if (strcmp(p->patient->adr,"sousse")==0)
            {
                sousse++;
            }
            else if (strcmp(p->patient->adr,"mounastir")==0)
            {
                mounastir++;
            }
            else if (strcmp(p->patient->adr,"mahdia")==0)
            {
                mahdia++;
            }
            else if (strcmp(p->patient->adr,"gabes")==0)
            {
                gabes++;
            }
            else if (strcmp(p->patient->adr,"siliana")==0)
            {
                siliana++;
            }
            else if (strcmp(p->patient->adr,"manouba")==0)
            {
                manouba++;
            }
            else if (strcmp(p->patient->adr,"kasserine")==0)
            {
                kasserine++;
            }
            else if (strcmp(p->patient->adr,"sidi bouzid")==0)
            {
                sidiBouzid++;
            }
            else if (strcmp(p->patient->adr,"kebili")==0)
            {
                kebili++;
            }
            else if (strcmp(p->patient->adr,"tozeur")==0)
            {
                tozeur++;
            }
            else if (strcmp(p->patient->adr,"gafsa")==0)
            {
                gafsa++;
            }
            else if (strcmp(p->patient->adr,"ben arous")==0)
            {
                benArous++;
            }
            else if (strcmp(p->patient->adr,"zaghouan")==0)
            {
                zaghouan++;
            }
            else if (strcmp(p->patient->adr,"nabeul")==0)
            {
                nabeul++;
            }
            else if (strcmp(p->patient->adr,"kairouan")==0)
            {
                kairouan++;
            }
            else if (strcmp(p->patient->adr,"medenine")==0)
            {
                medenine++;
            }
            else if (strcmp(p->patient->adr,"kef")==0)
            {
                kef++;
            }
            else
            {
                djerba++;
            }


            p = p->suivant;
        }
        //printf("\n                                                '.-----::                                          \n                                           ..---..    ':+/-----.'                                  \n                                     '-:-:-.'         ---+'   -+/-                                 \n                                    ::'.       bizerte       ..+/                  .--              \n                                 '-/.  '..       %d         .'   /.             `:-` :.             \n                            ':-..-''.     .         '''''-'Ariana'--.         `--`   .:             \n                            .:      -      .'     .'''    '..    ''.:/    --.--`     :-             \n                          .-:.      ''      '.' '..'Tunis  -.'.++/.     :- Nabeul ':.               \n                         /-'         .'       ''   ''''  %d  .'''-'---:-          .:'               \n                       ':- Jandouba   .   Beja         '.  ....'Ben A-'         :-                  \n                   .----'             ''               ...''''.'   '.         .:                   \n                  '/..'               .'              .''      .'  .         -:                    \n                   '.../   ''''''''..'-      ''''''''..         '...    '.---.                     \n                      '+'..'  '''' '.' ..''..'   ''  .'            ..'./.''                        \n                     '/'             .            ''.'  Zaghouan  '' /'                            \n                     .:              ''   Seliana  ..''           ''. ':                            \n                     -.               '.            ''.       ''.'   -.                            \n                     /'    Kef         '.'          '..'.''' .'-.     '/                            \n                    '/                  .'       ''''      '''  '-      -:                          \n                    --                '.'       .'              .'       -:                         \n                    :-               '.         .              .'Sousse    .:.                      \n                    .:       .'.'''  .'         -'             .'         '.'::-.                   \n                     .:'''' '.   ''''-'    ..''.'               .'       '.Mestir.-.'               \n                      +-' '''        '.'''  '.      Kairouan    .'     '.'     ''./'               \n                      /'                ''.' '.'                '...'''..'     ''./'               \n                     '/                    '-''.'               .    '''''''''.'' ./               \n                     .:                   '''   .              '.            '    /.               \n                     .:     Kasserine      .'     .'             .'  Mahdia        :-               \n                      :.                '.'      '.''          '.        ''''      -:.             \n                      '/.                ''.        '''''       -'     '.' '''''  '-:'             \n                     ':.                   -            '''.  ''''''.'''       '.'/.               \n                     /'                 ''.'                -.'                  .:                \n                     +                '.''                 '.                   .:                 \n                    .:               '.   Sidi Bouzid     '.   Sfax            .:'                 \n                    .-             '.'                   '.                  ':-      .--'         \n                    -+'        ''...'                   .'                  '/'      :/-:'         \n                    o' '''''''''   ''''''''            '.                 './'      ./-'           \n                  .:-                      -           '.'''            '/-.'                      \n               .-/-                        '.'             '.'       .---'                         \n           '---.'-'       Gafsa              '.'         '''.      ':-                             \n          '/'   ..                              '.    ''''      '---'                              \n          --   ..                                .'''.'      ':-.                                  \n      '----      '.'                      '''''''.'''..''   :-                                     \n    ':-'           ''..              '.''''.'           '..+-                                      \n   '/'                '.'''''-''''''.'     .               .:                                      \n   -:                       '.            '.                /'                                     \n   --      Tozeur           .'              -                ./'           -:..---.                 \n   :.                   '.'                .'                '/.          :'Djerba:'        \n   '/                 '.'                   .'   Gabes        -:'         :'      :+               \n    /'             '.'                       '.'                 -:-'    '-+/::.-:.                \n     /'          '.'                           '..                 '-/---.      :---               \n     '/.      '..'                                -                '.     '/   .+  -:              \n       :-  ''.'                                  .'               '.      '/-__-    +              \n        /.''                                      .'           ''.'         '      '/              \n        :.                  Kebeli                 '.'      ''.'  Medinine          /              \n        -.                                           '-'''.'          '''''         :.             \n        ':-.'                                          ''.'      ''''.'   '.'        ---.---..'    \n           '----.'                                       '.  '.'''          '''''         ''':-    \n               ''/.                                      ..'''                  ''.         '/     \n                  -:                                      .'                      '.        :.     \n                   ./'                                    .'                       '.       /'     \n                    ':'                             ''   '.                        '.       /'     \n                     ./                          '.'''.' .'                        '.       /'     \n                     '/              '''''''''''''     '.'-'                        .'      /'     \n                      /'     '''''''''''''                ''                         '.'    --     \n                      ::.'''''                                                         '.'   ./    \n                       .--.                                                              -    :-   \n                         '.:-'                                                         '.' '.:-    \n                            '--.                                                      .-.--.'      \n                              '.--.                Tataouine                        '.-:.'          \n                                 '.:.'                                         '.--.''             \n                                    '--'                                      .:''                 \n                                      .:                                    '-:                    \n                                      '+                                  ':-'                     \n                                       :.                                -:'                       \n                                        +                              ':-                         \n                                        :.                       '---.-:'                          \n                                        .:                      ':.  ''                            \n                                         /'                    .:                                  \n                                         .:                   .:                                   \n                                         '/                  '/'                                   \n                                          :.                  /.                                   \n                                          '/                  '/'                                  \n                                           /'                  .:                                  \n                                           .:                   :.                                 \n                                            /                    /'                                \n                                            --                   --                                \n                                             +                   '/                                \n                                             :.                  -:                                \n                                             .:                 .:                                 \n                                              +'               -:                                  \n                                              .:              :-                                   \n                                              '/            .:'                                    \n                                               :.          -:                                      \n                                               '/        ':.                                       \n                                                :.   .---:                                         \n                                                ./---.'                                            \n                                                                                                   \n",bizerte,tunis);
        //printf("\n                                                '.-----::                                          \n                                           ..---..    ':+/-----.'                                  \n                                     '-:-:-.'         ---+'   -+/-                                 \n                                    ::'.       bizerte       ..+/                  .--             \n                                 '-/.  '..       %d         .'   /.             `:-` :.            \n                            ':-..-''.     .         '''''-'Ariana'--.         `--`   .:            \n                            .:      -      .'     .'''    '.. %d ''.:/    --.--`     :-            \n                          .-:.      ''      '.' '..'Tunis  -.'.++/.     :- Nabeul ':.              \n                         /-'         .'       ''   ''''  %d  .'''-'---:-   %d     .:'              \n                       ':- Jandouba   .   Beja         '.  ....'Ben A-'         :-                 \n                   .----'     %d      ''     %d        ...''''.' %d '.         .:                  \n                  '/..'               .'              .''      .'  .         -:                    \n                   '.../   ''''''''..'-      ''''''''..         '...    '.---.                     \n                      '+'..'  '''' '.' ..''..'   ''  .'            ..'./.''                        \n                     '/'             .            ''.'  Zaghouan  '' /'                            \n                     .:              ''   Seliana  ..''    %d     ''. ':                           \n                     -.               '.     %d     ''.       ''.'   -.                            \n                     /'    Kef         '.'          '..'.''' .'-.     '/                           \n                    '/      %d          .'       ''''      '''  '-      -:                         \n                    --                '.'       .'              .'       -:                        \n                    :-               '.         .              .'Sousse    .:.                     \n                    .:       .'.'''  .'         -'             .'   %d    '.'::-.                  \n                     .:'''' '.   ''''-'    ..''.'               .'       '.Mestir.-.'              \n                      +-' '''        '.'''  '.      Kairouan    .'     '.'  %d   ''./'             \n                      /'                ''.' '.'       %d         '...'''..'     ''./'             \n                     '/                    '-''.'               .    '''''''''.'' ./               \n                     .:                   '''   .              '.            '    /.               \n                     .:     Kasserine      .'     .'             .'  Mahdia  %d    :-              \n                      :.       %d       '.'      '.''          '.        ''''      -:.             \n                      '/.                ''.        '''''       -'     '.' '''''  '-:'             \n                     ':.                   -            '''.  ''''''.'''       '.'/.               \n                     /'                 ''.'                -.'                  .:                \n                     +                '.''                 '.                   .:                 \n                    .:               '.   Sidi Bouzid     '.   Sfax            .:'                 \n                    .-             '.'        %d         '.     %d           ':-      .--'         \n                    -+'        ''...'                   .'                  '/'      :/-:'         \n                    o' '''''''''   ''''''''            '.                 './'      ./-'           \n                  .:-                      -           '.'''            '/-.'                      \n               .-/-                        '.'             '.'       .---'                         \n           '---.'-'       Gafsa              '.'         '''.      ':-                             \n          '/'   ..          %d                  '.    ''''      '---'                              \n          --   ..                                .'''.'      ':-.                                  \n      '----      '.'                      '''''''.'''..''   :-                                     \n    ':-'           ''..              '.''''.'           '..+-                                      \n   '/'                '.'''''-''''''.'     .               .:                                      \n   -:                       '.            '.                /'                                     \n   --      Tozeur           .'              -                ./'          -:..---.                 \n   :.        %d          '.'                .'                '/.         :'Djerba:'               \n   '/                 '.'                   .'   Gabes        -:'         :'  %d  :+               \n    /'             '.'                       '.'    %d           -:-'    '-+/::.-:.                \n     /'          '.'                           '..                 '-/---.      :---               \n     '/.      '..'                                -                '.     '/   .+  -:              \n       :-  ''.'                                  .'               '.      '/-__-    +              \n        /.''                                      .'           ''.'         '      '/              \n        :.                  Kebeli                 '.'      ''.'  Medinine     %d   /              \n        -.                     %d                    '-'''.'          '''''         :.             \n        ':-.'                                          ''.'      ''''.'   '.'        ---.---..'    \n           '----.'                                       '.  '.'''          '''''         ''':-    \n               ''/.                                      ..'''                  ''.         '/     \n                  -:                                      .'                      '.        :.     \n                   ./'                                    .'                       '.       /'     \n                    ':'                             ''   '.                        '.       /'     \n                     ./                          '.'''.' .'                        '.       /'     \n                     '/              '''''''''''''     '.'-'                        .'      /'     \n                      /'     '''''''''''''                ''                         '.'    --     \n                      ::.'''''                                                         '.'   ./    \n                       .--.                                                              -    :-   \n                         '.:-'                                                         '.' '.:-    \n                            '--.                                                      .-.--.'      \n                              '.--.                Tataouine                        '.-:.'         \n                                 '.:.'                 %d                        '.--.''           \n                                    '--'                                      .:''                 \n                                      .:                                    '-:                    \n                                      '+                                  ':-'                     \n                                       :.                                -:'                       \n                                        +                              ':-                         \n                                        :.                       '---.-:'                          \n                                        .:                      ':.  ''                            \n                                         /'                    .:                                  \n                                         .:                   .:                                   \n                                         '/                  '/'                                   \n                                          :.                  /.                                   \n                                          '/                  '/'                                  \n                                           /'                  .:                                  \n                                           .:                   :.                                 \n                                            /                    /'                                \n                                            --                   --                                \n                                             +                   '/                                \n                                             :.                  -:                                \n                                             .:                 .:                                 \n                                              +'               -:                                  \n                                              .:              :-                                   \n                                              '/            .:'                                    \n                                               :.          -:                                      \n                                               '/        ':.                                       \n                                                :.   .---:                                         \n                                                ./---.'                                            \n                                                                                                   ",bizerte,ariana,tunis,nabeul,jendouba,beja,benArous,zaghouan,siliana,kef,sousse,mounastir,kairouan,mahdia,kasserine,sidiBouzid,sfax,gafsa,tozeur,djerba,gabes,medenine,kebili,tataouine);
        printf("\n                                                '.-----::                /''''''''''''':                          \n                                           ..---..    ':+/-----.'       / Manouba : %d :                          \n                                     '-:-:-.'         ---+'   -+/-     /'''''''''''''''.                         \n                                    ::'.       bizerte       ..+/     /             .--             \n                                 '-/.  '..       %d         .'   /.  /           `:-` :.            \n                            ':-..-''.     .         '''''-'Ariana'--.         `--`   .:            \n                            .:      -      .'     .'''    '.. %d ''.:/    --.--`     :-            \n                          .-:.      ''      '.' '..'Tunis  -.'.++/.     :- Nabeul ':.              \n                         /-'         .'       ''   ''''  %d  .'''-'---:-   %d     .:'              \n                       ':- Jandouba   .   Beja         '.  ....'Ben A-'         :-                 \n                   .----'     %d      ''     %d        ...''''.' %d '.         .:                  \n                  '/..'               .'              .''      .'  .         -:                    \n                   '.../   ''''''''..'-      ''''''''..         '...    '.---.                     \n                      '+'..'  '''' '.' ..''..'   ''  .'            ..'./.''                        \n                     '/'             .            ''.'  Zaghouan  '' /'                            \n                     .:              ''   Seliana  ..''    %d     ''. ':                           \n                     -.               '.     %d     ''.       ''.'   -.                            \n                     /'    Kef         '.'          '..'.''' .'-.     '/                           \n                    '/      %d          .'       ''''      '''  '-      -:                         \n                    --                '.'       .'              .'       -:                        \n                    :-               '.         .              .'Sousse    .:.                     \n                    .:       .'.'''  .'         -'             .'   %d    '.'::-.                  \n                     .:'''' '.   ''''-'    ..''.'               .'       '.Mestir.-.'              \n                      +-' '''        '.'''  '.      Kairouan    .'     '.'  %d   ''./'             \n                      /'                ''.' '.'       %d         '...'''..'     ''./'             \n                     '/                    '-''.'               .    '''''''''.'' ./               \n                     .:                   '''   .              '.            '    /.               \n                     .:     Kasserine      .'     .'             .'  Mahdia  %d    :-              \n                      :.       %d       '.'      '.''          '.        ''''      -:.             \n                      '/.                ''.        '''''       -'     '.' '''''  '-:'             \n                     ':.                   -            '''.  ''''''.'''       '.'/.               \n                     /'                 ''.'                -.'                  .:                \n                     +                '.''                 '.                   .:                 \n                    .:               '.   Sidi Bouzid     '.   Sfax            .:'                 \n                    .-             '.'        %d         '.     %d           ':-      .--'         \n                    -+'        ''...'                   .'                  '/'      :/-:'         \n                    o' '''''''''   ''''''''            '.                 './'      ./-'           \n                  .:-                      -           '.'''            '/-.'                      \n               .-/-                        '.'             '.'       .---'                         \n           '---.'-'       Gafsa              '.'         '''.      ':-                             \n          '/'   ..          %d                  '.    ''''      '---'                              \n          --   ..                                .'''.'      ':-.                                  \n      '----      '.'                      '''''''.'''..''   :-                                     \n    ':-'           ''..              '.''''.'           '..+-                                      \n   '/'                '.'''''-''''''.'     .               .:                                      \n   -:                       '.            '.                /'                                     \n   --      Tozeur           .'              -                ./'          -:..---.                 \n   :.        %d          '.'                .'                '/.         :'Djerba:'               \n   '/                 '.'                   .'   Gabes        -:'         :'  %d  :+               \n    /'             '.'                       '.'    %d           -:-'    '-+/::.-:.                \n     /'          '.'                           '..                 '-/---.      :---               \n     '/.      '..'                                -                '.     '/   .+  -:              \n       :-  ''.'                                  .'               '.      '/-__-    +              \n        /.''                                      .'           ''.'         '      '/              \n        :.                  Kebeli                 '.'      ''.'  Medinine     %d   /              \n        -.                     %d                    '-'''.'          '''''         :.             \n        ':-.'                                          ''.'      ''''.'   '.'        ---.---..'    \n           '----.'                                       '.  '.'''          '''''         ''':-    \n               ''/.                                      ..'''                  ''.         '/     \n                  -:                                      .'                      '.        :.     \n                   ./'                                    .'                       '.       /'     \n                    ':'                             ''   '.                        '.       /'     \n                     ./                          '.'''.' .'                        '.       /'     \n                     '/              '''''''''''''     '.'-'                        .'      /'     \n                      /'     '''''''''''''                ''                         '.'    --     \n                      ::.'''''                                                         '.'   ./    \n                       .--.                                                              -    :-   \n                         '.:-'                                                         '.' '.:-    \n                            '--.                                                      .-.--.'      \n                              '.--.                Tataouine                        '.-:.'         \n                                 '.:.'                 %d                        '.--.''           \n                                    '--'                                      .:''                 \n                                      .:                                    '-:                    \n                                      '+                                  ':-'                     \n                                       :.                                -:'                       \n                                        +                              ':-                         \n                                        :.                       '---.-:'                          \n                                        .:                      ':.  ''                            \n                                         /'                    .:                                  \n                                         .:                   .:                                   \n                                         '/                  '/'                                   \n                                          :.                  /.                                   \n                                          '/                  '/'                                  \n                                           /'                  .:                                  \n                                           .:                   :.                                 \n                                            /                    /'                                \n                                            --                   --                                \n                                             +                   '/                                \n                                             :.                  -:                                \n                                             .:                 .:                                 \n                                              +'               -:                                  \n                                              .:              :-                                   \n                                              '/            .:'                                    \n                                               :.          -:                                      \n                                               '/        ':.                                       \n                                                :.   .---:                                         \n                                                ./---.'                                            \n                                                                                                   \n",manouba,bizerte,ariana,tunis,nabeul,jendouba,beja,benArous,zaghouan,siliana,kef,sousse,mounastir,kairouan,mahdia,kasserine,sidiBouzid,sfax,gafsa,tozeur,djerba,gabes,medenine,kebili,tataouine);
    }
}

