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
#include "trier.h"
#include "file.h"
#include "trier_monotonie.h"

file * trier_monotonie (file * fileSource)
{
  unsigned i        = 0,
      nbMono        = 1,  /* on aura toujours au moins une monotonie */
      nbMonotonies  = 1;  /*  */
  int    comp;
  int *nbelem1,
      *nbelem2;
  file  *f1         = (file *) malloc( sizeof( file* ) ),
        *f2         = (file *) malloc( sizeof( file* ) );

  file_creer(f1, &string_copier, &string_liberer);
  file_creer(f2, &string_copier, &string_liberer);

  /* compte le nb de monotonies */
  while ( i < file_taille( fileSource )-1 )
  {
      comp = string_file_comparer_elements( fileSource, fileSource, (unsigned)i, (unsigned)i+1, &strcmp ); 
      if ( comp > 0 )
      {
        nbMono++;
      }
      i++;
  }

  if (nbMono == 1)
  {
    return fileSource;
  }

  if ( nbMono % 2 )
  {
    nbelem1 = malloc( (( nbMono / 2 ) + 1) * sizeof( int ) );
    nbelem2 = malloc( (( nbMono / 2 ) + 1) * sizeof( int ) );
  }
  else
  {
    nbelem1 = malloc( ( nbMono / 2 ) * sizeof( int ) );
    nbelem2 = malloc( ( nbMono / 2 ) * sizeof( int ) );
  }

  do /* Processus de tri */
  {
    i             = 0;
    while( i < nbMono - 1 )
    {
      nbelem1[i] = 0;
      nbelem2[i] = 0;
      i++;
    }
    nbMono        = 1;
    nbMonotonies  = 1;

    do /* Séparation en deux files */   
    {  
      comp = string_file_comparer_elements( fileSource, fileSource, (unsigned)0, (unsigned)1, &strcmp ); 

      if ( nbMono % 2 )
      {
        enfiler( f2, tete( fileSource ) );
        nbelem2[nbMonotonies-1]++;
        defiler( fileSource );
      }
      else
      {
        enfiler( f1, tete( fileSource ) );
        nbelem1[nbMonotonies-1]++;
        defiler( fileSource );
      }

      if ( comp > 0 )
      {
        nbMono++;
        if ( nbMono % 2 )
          nbMonotonies++;
      }      
    } while ( file_taille( fileSource ) > 1 );

    if ( nbMono % 2 )
    {
      enfiler( f2, tete( fileSource ) );
      nbelem2[nbMonotonies-1]++;
      defiler( fileSource );
    }
    else
    {
      enfiler( f1, tete( fileSource ) );
      nbelem1[nbMonotonies-1]++;
      defiler( fileSource );
    }

    nbMono = 0;
    if (nbMonotonies != 1)
    {
      while( !file_vide( f1 ) || !file_vide( f2 )  )                  /* tant qu'il existe des elements dans une des deux files... */
      {
        if( ! nbelem1[nbMono] && ! nbelem2[nbMono] )    /* Si les deux files sont vides */
        {
          nbMono++;                                                 /* passe a la monotonie suivante */
        }
        else                                                            /* sinon */
        {
          if ( !nbelem1[nbMono] )                                 /* si la monotonie actuelle dans f1 est vide et l'autre dans f2 contient des elements */
          {
            enfiler( fileSource, tete( f2 ) );
            defiler( f2 );
            nbelem2[nbMono]--;
          }
          else if ( !nbelem2[nbMono] )                            /* sinon si la monotonie actuelle dans f2 est vide et l'autre dans f1 contient des elements */
          {
            enfiler( fileSource, tete( f1 ) );
            defiler( f1 );
            nbelem1[nbMono]--;
          }
          else                                                            /* sinon les deux monotonies contiennent des elements : on peut donc les comparer */
          {
            comp = string_file_comparer_elements( f1, f2, (unsigned)0, (unsigned)0, &strcmp ) ; 
            if ( comp <= 0 )
            {
              enfiler( fileSource, tete( f1 ) );
              defiler( f1 );
              nbelem1[nbMono]--;
            }
            else
            {
              enfiler( fileSource, tete( f2 ) );
              defiler( f2 );
              nbelem2[nbMono]--;
            }
          }
        }
      }
    }
    else  /* On a fini : */
    {
      while( !file_vide( f1 ) || !file_vide( f2 ) )             /* Tant que f1 et f2 ne sont pas vide */
      {
        /* on insere la plus petite valeur */
        if ( !nbelem1[nbMonotonies-1] )                                 /* si la monotonie actuelle dans f1 est vide et l'autre dans f2 contient des elements */
        {
          enfiler( fileSource, tete( f2 ) );
          defiler( f2 );
          nbelem2[nbMonotonies-1]--;
        }
        else if ( !nbelem2[nbMonotonies-1] )                            /* sinon si la monotonie actuelle dans f2 est vide et l'autre dans f1 contient des elements */
        {
          enfiler( fileSource, tete( f1 ) );
          defiler( f1 );
          nbelem1[nbMonotonies-1]--;
        }        
        else
        {
          comp = string_file_comparer_elements( f1, f2, (unsigned)0, (unsigned)0, &strcmp ) ;           
          if ( comp <= 0 )
          {
            enfiler( fileSource, tete( f1 ) );
            defiler( f1 );
            nbelem1[nbMonotonies-1]--;
          }
          else
          {
            enfiler( fileSource, tete( f2 ) );
            defiler( f2 );
            nbelem2[nbMonotonies-1]--;
          }  
        }      
      }
    }

    /* compte le nb de monotonies */
    i = 0;
    nbMono = 1;
    while ( i < file_taille( fileSource ) - 1 )
    {
        comp = string_file_comparer_elements( fileSource, fileSource, (unsigned)i, (unsigned)i+1, &strcmp ); 
        if ( comp > 0 )
        {
          nbMono++;
        }
        i++;
    }

  } while (nbMono != 1);

  free(nbelem1);
  free(nbelem2);

  return fileSource;
}