/*
  * Provides:
  * - 
  * Version: ...
  * Author: Vincent Frochot / Simon Jornet
  * Copyright: 2012 - Vincent Frochot, Simon Jornet
*/
  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trier_monotonie.h"
#include "file.h"
#include "trier.h"

#define NB_MAX_CHARS 256

void char_copier ( const void * valeur , void ** lieu )
{
	(*lieu)	= calloc( 1, sizeof( char ) );
	memcpy( (*lieu), valeur, sizeof( char ) );
	return;
}

void char_liberer ( void ** lieu )
{
	*(char *)*lieu	= 0;
	free( (*lieu) );
	free( lieu );
	return;
}

void string_copier ( const void * valeur , void ** lieu )
{
	(*lieu) = calloc( ( strlen( valeur ) )+1, sizeof( char ) );
	if ( NULL == (*lieu) )
	{
		fprintf(stderr, "L'allocation memoire n'a pas fonctionne : %d octets requis.\n", (int) ( strlen(valeur) + 1 ) );
		return;
	}

	strcpy( (*lieu), valeur );

	return;
}

void string_liberer ( void ** lieu )
{
	int i = 0;
	while ( '\0' != *(char *)( (*(char **)lieu) + i ) )
	{
		*(char *)( (*(char **)lieu) + i ) = '\0';
	}
	free( (*lieu) );
	free( lieu );

	return;
}

int main ( int argc, char *argv[] )
{

	unsigned 	i;
	int
			triInverse=0, 
			triSansRep=0, 
			entreeAutre=0, 
			sortieAutre=0; /* variables d'options */
	char 	* entree 		= NULL,
			* sortie 		= NULL,
			* ligne			= NULL; /* contient la ligne en cours de traitement */
	FILE 	*fichier_entree, 
			*fichier_sortie;
	file 	*f;

	ligne 	= malloc( sizeof( char ) * NB_MAX_CHARS );					
	f 		= malloc( sizeof( file * ) );

	file_creer( f, &string_copier, &string_liberer );	

	if (argc > 1)
	{
		for ( i=1 ; i < (unsigned)argc ; i++ ) 
		{
			if (strcmp(argv[i],"-r")==0)
			{
				triInverse=1; /* Activation du mode tri inversé */
			}
			else if (strcmp(argv[i],"-u")==0)
			{
				triSansRep=1; /* Activation du mode tri sans répétitions */
			}
			else if (strcmp(argv[i],"-o")==0)
			{
				sortieAutre = 1;
				sortie = argv[i+1]; /* Sortie spécifiée */
			}
			else
			{
				if (!sortieAutre)
				{
					entreeAutre = 1;
					entree = argv[i]; /* Entrée spécifiée */
				}
			}
		}
		
		if( !entreeAutre )
		{ /* il faut que l'utilisateur entre les phrases. */				
			printf ("Veuillez entrer vos phrases, écrivez \"stop\" lorsque vous aurez terminé.\n");
			do
			{
				gets(ligne);
				if (0 != strcmp(ligne, "stop"))
					enfiler( f, ligne );
			} while (0 != strcmp(ligne, "stop"));
		}
		else
		{ /* il faut lire les phrases depuis le fichier "entree" */
			fichier_entree = fopen(entree, "r");
			if ( NULL == fichier_entree )
			{
				fprintf(stderr, "Le fichier %s semble ne pas exister...", entree);
				return EXIT_FAILURE;
			}		

			while (fgets( ligne , NB_MAX_CHARS, fichier_entree) != NULL)
	        {
				enfiler( f, ligne );
	        }

        	fclose( fichier_entree );
		}

	    trier_monotonie( f );

		
	    if( triInverse )
	    {
			fprintf(stdout, "Pas encore implemente...", entree);
		/*
	    	i = 0;
	    	while ( i < file_taille( f ) )
	    	{
	    		empiler( f, queue( f ) );
	    		depiler( f );
	    		i++;
	    	}
		*/			
	    }
		
		
		if( triSansRep )
	    {
	    	i = file_taille(f);
	    	while ( i )
	    	{
	    		strcpy( (char*)ligne, (char*)tete( f ) );
	    		defiler( f );
	    		if( strcmp( ligne, tete( f ) ) )
	    		{	
	    			enfiler( f, ligne );
	    		}
	    		i--;
	    	}
	    }			

		if( !sortieAutre )
		{
			while( !file_vide( f ) )
			{
				printf("%s\n", (char*)tete( f ));
				defiler( f );
			}			
		}
		else
		{
			fichier_sortie = fopen( sortie, "w+" );  

			if( NULL == fichier_sortie )
			{
				fprintf(stdout, "L'ouverture du fichier %s en ecriture a echouee...", entree);
				return EXIT_FAILURE;
			}

			while( !file_vide( f ) )
			{
				fputs( tete( f ), fichier_sortie);
				defiler( f );
			}

			fclose(fichier_sortie);
		}
	}

	file_detruire( f );
	free(ligne);


	return EXIT_SUCCESS;
}