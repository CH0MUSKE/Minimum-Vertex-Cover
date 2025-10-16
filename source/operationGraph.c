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
        res->tabAdjacence[i] = raccourcitListe(res->tabAdjacence[i], res->degreSommet[i], &temp) ; 
        res->degreSommet[i] = temp ; 
    }
    free(nbArreteCourant) ; 
    
    return res ;         
}


Graph *creeGraph(int n) {
    Graph *res = malloc(sizeof(Graph)) ; 
    res->nbSommets = n ; 
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
	int estDetruit ; 
	res->tabSommets = supprimePremierEl(res->tabSommets, res->nbSommets, v, &estDetruit) ; 

	if (estDetruit != -1 && res->nbSommets > 1) {
        // Etape 2 
		int temp ; 
		for (int i = 0 ; i < res->degreSommet[estDetruit] ; i++) {
            int sommetAdj = res->tabAdjacence[estDetruit][i] ; 
			res->tabAdjacence[sommetAdj] = 
            supprimePremierEl(res->tabAdjacence[sommetAdj], res->degreSommet[sommetAdj], v, &temp) ; 
			res->degreSommet[sommetAdj] -= 1 ; 
		}
        
		// Etape 3 
		res->degreSommet = retireValTabIndex(res->degreSommet, res->nbSommets, estDetruit, &temp) ; 
        int **listAdj = malloc(sizeof(int*) * (res->nbSommets - 1)) ; 
        temp = 0 ; 
        for (int i = 0 ; i < res->nbSommets ; i++) {
            if (estDetruit != i) {
                listAdj[i - temp] = res->tabAdjacence[i] ; 
            }
            else {
                temp = 1 ; 
            }
        }
        free(res->tabAdjacence) ; 
        res->tabAdjacence = listAdj ; 

		res->nbSommets -= 1 ; 
	}
    else if (estDetruit != -1 && res->nbSommets == 1) {
        libereGraph(res) ; 
        res = NULL ; 
    }
	return res ; 
}

Graph *retireEnsembleSommet (Graph *g, int *tab, int len) {
    Graph *prec = g ; 
    Graph *suiv = NULL ; 
    for (int i = 0 ; i < len ; i++) {
        printf("Graphe a l'etape %d, retrait de %d\n\n\n",i, tab[i]) ; 
        afficheGraph(prec) ;
        if (prec) {
            suiv = retireSommet(prec, tab[i]) ; 
            prec = suiv ; 
        }
        else {
            return prec ; 
        }       
    }
    return suiv ; 
}

int **listeAretes(Graph *g){
    int nbSommets = g ->nbSommets;
    int nbAretes = g -> nbAretes;
    int **list = malloc(sizeof(int *) * nbAretes); 
    for (int i = 0; i < nbSommets; i++){
            list[i] = malloc(sizeof(int) * 2);
            for (int j = 0 ;j< g -> degreSommet[i]; j++){
                if(g->tabSommets[i] < g->tabAdjacence[i][j]){
                    list[i][0] = g ->tabSommets[i];
                    list[i][j] = g -> tabAdjacence[i][j];
                }
            }
    }
    return list;
}

solution branchementSimple(Graph *g, int *C, int n){
    solution sol;
    if(g -> nbAretes == 0){
        sol.cardinal = n;
        sol.couverture = C;
        return sol;
    }
    int **liste_aretes = listeAretes(g);
    int u = liste_aretes[0][0];
    int v = liste_aretes[0][1];
    freeTab(liste_aretes,n);
    Graph *g_sans_u = retireSommet(g,u);
    Graph *g_sans_v = retireSommet(g,v);
    int *C_u = malloc(sizeof(int) * (n+1));
    int *C_v = malloc(sizeof(int) * (n+1));
    memcpy(C_u,C,sizeof(int) * n);
    memcpy(C_v,C,sizeof(int) * n);
    C_u[n] = u;
    C_v[n] = v;
    free(C);
    solution branche_u = branchementSimple(g_sans_u,C_u,n+1);
    solution branche_v = branchementSimple(g_sans_v,C_v, n+1);

    freeGraph(g_sans_u);
    freeGraph(g_sans_v);

    if(branche_u.cardinal < branche_v.cardinal){
        free(branche_v.couverture);
        return branche_u;
    }
    free(branche_u.couverture);
    return branche_v;
    
}