/*
  * Provides:
  * - 
  * Version: ...
  * Author: Simon Jornet / Vincent Frochot
  * Copyright: 2012 - Simon Jornet, Vincent Frochot
 */

/* Création d’une file générique.
        - file_lieu : endroit pour indiquer l’emplacement de la nouvelle file
        - copier sert à copier une valeur de type inconnu
        (utilisation de void * pour cela, alloue de la mémoire si nécessaire)
        - libérer sert à détruire une valeur créée avec copier
        (désalloue de la mémoire le cas échéant).
        * retourne 0 en cas de succès sinon un code d’erreur.
*/

#ifndef FILE_H
#define FILE_H

#include <stdlib.h>

typedef void * file;

extern int file_creer ( file * file_lieu,
                        void ( * copier ) ( void * valeur , void ** lieu ) ,
                        void ( * liberer ) ( void ** lieu ) ) ;

extern void copier ( void * valeur , void ** lieu ) ;
extern void liberer ( void ** lieu ) ;

#endif