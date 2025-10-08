#include <stdio.h>
#include <stdlib.h>

typedef struct _graph {
    int nbSommets ; 
    int *nbAretes ; // On suppose que les labels sont en ordre croissant 
    int *tabSommets ; 
    int **tabAdjacence ; 
} Graph ; 

Graph *lireGraph (FILE *f) ; 
int ecrireGraph (FILE *f, Graph *g) ; 
void libereGraph (Graph *g) ; 
int *supprimePremierEl (int* tab, int len, int e, int *index) ; 
void afficheTab (int *tab, int len) ; 