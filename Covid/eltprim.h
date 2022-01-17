
#ifndef _ELTPRIM_H
#define _ELTPRIM_H

#include "ELTSDD.H"
#include "lstpatient.h"
/* Lecture d'un �l�ment*/
void elementLire(PATIENT *);
/* Affichage d'un �l�ment*/
void elementAfficher(PATIENT*);
/* Affectation du 2eme argument dans le 1er qui est donc modifi� et pass� par
adresse */
void elementAffecter(PATIENT*, PATIENT*);
/* Copie du contenu du deuxi�me argument dans le premier, les deux
arguments ont des adresses diff�rentes (duplication)*/
void elementCopier(PATIENT *,PATIENT*) ;
/* Comparaison des arguments retourne un entier 0, < 0 ou > 0 la
"diff�rence" (e1-e2) */
int elementComparer(PATIENT*,PATIENT*);
/* Cr�ation d'un �l�ment*/
PATIENT* patientCreer(void) ;
/* Lib�ration de m�moire */
void elementDetruire(PATIENT*);
#endif

