#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./header/operationTableau.h"

typedef struct _graph {
    int nbSommets ; 
    int nbAretes ; 
    int *degreSommet ; // On suppose que les labels sont en ordre croissant 
    int *tabSommets ; 
    int **tabAdjacence ; // Tableau 
} Graph ; 
// Un graphe vide est un graphe n'ayant pas de sommets 
// On suppose que un graphe vide est représenté par NULL 


typedef struct _couverture {
    int *listeSommets ; 
} Couverture ; 

Graph *lireGraph (FILE *f) ; 
int ecrireGraph (FILE *f, Graph *G) ; 
void libereGraph (Graph *G) ; 
Graph *creeGraph(int n) ; 
Graph *genereGraphAlea (int n, float p) ; 
void afficheGraph(Graph *G) ; 
Graph *copieGraph (Graph *G) ; 
Graph *retireSommet (Graph *G, int v) ; 
Graph *retireEnsembleSommet (Graph *g, int *tab, int len) ; 
int *algoCouplage(Graph *G, int *tailleCouverture) ; 
int *algoGlouton(Graph *G) ; 