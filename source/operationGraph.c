#include "./header/operationGraph.h"
 
int calcdegreSommet (Graph *g) {
    if (g)
    {
        int res = 0 ; 
        for (int i = 0 ; i < g->nbSommets ; i++) {
            res += g->degreSommet[i] ; 
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
    if (p > 1 || p < 0 || n <= 0) {
        return NULL ; 
    }

    Graph *res = creeGraph(n) ; 
    res->tabSommets = malloc(sizeof(int) * res->nbSommets) ; 
    res->degreSommet = malloc(sizeof(int) * res->nbSommets) ; 
    res->tabAdjacence = malloc(sizeof(int*) * res->nbSommets) ; 
    // On crée les sommets 
    for (int i = 0 ; i < res->nbSommets ; i++) {
        res->tabSommets[i] = i ; 
        res->degreSommet[i] = res->nbSommets - 1 ; 
        res->tabAdjacence[i] = malloc(sizeof(int) * res->degreSommet[i]) ; 
        for (int j = 0 ; j < res->degreSommet[i] ; j++) {
            res->tabAdjacence[i][j] = -1 ; 
        }
    }
    
    // On initialise les degrés temporaires des arcs 
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
        res->tabAdjacence[i] = raccourcitListe(res->tabAdjacence[i], res->degreSommet[i], &temp) ; 
        res->degreSommet[i] = temp ; 
        res->nbAretes += temp ; 
    }
    free(nbArreteCourant) ; 
    
    return res ;         
}


Graph *creeGraph(int n) {
    Graph *res = malloc(sizeof(Graph)) ; 
    res->nbSommets = n ; 
    res->nbAretes = 0 ; 
    res->degreSommet = NULL ; 
    res->tabSommets = NULL ; 
    res->tabAdjacence = NULL ; 
    return res ; 
}

void libereGraph (Graph *g) {
    if (g) {
        free(g->degreSommet) ; 
        free(g->tabSommets) ; 
        
        for (int i = 0 ; i < g->nbSommets ; i++) {
            if (g->tabAdjacence[i]) {
                free(g->tabAdjacence[i]) ; 
            }
        }

        free(g) ; 
    }
}

Graph *copieGraph (Graph *g) {
    Graph *res = creeGraph(g->nbSommets) ; 
    res->nbAretes = g->nbAretes ; 
    res->degreSommet = copieTab(g->degreSommet, g->nbSommets) ; 
    res->tabSommets = copieTab(g->tabSommets, g->nbSommets) ; 
    res->tabAdjacence = malloc(sizeof(int*)*g->nbSommets) ; 

    for (int i = 0 ; i < g->nbSommets ; i++) {
        res->tabAdjacence[i] = copieTab(g->tabAdjacence[i], g->degreSommet[i]) ; 
    }
    return res ; 
}

void afficheGraph(Graph *g) {
    if (g) {
        printf("Tableau des sommets : ") ; 
        afficheTab(g->tabSommets, g->nbSommets) ; 
    
        // Finir affichage 
        for (int i = 0 ; i < g->nbSommets ; i++) {
            printf("Sommets adjacents de %d : ", g->tabSommets[i]) ; 
            afficheTab(g->tabAdjacence[i], g->degreSommet[i]) ; 
        }
        printf("Liste des tailles des listAdj : ") ; 
        afficheTab(g->degreSommet, g->nbSommets) ; 
    } 
    else {
        printf("Graphe est vide\n") ; 
    }

}

Graph *retireSommet (Graph *G, int v) {
	/*
	1. Détruire le sommet v dans la liste des sommets de G 
	2. Pour chaque sommet présent dans la liste des adjacents du sommet v : 
		2.1. Détruire le sommet v de cette liste 
	3. Détruire la liste des adjacents du sommet v 
	*/

    Graph *res = copieGraph(G) ; 
	libereGraph(G) ; 
	int posValSupprimer = calculeIndexValeur(res->tabSommets, res->nbSommets, v) ; 
    //printf("---------------- 3\n") ; 
	if (posValSupprimer != -1 && res->nbSommets > 1) {
        // Etape 2 
		int temp ; 
        
		for (int i = 0 ; i < res->degreSommet[posValSupprimer] ; i++) {
            int posSommetAdj = calculeIndexValeur(res->tabSommets, res->nbSommets, res->tabAdjacence[posValSupprimer][i]) ; 
            //printf("---------------- 3e\n") ; 
            afficheTab(res->tabAdjacence[posSommetAdj], res->degreSommet[posSommetAdj]) ; 
        
			res->tabAdjacence[posSommetAdj] = 
            supprimePremierEl(res->tabAdjacence[posSommetAdj], res->degreSommet[posSommetAdj], v, &temp) ; 
            if (temp != -1) {
                res->degreSommet[posSommetAdj] -= 1 ; 
            }
            else {
                printf("%p\n", res->tabAdjacence[posSommetAdj]) ; 
                afficheTab(res->tabAdjacence[posSommetAdj], res->degreSommet[posSommetAdj]) ; 
                printf("%d, Error\n", posSommetAdj) ; 
            }
		}

		// Etape 3 
        res->nbAretes -= res->degreSommet[posValSupprimer] ; 
		res->degreSommet = retireValTabIndex(res->degreSommet, res->nbSommets, posValSupprimer, &temp) ; 
        int **listAdj = malloc(sizeof(int*) * (res->nbSommets - 1)) ; 

        temp = 0 ; 
        for (int i = 0 ; i < res->nbSommets ; i++) {
            if (posValSupprimer != i) {
                listAdj[i - temp] = res->tabAdjacence[i] ; 
            }
            else {
                temp = 1 ; 
            }
        }
        free(res->tabAdjacence) ; 
        res->tabAdjacence = listAdj ; 
        res->tabSommets = retireValTabIndex(res->tabSommets, res->nbSommets, posValSupprimer, &temp) ; 
		res->nbSommets -= 1 ; 
	}
    else if (posValSupprimer != -1 && res->nbSommets == 1) {
        libereGraph(res) ; 
        res = NULL ; 
    }
	return res ; 
}

Graph *retireEnsembleSommet (Graph *g, int *tab, int len) {
    Graph *prec = g ; 
    Graph *suiv = NULL ; 
    for (int i = 0 ; i < len ; i++) {
        //printf("---------------- 2\n") ; 
        if (prec) {
            suiv = retireSommet(prec, tab[i]) ; 
            prec = suiv ; 
        }
        else {
            return prec ; 
        }
        //printf("---------------- 2e\n") ; 
        afficheGraph(suiv) ; 
    }
    return suiv ; 
}

int *algoCouplage(Graph *G, int *tailleCouverture) {
    int *C = malloc(sizeof(int) * G->nbSommets) ; 
    int nbSommetsCouverture = 0 ; 
    for (int i = 0 ; i < G->nbSommets ; i++) {
        C[i] = -1 ; 
    }
    Graph *grapheCourant = copieGraph(G) ; 
    for (int i = 0 ; i < grapheCourant->nbSommets ; i++) {
        
        if (grapheCourant->nbAretes > 0) {
            for (int j = 0 ; j < grapheCourant->degreSommet[i] ; j++) {
                int *aRetirer = malloc(sizeof(int) * 2) ; 
                aRetirer[0] = grapheCourant->tabSommets[i] ; 
                aRetirer[1] = grapheCourant->tabAdjacence[i][j] ; 
                //printf("---------------- 1\n") ; 
                grapheCourant = retireEnsembleSommet(
                    grapheCourant, 
                    aRetirer, 
                    2
                ) ; 
                //printf("---------------- 1e\n") ; 
                C[nbSommetsCouverture] = grapheCourant->tabSommets[i] ; 
                C[nbSommetsCouverture + 1] = grapheCourant->tabAdjacence[i][j] ; 
                nbSommetsCouverture += 2 ; 
                i = 0 ; 
            }
        }
        afficheGraph(G) ; 
    }
    C = raccourcitListe(C, G->nbSommets, tailleCouverture) ; 
    return C ; 
} 
