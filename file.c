/*
  * Provides:
  * - 
  * Version: ...
  * Author: Simon Jornet / Vincent Frochot
  * Copyright: 2012 - Simon Jornet, Vincent Frochot
*/

#include "file.h"


typedef struct maillon 
{
	void * valeur;
	struct maillon * suivant;
	void ( * copier ) ( void * valeur , void ** lieu );
	void ( * liberer ) ( void ** lieu );
} maillon;


int file_creer (	file * file_lieu,
					void ( * copier ) ( void * valeur , void ** lieu ) ,
					void ( * liberer ) ( void ** lieu ) ) 
{
	maillon * m 	= (maillon *) malloc(sizeof(maillon));
	if (NULL == m)
		return 1;
	(*m).valeur		= NULL;
	(*m).suivant 	= NULL;
	(*m).copier		= copier;
	(*m).liberer	= liberer;
	(*file_lieu) 	= (file *)m;
	return 0;
}

void file_detruire ( file * f)
{
	while(!file_vide(f))
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
void enfiler(file * f, void * value) 
{
	maillon * m	= (maillon *) malloc(sizeof(maillon));
	if (NULL == m)
		return ;
	(*(maillon *)f).copier(value, (*m).valeur);
	(*m).suivant 	= (maillon *)f;
	(*f)			= m;
}

extern void * tete (file * f)
{
	maillon * temp = (maillon *)f;
	if(file_vide(f))
		return NULL;
	while (NULL != (*temp).suivant)
	{
		temp = (*temp).suivant;
	}
	return temp;
}


/* Libère la mémoire de tête de file */
void defiler(file * f)
{
	maillon * temp, * nouvelle_tete;
	if(file_vide(f))
		return;
	/* marche jusqu'en tête de file... */	
	while ( NULL != (*temp).suivant )
	{
		nouvelle_tete	= temp;
		temp			= (*temp).suivant;
	}
	(*nouvelle_tete).suivant = NULL;
	(*temp).liberer((*temp).valeur);
	free(temp);
}


int file_vide (file * f) 
{
	if ( NULL == (*(maillon *)f).valeur )
		return 1;
	return 0;
}