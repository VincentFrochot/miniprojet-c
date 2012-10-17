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


/* 
tete et queue permettent d'enfiler et défiler en temps constant.
Pointeurs de fonctions copier() et liberer() afin que chaque file puisse stocker le type de donnees de son choix (ainsi il est nécessaire de créer une structure file.
*/
typedef struct file {
	struct maillon * tete;
	struct maillon * queue;
	void ( * copier ) ( void * valeur , void ** lieu );
	void ( * liberer ) ( void ** lieu );	
} file;


/* Création d’une file générique.
        - 1 : endroit pour indiquer l’emplacement de la nouvelle file
        - copier sert à copier une valeur de type inconnu
        (utilisation de void * pour cela, alloue de la mémoire si nécessaire)
        - libérer sert à détruire une valeur créée avec copier
        (désalloue de la mémoire le cas échéant).
        * retourne 0 en cas de succès sinon un code d’erreur.
*/
extern int file_creer (	file *,
					void ( * copier ) ( void *, void ** ) ,
					void ( * liberer ) ( void ** ) ) ;

/* Supprime la file et libere la memoire allouee.
*/
extern void file_detruire ( file * ) ;

/* Concatene deux files.
*/
extern void enfiler_file( file *, file * ) ;

/* Retourne un pointeur sur l'element de tete.
*/
extern void * tete ( file * ) ;

/* Alloue de la place pour le nouvel element a inserer et lui attribue une valeur.
*/
extern int enfiler( file *, void * ) ;

/* Supprime la tete de file et libere la memoire allouee.
*/
extern void defiler( file * ) ;

/* Affiche une file
*/
extern void file_afficher ( file * ) ;

#endif