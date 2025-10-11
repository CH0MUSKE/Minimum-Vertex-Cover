#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./header/operationTableau.h"

typedef struct _graph {
    int nbSommets ; 
    int *nbAretes ; // On suppose que les labels sont en ordre croissant 
    int *tabSommets ; 
    int **tabAdjacence ; 
} Graph ; 

Graph *lireGraph (FILE *f) ; 
int ecrireGraph (FILE *f, Graph *g) ; 
void libereGraph (Graph *g) ; 
Graph *creeGraph(int n) ; 
Graph *genereGraphAlea (int n, float p) ; 
void afficheGraph(Graph *g) ; 
Graph *copieGraph (Graph *g) ; 
Graph *retireSommet (Graph *G, int v) ; 
