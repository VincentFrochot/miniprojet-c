/*
  * Provides:
  * - 
  * Version: ...
  * Author: Simon Jornet / Vincent Frochot
  * Copyright: 2012 - Simon Jornet, Vincent Frochot
 */


#ifndef FILE_H
#define FILE_H

#include <stdlib.h>

typedef struct file {
	struct maillon * tete;
	struct maillon * queue;
	
} file;

/* Création d’une file générique.
        - file_lieu : endroit pour indiquer l’emplacement de la nouvelle file
        - copier sert à copier une valeur de type inconnu
        (utilisation de void * pour cela, alloue de la mémoire si nécessaire)
        - libérer sert à détruire une valeur créée avec copier
        (désalloue de la mémoire le cas échéant).
        * retourne 0 en cas de succès sinon un code d’erreur.
*/
extern int file_creer (	file *,
					void ( * copier ) ( void *, void ** ) ,
					void ( * liberer ) ( void ** ) ) ;
extern void file_detruire (file *) ;
extern void enfiler_file(file *, file *) ;
extern int file_vide (file *) ;
extern void * tete (file *);
extern void enfiler(file *, void *) ;
extern void defiler(file *) ;


#endif