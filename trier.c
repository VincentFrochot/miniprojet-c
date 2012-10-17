#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "trier.h"


void char_copier ( void * valeur , void ** lieu )
{
	(*lieu) 	= malloc( sizeof( char ) );
	memcpy( (*lieu), valeur, sizeof( char ) );
	return ;
}

void liberer ( void ** lieu )
{
	free( (*lieu) );
	return;
}

int main ( int argc, char *argv[] )
{    
	int i;
	int triInverse=0, triSansRep=0, entreeAutre=0, sortieAutre=0; /* variables d'options */
	char * entree = NULL;
	char * sortie = NULL;
	char tableau [5] = {7,5,9,1,3}; /* Variables de test */
	void * resultat;
	file * f = malloc( sizeof( file ) );
	int res;
	char * test = "abc";
	
	res = file_creer( f, &char_copier, &liberer );
	if ( res )
		return res;
	printf( "PLOP\n" );
	enfiler( f, test );
	file_afficher( f );
	
	
	if (argc > 1)
	{
		for ( i=1 ; i < argc ; i++ ) 
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
			else if ((strcmp(argv[i-1],"-o"))!=0)
			{
				entreeAutre = 1;
				entree = argv[i]; /* Entrée spécifiée */
			}
		}
		
		/* Test des paramètres
		printf("triInverse: %d\ntriSansRep: %d\nentreeAutre: %d\nentree: %s\nsortieAutre: %d\nsortie: %s\n", triInverse, triSansRep, entreeAutre, entree, sortieAutre, sortie); */
		
/*		resultat = decoupe(tableau,5); */
	}

	free(f);

	printf("PLOP\n");
	return EXIT_SUCCESS;
}