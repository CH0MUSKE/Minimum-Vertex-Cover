#include "./header/operationGraph.h"
 
int calcNbAretes (Graph *g) {
    if (g)
    {
        int res = 0 ; 
        for (int i = 0 ; i < g->nbSommets ; i++) {
            res += g->nbAretes[i] ; 
        }
        return res ; 
    }
    return 0 ; 
}

float valRandom() {
    // Tire une valeur aléatoire entre 0 et 1 
    return ((float) rand()) / ((float) RAND_MAX) ; 
}

Graph *genereGraphAlea (int n, float p) {
    srand(time(NULL)) ;
    if ((p <= 1 && p >= 0) && (n > 0)) {
        return NULL ; 
    }

    Graph *res = creeGraph(n) ; 
    res->tabSommets = malloc(sizeof(int) * res->nbSommets) ; 
    res->nbAretes = malloc(sizeof(int) * res->nbSommets) ; 
    res->tabAdjacence = malloc(sizeof(int*) * res->nbSommets) ; 
    // On crée les sommets 
    for (int i = 0 ; i < res->nbSommets ; i++) {
        res->tabSommets[i] = i ; 
        res->nbAretes[i] = res->nbSommets - 1 ; 
        res->tabAdjacence[i] = malloc(sizeof(int) * res->nbAretes[i]) ; 
        for (int j = 0 ; j < res->nbAretes[i] ; j++) {
            res->tabAdjacence[i][j] = -1 ; 
        }
    }
    
    // On crée les arcs 
    int *nbArreteCourant = malloc(sizeof(int) * res->nbSommets) ; 
    for (int i = 0; i < res->nbSommets ; i++) {
        nbArreteCourant[i] = 0 ; 
    }

    // On considère que on ne peut que rajouter des sommets dont leur numéro est supérieur 
    // Au numéro présent, pour éviter des doubles arcs 
    for (int i = 0 ; i < res->nbSommets ; i++) {
        
        // ########################## Changer valRandom en : 
        // Génerateur de nombre random https://blog.bithole.dev/blogposts/random-float/
        for (int j = i + 1 ; j < res->nbSommets ; j++) {
            if (valRandom() < p) {
                
                // On met j dans les adjacents de i 
                res->tabAdjacence[i][nbArreteCourant[i]] = j ; 
                nbArreteCourant[i] += 1 ; 
                // On met i dans les adjacents de j 
                res->tabAdjacence[j][nbArreteCourant[j]] = i ; 
                nbArreteCourant[j] += 1 ; 
            }
        }
        int temp = 0 ; 
        res->tabAdjacence[i] = raccourcitListe(res->tabAdjacence[i], res->nbAretes[i], &temp) ; 
        res->nbAretes[i] = temp ; 
    }
    free(nbArreteCourant) ; 
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
    for (int i = 0 ; i < g->nbSommets ; i++) {
        printf("%d, ", g->nbAretes[i]) ; 
    }
    

}

Graph *retireSommet (Graph *G, int v) {
    // Cas pathologique : 1 ou 0 sommets 
    int *index ; 
    Graph *res = copieGraph(G) ; 
    
    res->tabSommets = supprimePremierEl(res->tabSommets, res->nbSommets, v, index) ; 
    int **tabAdj = NULL ; 
    
    if (*index != -1) {
        
        int *estSupprime ; 
        
        // v est dans G 
        *estSupprime = 1 ; 
        tabAdj = malloc(sizeof(int*) * (res->nbSommets - 1)) ; 
        int q = 0 ; 
        for (int i = 0 ; i < res->nbSommets ; i++) {
            if (*index != i) {
                tabAdj[i - q] = supprimePremierEl(res->tabAdjacence[i], res->nbAretes[i], v, estSupprime) ; 
                if (*estSupprime != -1) {
                    res->nbAretes[i] -= 1 ; 
                }
            }
            else {
                q = 1 ; 
            }
        }
        
        int *t = retireValTabIndex(res->nbAretes, res->nbSommets, *index, estSupprime) ; 
        res->nbAretes = t ; 
        
        for (int i = 0 ; i < res->nbSommets ; i++) {
            free(res->tabAdjacence[i]) ; 
        }
        free(res->tabAdjacence) ; 
        res->tabAdjacence = tabAdj ; 

        res->nbSommets -= 1 ; 
        libereGraph(G) ; 
    }
    else {
        libereGraph(G) ; 
    }
    return res ; 
}