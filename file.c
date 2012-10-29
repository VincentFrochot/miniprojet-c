/*
  * Provides:
  * - 
  * Version: ...
  * Author: Vincent Frochot / Simon Jornet
  * Copyright: 2012 - Vincent Frochot, Simon Jornet
*/
#include <stdio.h>
#include <string.h>
#include "file.h"


	/* dev sous mac, windows et linux */

/*
	
*/
typedef struct maillon 
{
	void * valeur;
	struct maillon * precedant;
} maillon;


/*
	Une file contient 
		- des pointeurs de fonctions vers copier() et liberer() afin de pouvoir stocker le type de donnees de son choix.
		- des pointeurs vers sa tete et sa queue, ce qui permet d'avoir ses operation d'enfilage et defilage en temps constant.
	Cette file est "observable" : une fonction permet d'obtenir la valeur contenue dans la tete de file et le defilage ne renvoie rien.
*/
typedef struct file {
	maillon * tete;
	maillon * queue;
	void ( * copier ) ( const void * valeur , void ** lieu );
	void ( * liberer ) ( void ** lieu );
} File ;


/*
	La fonction enfiler() alloue dynamiquement de la mémoire, il est donc nécessaire de la désallouer dans défiler().
	La file est donc observable : on peut accéder à l'élément de tete de file.
*/


int file_creer (	file * file_lieu,
					void ( * copier ) ( const void * valeur , void ** lieu ) ,
					void ( * liberer ) ( void ** lieu ) )
{
	*(File **)file_lieu	= (File *)malloc( sizeof( File ) );

	if ( NULL == copier ) 
	{
		fprintf(stderr, "L'adresse de la fonction copier() a ete mal passee.");
		return 1;
	}
	if ( NULL == liberer )
	{
		fprintf(stderr, "L'adresse de la fonction liberer() a ete mal passee.");
		return 2;	
	}
	if ( NULL == file_lieu )
	{
		fprintf(stderr, "Le pointeur sur la file n'a pas ete alloue. Procedez ainsi : file * f = malloc( sizeof( file * ) );");
		return 3;
	}

	( *( *(File**)file_lieu ) ).copier	= copier;
	( *( *(File**)file_lieu ) ).liberer	= liberer;
	( *( *(File**)file_lieu ) ).tete 	= NULL;
	( *( *(File**)file_lieu ) ).queue 	= NULL;
	return 0;
}



unsigned file_taille ( const file * f ) 
{
	maillon * temp	= (* ( *(File**)f ) ).tete;
	unsigned i 			= 0;
	
	while(temp != NULL) {
		temp = (*temp).precedant;
		i++;
	}	
	return i;
}

/*
	place : en partant de la tete de la file (tete=0).
	Comparatrice doit retourner 0 si val == val2, negatif si val2 < val, positif si val < val2 (modèle strcmp).
*/
int string_file_comparer_elements( const file * f1, const file * f2, unsigned place1, unsigned place2, int ( * comparatrice ) ( const char * val, const char * val2 ) )
{
	unsigned 	f_taille1, 
				f_taille2;
	maillon *temp, *temp2;

	f_taille1 	= file_taille( f1 );
	f_taille2 	= file_taille( f2 );
	
	if ( f_taille1 < place1 || f_taille2 < place2 )
	{
		fprintf(stderr, "taille de file 1 : %u, place 1 : %u, taille de file 2 : %u, place 2 : %u\n", f_taille1, place1, f_taille2, place2);
		exit(EXIT_FAILURE);
	}

	temp 	= ( *( *(File**)f1 ) ).tete;
	temp2 	= ( *( *(File**)f2 ) ).tete;
	
	while( place1-- ) 
	{
		temp = (*temp).precedant;
	}

	while( place2-- ) 
	{
		temp2 = (*temp2).precedant;
	}

	return comparatrice( (*temp).valeur, (*temp2).valeur );
}

int enfiler( file * f, void * value ) 
{
	maillon * m;	
	

	if ( NULL == f ) 
	{
		fprintf(stderr, "Le pointeur sur la file n'a pas ete alloue. Procedez ainsi : file * f = malloc( sizeof( file * ) );");
		return 1;
	}
	if ( NULL == *(File**)f ) 
	{
		fprintf(stderr, "la file n'a pas ete allouee. Utilisez file_creer()");
		return 2;
	}

	m = (maillon *) malloc( sizeof(maillon) );

	if ( NULL == m )
	{
		fprintf(stderr, "Manque de memoire, tentez de fermer des applications (tentative d'allocation pour une structure de 2 pointeurs).");
		return 3;
	}

	(*m).precedant = NULL;		
	( *( *(File**)f ) ).copier( value, &((*m).valeur) );
	if ( file_vide( f ) ) 
	{
		(* ( *(File**)f ) ).tete	= m;
	} else
	{
		(* (* (* (File**)f ) ).queue ).precedant	= m;
	}
	(* (* (File**)f ) ).queue		= m;
	return 0;
}

/* Detruit l'element de tete en un temps constant */
void defiler(file * f)
{
	maillon * temp;
	
	if( file_vide( f ) )
		return;

	temp 							= (* ( *(File**)f ) ).tete;
	(* ( *(File**)f ) ).tete 		= (* (* ( *(File**)f ) ).tete ).precedant;
	(* ( *(File**)f ) ).liberer( (void **)temp );
	
	if ( file_vide(f) )
		(* ( *(File**)f ) ).queue 	= NULL;
}

int empiler( file * f, void * value ) 
{
	maillon * m;	
	

	if ( NULL == f ) 
	{
		fprintf(stderr, "Le pointeur sur la file n'a pas ete alloue. Procedez ainsi : file * f = malloc( sizeof( file * ) );");
		return 1;
	}
	if ( NULL == *(File**)f ) 
	{
		fprintf(stderr, "la file n'a pas ete allouee. Utilisez file_creer()");
		return 2;
	}

	m = (maillon *) malloc( sizeof(maillon) );

	if ( NULL == m )
	{
		fprintf(stderr, "Manque de memoire, tentez de fermer des applications (tentative d'allocation pour une structure de 2 pointeurs).");
		return 3;
	}

	(*m).precedant = (* ( *(File**)f ) ).tete;		
	( *( *(File**)f ) ).copier( value, &((*m).valeur) );

	(* ( *(File**)f ) ).tete	= m;

	return 0;
}

/* Detruit l'element de queue en un temps lineaire */
void depiler(file * f)
{
	maillon *temp, 
			*temp2;

	if( file_vide( f ) )
		return;

	/* au moins 1 maillon */
	temp 	= (* ( *(File**)f ) ).tete;

	if( NULL == (* (* ( *(File**)f ) ).tete ).precedant )
	{
		(* ( *(File**)f ) ).liberer( (void **)temp );
		(* ( *(File**)f ) ).queue 		= NULL;	
		(* ( *(File**)f ) ).tete 	= NULL;	
		return;
	}

	/* plus de 1 maillon */
	temp2	= (* (* ( *(File**)f ) ).tete).precedant;

	while( NULL != (*temp2).precedant )
	{
		temp 	= temp2;
		temp2	= (*temp).precedant;
	}

	(* ( *(File**)f ) ).liberer( (void **)temp2 );
	(* ( *(File**)f ) ).queue 		= temp;	

	if ( file_taille( f ) == 0 )
		(* ( *(File**)f ) ).tete 	= NULL;	
}

void file_detruire ( file * f )
{
	if ( NULL == f )
		return;
	
	while( !file_vide(f) )
		defiler(f);

	free( ( *(File**)f ) );
	free( f );
}

int file_vide ( const file * f ) 
{
	if ( NULL == ( *(File**)f ) ) 
	{
		fprintf(stderr, "La file n'est pas allouee.");
		exit(EXIT_FAILURE);
	}

	if ( NULL == (* ( *(File**)f ) ).tete )
		return 1;
	return 0;
}

void * tete ( const file * f )
{
	if( NULL == f ) 
	{
		fprintf(stderr, "La file pointe sur NULL.");
		return NULL;
	}
	if ( file_vide( f ) )
	{
		fprintf(stderr, "La file est vide : sa tete pointe sur NULL.");
		return NULL;
	}

	return (* (* ( *(File**)f ) ).tete).valeur;
}

void * queue ( const file * f )
{
	if( NULL == f ) 
	{
		fprintf(stderr, "La file pointe sur NULL.");
		return NULL;
	}
	if ( file_vide( f ) )
	{
		fprintf(stderr, "La file est vide : sa tete pointe sur NULL.");
		return NULL;
	}

	return (* (* ( *(File**)f ) ).queue).valeur;
}

/*
void enfiler_file(file * source, file * dest)
{
	while( ! file_vide( source ) ) {
		enfiler( dest, tete( source ) );
		defiler( source );
	}
	file_detruire( source );
}
*/
void file_char_afficher ( const file * f )
{
	maillon * temp;
	int i 			= 0;
	
	if ( NULL == f || file_vide( f ) )
		return;	
	temp 	= (* ( *(File**)f ) ).tete;
	
	while( temp != NULL ) {
		printf("%c %d\n", (*(char *)(*temp).valeur), i++);
		temp = (*temp).precedant;
	}
}

void file_string_afficher ( const file * f )
{
	maillon * temp;
	
	if ( NULL == f || file_vide( f ) )
		return;	
	temp 	= (* ( *(File**)f ) ).tete;
	
	while(temp != NULL) {
		printf("%s", (char*)(*temp).valeur );

		temp = (*temp).precedant;
	}
}