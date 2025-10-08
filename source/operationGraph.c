#include <stdio.h>
#include <stdlib.h>
#include "./header/operationGraph.h"


int recherche(int *tab, int len, int e) {
    // Cherche e dans tab (A remplacer par recherche dicho)
    for (int i = 0 ; i < len ; i++) {
        if (tab[i] == e) {
            return i ; 
        }
    }
    return -1 ; 
}

int rechercheDich (int *tab, int len, int e) {
    if (tab[len / 2] == e) {
        return len / 2 ; 
    }
    else if (tab[len / 2] > e)
    {
        
    }
    
}

void afficheTab (int *tab, int len) {
    for (int i = 0 ; i < len - 1 ; i++) {
        printf("%d, ", tab[i]) ; 
    }
    printf("%d\n", tab[len - 1]) ; 
}

int *copieTab (int *tab, int len) {
    int *res = malloc(sizeof(int) * len) ; 
    if (tab) {
        for (int i = 0 ; i < len ; i++) {
            res[i] = tab[i] ; 
        }
    }
    else {
        return NULL ; 
    }
    return res ; 
}

int *supprimePremierEl (int* tab, int len, int e, int *index) {
    /*
    Retire le premier e contenu dans tab. 
    index vaut : 
    l'index du nombre retiré 
    -1 si il n'y est pas contenu 
    */
    *index = recherche(tab, len, e) ; 
    
    int *res = NULL ; 
    if (*index != -1) {
        
        res = malloc(sizeof(int) * (len - 1)) ; 
        int q = 0 ; 

        for (int i = 0 ; i < len - 1 ; i++) {
            if (*index != i) {
                res[i - q] = tab[i] ; 
            }
            else {
                q = 1 ; 
            }
        }
    }
    else {

        res = malloc(sizeof(int) * (len)) ; 
        for (int i = 0 ; i < len - 1 ; i++) {
            res[i] = tab[i] ; 
        }

    }

    return res ; 
}


Graph *creeGraph(int n) {
    Graph *res = malloc(sizeof(Graph)) ; 
    res->nbSommets = n ; 
    res->nbAretes = NULL ; 
    res->tabSommets = NULL ; 
    res->tabAdjacence = NULL ; 
    return res ; 
}

void libereGraph (Graph *g) {
    if (g) {
        free(g->nbAretes) ; 
        free(g->tabSommets) ; 
        for (int i = 0 ; i < g->nbSommets ; i++) {
            free(g->tabAdjacence[i]) ; 
        }
        free(g) ; 
    }
}

Graph *copieGraph (Graph *g) {
    Graph *res = creeGraph(g->nbSommets) ; 
    res->nbAretes = copieTab(g->nbAretes, g->nbSommets) ; 
    res->tabSommets = copieTab(g->tabSommets, g->nbSommets) ; 
    res->tabAdjacence = malloc(sizeof(int*)*g->nbSommets) ; 
    for (int i = 0 ; i < g->nbSommets ; i++) {
        res->tabAdjacence[i] = copieTab(g->tabAdjacence[i], g->nbAretes[i]) ; 
    }
    return res ; 
}

void afficheGraph(Graph *g) {
    printf("Tableau des sommets : ") ; 
    afficheTab(g->tabSommets, g->nbSommets) ; 
    // Finir affichage 
    for (int i = 0 ; i < g->nbSommets ; i++) {
        printf("Sommets adjacents de %d : ", g->tabSommets[i]) ; 
        afficheTab(g->tabAdjacence[i], g->nbAretes[i]) ; 
    }
}

Graph *retireSommet (Graph *G, int v) {
    // Cas pathologique : 1 ou 0 sommets 
    int *index ; 

    Graph *res = copieGraph(G) ; 
    
    res->tabSommets = supprimePremierEl(res->tabSommets, res->nbSommets, v, index) ; 
    
    int **tabAdj = NULL ; 
    
    if (*index != -1) {

        // v est dans G 
        
        tabAdj = malloc(sizeof(int*) * (res->nbSommets - 1)) ; 
        int q = 0 ; 

        for (int i = 0 ; i < res->nbSommets ; i++) {
            if (*index != i) {
                tabAdj[i - q] = supprimePremierEl(res->tabAdjacence[i], res->nbAretes[i], v, &q) ; 
            }
            else {
                q = 1 ; 
            }
        }

        
        for (int i = 0 ; i < res->nbSommets ; i++) {
            free(res->tabAdjacence[i]) ; 
        }
        free(res->tabAdjacence) ; 
        res->tabAdjacence = tabAdj ; 

        res->nbSommets -= 1 ; 
    }
    else {

        return NULL ; 
    }
}