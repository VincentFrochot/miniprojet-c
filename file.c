/*
  * Provides:
  * - 
  * Version: ...
  * Author: Simon Jornet / Vincent Frochot
  * Copyright: 2012 - Simon Jornet, Vincent Frochot
*/

#include "file.h"


typedef struct maillon {
	void * valeur;
	struct maillon * suivant;
	void (* copier) ( void * valeur , void ** lieu );
	void (* liberer) (void ** lieu);
} maillon;



int file_creer ( file * file_lieu,
                        void ( * copier ) ( void * valeur , void ** lieu ) ,
                        void ( * liberer ) ( void ** lieu ) )
{
/*	file_lieu = malloc();
	if( sizeof( *(valeur) ) )
		file_lieu.copier = copier_int();
	
	file_lieu.liberer = free_();
*/
}

void copier ( void * valeur , void ** lieu )
{
/*    *lieu = malloc(sizeof(*valeur));
	(*(*lieu)) = *valeur;
*/
}

void liberer ( void ** lieu )
{
    free(*lieu);
}
