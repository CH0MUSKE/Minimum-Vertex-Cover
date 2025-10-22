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


typedef struct _couverture {
    int *listeSommets ; 
} Couverture ; 

typedef struct couplage
{
    int **couplage;
    int cardinal;
} Couplage;



// Libère le graphe passé en paramètre 
void freeGraph (Graph *G) ; 

// Crée un graphe ayant n sommets 
Graph *creeGraph(int n) ; 

// Génère un graphe de n sommets, avec une probabilité d'avoir une arête entre deux sommets de p 
Graph *genereGraphAlea (int n, float p) ; 

// Affiche le graphe passé en paramètre 
void afficheGraph(Graph *G) ; 

// Copie le graphe passé en paramètre, ne détruit pas le graphe passé en paramètre 
Graph *copieGraph (Graph *G) ; 

// Retire le sommet de label v du graphe G, détruit le graphe G 
Graph *retireSommet (Graph *G, int v) ; 

// Retire les sommets donts les labels sont dans tab du graphe G, détruit le graphe G 
Graph *retireEnsembleSommet (Graph *g, int *tab, int len) ; 

// Calcule une couverture de G
int *algoCouplage(Graph *G, int *tailleCouverture) ; 

// Calcule une couverture de G, avec un algorithme glouton 
int *algoGlouton(Graph *G, int *tailleCouverture) ; 

// Retourne le sommet de degré maximum de G 
int indexSommetDegMax (Graph *G) ; 

// Ecrit le graphe passé en paramètre dans un fichier texte 
int ecrireGraph(char *nom, Graph *g) ; 


// Lit le graphe contenu dans le ficier passé en paramètre 
Graph *lireGraph(char *f) ; 
int **listeAretes(Graph *g);

int *uneArete(Graph *g);

Couplage couplage(Graph *g);