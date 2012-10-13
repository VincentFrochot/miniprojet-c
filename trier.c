#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, char *argv[])
{    
	int i;
	int triInverse=0, triSansRep=0, entreeAutre=0, sortieAutre=0; /* variables d'options */
	char * entree = NULL;
	char * sortie = NULL;

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
		
		/* TEST */
		printf("triInverse: %d\ntriSansRep: %d\nentreeAutre: %d\nentree: %s\nsortieAutre: %d\nsortie: %s\n", triInverse, triSansRep, entreeAutre, entree, sortieAutre, sortie);
	}

	return 0;
}
