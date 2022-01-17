#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char T_etat[25][30]= {{"bizerte"},{"tunis"},{"ariana"},{"sfax"},{"jendouba"},{"beja"},{"tataouine"},
    {"sousse"},{" mounastir"},{"mahdia"},{"gabes"},{"siliana "},{"manouba"},
    {"kasserine"},{"sidi bouzid"},{"kebili"},{"tozeur"},{"gafsa"},{"ben arous"},{"zaghouan"},{"nabeul"},{"kairouan"},{"medenine"},{"kef"}
};
int isCIN(char cin[])
{
    int i;
    if(strlen(cin)>8)
    {
        return 0;
    }
    else
    {
        for(i = 0; i<8; i++)
        {
            if(!isdigit(cin[i])) return 0;
        }
    }
    return 1; //success
}

int isCarac(char chaine[])
{
    int i;

    for(i = 0; i<strlen(chaine); i++)
    {
        if(isdigit(chaine[i])) return 0;
    }

    return 1; //success
}



