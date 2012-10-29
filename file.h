/*
  * Provides:
  * - 
  * Version: ...
  * Author: Vincent Frochot / Simon Jornet
  * Copyright: 2012 - Vincent Frochot, Simon Jornet
 */


#ifndef FILE_H
#define FILE_H

#include <stdlib.h>


/* 

tete et queue permettent d'enfiler et défiler en temps constant.
Pointeurs de fonctions copier() et liberer() afin que chaque file puisse stocker le type de donnees de son choix (ainsi il est nécessaire de créer une structure file.
*/

typedef struct file file;

/* Création d’une file générique.
        - 1 : endroit pour indiquer l’emplacement de la nouvelle file
        - copier sert à copier une valeur de type inconnu
        (utilisation de void * pour cela, alloue de la mémoire si nécessaire)
        - libérer sert à détruire une valeur créée avec copier
        (désalloue de la mémoire le cas échéant).
        * retourne 0 en cas de succès sinon un code d’erreur.
*/
extern int file_creer (	file *,
					void ( * copier ) ( const void *, void ** ) ,
					void ( * liberer ) ( void ** ) ) ;

/* 	Supprime la file et libere la memoire allouee.
*/
extern void file_detruire ( file * ) ;

/* 	Concatene deux files et detruit source
*/
extern void enfiler_file( file * source, file * dest ) ;

/*  Retourne un pointeur sur l'element de queue.
*/
extern void * queue ( const file * ) ;

/* 	Retourne un pointeur sur l'element de tete.
*/
extern void * tete ( const file * ) ;

/* 	Alloue de la place pour le nouvel element a inserer en tete de file et lui attribue une valeur.
*/
extern int enfiler( file *, void * ) ;

/* 	Detruit l'element de tete en un temps constant
*/
extern void defiler( file * ) ;

/*  Alloue de la place pour le nouvel element a inserer en queue de file et lui attribue une valeur.
*/
extern int empiler( file *, void * ) ;

/*  Detruit l'element de queue en un temps lineaire 
*/
extern void depiler( file * ) ;

/* 	Affiche une file de char
*/
extern void file_char_afficher ( const file * ) ;

/*  Affiche une file de string
*/
extern void file_string_afficher ( const file * ) ;

/*	1 si file est vide, 0 sinon.
*/
extern int file_vide ( const file * ) ;

/*	Renvoie le nb d'element de la file.
*/
extern unsigned file_taille ( const file * ) ;

/*  
*/
extern int string_file_comparer_elements( const file *, const file *, unsigned, unsigned, int ( * comparatrice ) ( const char *, const char * ) ) ;

#endif