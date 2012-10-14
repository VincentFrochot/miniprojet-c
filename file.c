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
/*	(*file_lieu).copier 	= copier;
	(*file_lieu).liberer 	= liberer;
*/	return 0;
}

void copier ( void * valeur , void ** lieu )
{
/*    *lieu 			= malloc(sizeof(*valeur));
	*((void*)lieu) 	= *(valeur);
/*	
void * a = ....;
....
 //  (int*)a donne une adresse dont le type est int *
* (int*)a = 12345;	
	*/
}

void liberer ( void ** lieu )
{
    free(*lieu);
}