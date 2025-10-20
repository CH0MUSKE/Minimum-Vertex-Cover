#include "./header/branchBound.h" 

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

solution *copieSolution(solution *s) {
    if (s) {
        solution *res = malloc(sizeof(solution)) ; 
        res->cardinal = s->cardinal ; 
        res->couverture = copieTab(s->couverture, s->cardinal) ; 
        return res ; 
    }
    return NULL ; 
}

int valeurBorne (Graph *G, solution *couverture) {
    int *m ; 
    int *couplage = algoCouplage(G, m) ; 
    int b1 = (int) m / (int) G->degreSommet[indexSommetDegMax(G)] ; 
    int b2 = *m ; 
    int b3 = (int) ((2*G->nbSommets - 1 - sqrt( (2*G->nbSommets - 1)*(2*G->nbSommets - 1) - (8 * *m)))) / 2 ; 
    if(b1 >= b2 && b1 >= b3) {
        return b1 ; 
    }
    if(b2 >= b1 && b2 >= b3) {
        return b2 ; 
    }
    if(b3 >= b1 && b3 >= b2) {
        return b3 ; 
    }
    else {
        return -1 ; 
    }
}