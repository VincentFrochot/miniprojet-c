/*
  * Provides:
  * - 
  * Version: ...
  * Author: Simon Jornet / Vincent Frochot
  * Copyright: 2012 - Simon Jornet, Vincent Frochot
*/

#include "file.h"

/*
	La fonction enfiler() alloue dynamique de la mémoire, il est donc nécessaire de la désallouer dans défiler().
	La file est donc observable : on peut accéder à l'élément de tete de file.
*/



/*
	Pointeurs de fonctions copier() et liberer() afin que chaque maillon puisse stocker le type de donnees de son choix.
*/
typedef struct maillon 
{
	void * valeur;
	struct maillon * suivant;
} maillon;


static int file_vide ( file * f ) 
{
	if ( NULL == (*f).tete )
		return 1;
	return 0;
}

/* file_lieu a deja ete alloue dynamiquement, il ne reste qu'a initialiser ses variables */
int file_creer (	file * file_lieu,
					void ( * copier ) ( void * valeur , void ** lieu ) ,
					void ( * liberer ) ( void ** lieu ) ) 
{
	(*file_lieu).copier		= copier;
	(*file_lieu).liberer	= liberer;
	(*file_lieu).tete 		= NULL;
	(*file_lieu).queue 		= NULL;
	return 0;
}

void file_detruire ( file * f )
{
	while( !file_vide(f) )
		defiler(f);
	free(f);
}
/*
void enfiler_file(file * source, file * dest)
{
	while(!file_vide(source)) {
		
		defiler(source);
	}
}
*/
int enfiler( file * f, void * value ) 
{
	maillon * m	= (maillon *) malloc(sizeof(maillon));
	if ( NULL == m )
		return 0;
	(*f).copier( value, (*m).valeur );
	(*m).suivant 	= (*f).tete;
	(*f).queue		= m;
	if ( file_vide( f ) )
		(*f).tete	= m;
	return 1;
}

void defiler(file * f)
{
	if( file_vide(f) )
		return;
	(*f).tete = ( *(*f).tete ).suivant;
	(*f).liberer( (void **)&((*f).tete) );
	if ( file_vide(f) )
		(*f).queue = NULL;
}

void * tete ( file * f )
{
	return (*f).tete;
}

void file_afficher ( file * f )
{
	
}