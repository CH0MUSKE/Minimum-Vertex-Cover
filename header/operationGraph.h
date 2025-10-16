#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
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

typedef struct solution{
    int cardinal;
    int *couverture;
}solution;

typedef struct _couverture {
    int *listeSommets ; 
} Couverture ; 

Graph *lireGraph (char *f) ; 
int ecrireGraph (char *f, Graph *g) ; 
void libereGraph (Graph *G) ; 
Graph *creeGraph(int n) ; 
Graph *genereGraphAlea (int n, float p) ; 
void afficheGraph(Graph *G) ; 
Graph *copieGraph (Graph *G) ; 
Graph *retireSommet (Graph *G, int v) ; 
Graph *retireEnsembleSommet (Graph *g, int *tab, int len) ; 
int map_indice_sommet(int nbSommets,int *tabSommets, int sommet);
int *algoCouplage(Graph *G, int *tailleCouverture) ; 
int *algoGlouton(Graph *G) ; 
solution branchementSimple(Graph *g, int *C, int n);
