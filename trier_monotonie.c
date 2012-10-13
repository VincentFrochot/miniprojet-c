/*
  * Provides:
  * - 
  * Version: ...
  * Author: Simon Jornet / Vincent Frochot
  * Copyright: 2012 - Simon Jornet, Vincent Frochot
 */

#include "trier_monotonie.h"

void * tri_monotonie (void *fileSource, void *couple)
{
    /* DECOUPAGE */
    int i;
    int tailleFile = 0;

    while (*fileSource.valeur != NULL)
    {
        i++;
    }
    tailleFile = i;

    if (tailleFile == 1) /* File à un seul élément (aucun tri) */
    {
        *couple = *fileSource;
    }
    else
    {
        if (tailleFile%2 == 0) /* Nombre d'éléments pair */
        {
            *couple = {trier_monotonie (/* Nouvelle file de taille tailleFile/2 */, /* Nouveau couple */), trier_monotonie (/* Nouvelle file de taille tailleFile/2 */, /* Nouveau couple */)};
        }
        else
        {
            *couple = {trier_monotonie (/* Nouvelle file de taille tailleFile/2+1 */, /* Nouveau couple */), trier_monotonie (/* Nouvelle file de taille tailleFile/2 */, /* Nouveau couple */)};
        }
    }

    /* FUSION */
    *couple
}