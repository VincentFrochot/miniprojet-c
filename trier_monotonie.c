#include <stdio.h>
#include <stdlib.h>
#include "trier_monotonie.h"

/*
  * Provides:
  * - 
  * Version: ...
  * Author: Simon Jornet / Vincent Frochot
  * Copyright: 2012 - Simon Jornet, Vincent Frochot
 */

/*
file * fusion (file * f1, file * f2)
{
	
} 
 
file ** division ()
{
	
}
*/


char * fusion (char tab1[], char tab2[])
{
    int i, taille1 = 0, taille2 =0;
    char * tabNew = (char *) malloc( (taille1+taille2) * sizeof(char) );    
	
    /* Calcul des tailles des tableaux */
    for (i=0; tab1[i] != '\0'; i++)
        taille1++;
    for (i=0; tab2[i] != '\0'; i++)
        taille2++;
    
    /* Tri des tableaux et copie dans le nouveau tableau trié */
    if (tab1[0] > tab2[0])
    {
        for (i=0; i < taille1; i++)
            tabNew[i] = tab2[i];
        for (i=taille2; i < taille1+taille2; i++)
            tabNew[i] = tab1[i];
    }
    else
    {
        for (i=0; i < taille2; i++)
            tabNew[i] = tab1[i];
        for (i=taille1; i < taille1+taille2; i++)
            tabNew[i] = tab2[i];
    }

    return tabNew;
}

char * decoupe (char tab[], int longueur)
{
    int i;
    void * res;
    char tabTrie [longueur];


    if (longueur == 1) /* File à un seul élément (aucun tri) */
        return tab;
    
    else
    {
        if (longueur%2 == 0) /* Nombre d'éléments pair */
            tabTrie = fusion(decoupe(&(tab[0]),longueur/2), decoupe(&(tab[longueur/2]),longueur/2));
        else /* Nombre d'éléments impair */
            tabTrie = fusion(decoupe(&tab[0],longueur/2+1), decoupe(&(tab[longueur/2+1]),longueur/2));
    }
    
    /* Test */
    for (i=0; i < longueur; i++)
        printf("%c", tabTrie[i]);
    
    return tabTrie;
}
