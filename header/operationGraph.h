#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./header/operationTableau.h"
#include <string.h>

typedef struct _graph {
    int nbSommets ; 
    int nbAretes;
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

Graph *lireGraph (char *f) ; 
int ecrireGraph (char *f, Graph *g) ; 
void libereGraph (Graph *g) ; 
Graph *creeGraph(int n) ; 
Graph *genereGraphAlea (int n, float p) ; 
void afficheGraph(Graph *g) ; 
Graph *copieGraph (Graph *g) ; 
Graph *retireSommet (Graph *G, int v) ; 
Graph *retireEnsembleSommet (Graph *g, int *tab, int len) ; 
int map_indice_sommet(int nbSommets,int *tabSommets, int sommet);