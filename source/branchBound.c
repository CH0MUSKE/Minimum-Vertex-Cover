#include "./header/branchBound.h" 

solution meilleure_solution = {INT_MAX, NULL};

int count = 0;
int count2 = 0;

solution branchSimplInit (Graph *G) {
    solution res = branchementSimple(G, NULL, 0) ; 
    return res ; 
}

solution branchSimplInit2 (Graph *G) {
    solution res = altBranchementSimple(G, NULL, 0) ; 
    return res ; 
}

/*

solution branchementSimple(Graph *g, int *C, int n){

    solution sol;
    // Si le graphe n'as pas d'arêtes, on arrête la récursion 
    // car on a plus d'arête à couvrir
    if(g -> nbAretes == 0){
        sol.cardinal = n;
        sol.couverture = C;
        return sol;
    }
    // Sinon on prend une arête du graphe {u, v}
    int *arete = uneArete(g);
    int u = arete[0];
    int v = arete[1];
    free(arete);
    Graph *gcpy1 = copieGraph(g);
    Graph *gcpy2 = copieGraph(g);
    
    // On retire u (resp v) de g pour les ajouter aux couvertures 
    Graph *g_sans_u = retireSommet(gcpy1,u);
    Graph *g_sans_v = retireSommet(gcpy2,v);

    // On met à jour la couverture des deux graphe ainsi crées 
    int *C_u = malloc(sizeof(int) * (n+1));
    int *C_v = malloc(sizeof(int) * (n+1));
    if(C != NULL){
        // Copie de la couverture du noeud père dans les noeuds fils 
        memcpy(C_u,C,sizeof(int) * n);
        memcpy(C_v,C,sizeof(int) * n);
    }
    // On ajoute u (resp v) aux tableaux 
    C_u[n] = u;
    C_v[n] = v;
    // On détruit la liste précédente si nécessaire 
    if(C != NULL){
        free(C);
    }
    // On calcule les couvrement optimaux sachant U 
    //  dans la couveture et V dans la couverture 
    solution branche_u = branchementSimple(g_sans_u,C_u,n+1);
    solution branche_v = branchementSimple(g_sans_v,C_v,n+1);

    freeGraph(g_sans_u);
    freeGraph(g_sans_v);
    // Si la solution du sous-arbre gauche est meilleure que celle de droite, 
    // on prend celle-ci, sinon l'autre 
    if(branche_u.cardinal < branche_v.cardinal){
        free(branche_v.couverture);
        return branche_u;
    }
    free(branche_u.couverture);
    return branche_v;
}
*/

solution branchementSimple(Graph *g, int *C, int n){
    solution sol;
    // Si le graphe n'as pas d'arêtes, on arrête la récursion 
    // car on a plus d'arête à couvrir
    Graph *gCopy = copieGraph(g) ; 
    gCopy = retireEnsembleSommet(gCopy, C, n) ; 
    if (gCopy) {
        if(gCopy->nbAretes == 0){
            sol.cardinal = n;
            sol.couverture = C;
            return sol;
        }
        // =========================A FINIIIIIIIIIIIIIIIIIIIIIIIIIIIIIR
    }
    else {
        sol.cardinal = n;
        sol.couverture = C;
        return sol;
    }
    
    // Sinon on prend une arête du graphe {u, v}
    int *arete = uneArete(gCopy);
    int u = arete[0];
    int v = arete[1];
    
    free(arete);
    freeGraph(gCopy) ; 
    
    // On met à jour la couverture des deux graphe ainsi crées 
    int *C_u = malloc(sizeof(int) * (n+1));
    int *C_v = malloc(sizeof(int) * (n+1));
    if(C != NULL){
        // Copie de la couverture du noeud père dans les noeuds fils 
        memcpy(C_u,C,sizeof(int) * n);
        memcpy(C_v,C,sizeof(int) * n);
    }
    // On ajoute u (resp v) aux tableaux 
    C_u[n] = u;
    C_v[n] = v;
    // On détruit la liste précédente si nécessaire 
    if(C != NULL){
        free(C);
    }
    // On calcule les couvrement optimaux sachant U 
    //  dans la couveture et V dans la couverture 
    solution branche_u = branchementSimple(g,C_u,n+1);
    solution branche_v = branchementSimple(g,C_v,n+1);
    // Si la solution du sous-arbre gauche est meilleure que celle de droite, 
    // on prend celle-ci, sinon l'autre 
    if(branche_u.cardinal < branche_v.cardinal){
        free(branche_v.couverture);
        return branche_u;
    }
    free(branche_u.couverture);
    return branche_v;
}


int testElag(Graph *g, int cur_n){
    Couplage c = couplage(g);
    int b2 = c.cardinal;
    freeTab(c.couplage, c.cardinal);
    int degMax = g -> degreSommet[indexSommetDegMax(g)];
    int m = g -> nbAretes;
    int b1;
    if(degMax == 0) b1 = 0;
    else b1 = ceil((double)m/degMax);
    int n = g -> nbSommets;
    double tmp = sqrt(pow(2.0 * n - 1.0, 2.0) - 8.0 * (double)m);
    int b3 = (int)ceil((2.0 * n - 1.0 - tmp) / 2.0);
    int maxb;
    if(b1 >= b2)maxb = b1;
    else maxb = b2;
    if(b3 > maxb) maxb = b3;

    return cur_n + maxb >= meilleure_solution.cardinal;
}

solution copy_sol(solution sol){
    solution s;
    s.cardinal = sol.cardinal;
    s.couverture = malloc(sizeof(int) * s.cardinal);
    for(int i = 0; i < s.cardinal; i++){
        s.couverture[i] = sol.couverture[i];
    }
    return s;
}

solution concatene_sol(solution sol, int *C, int n){
    solution s;
    if(C == NULL){
        s.cardinal = sol.cardinal;
        s.couverture = sol.couverture;
    }
    else{
        s.cardinal = sol.cardinal + n;
        s.couverture = malloc(sizeof(int ) * s.cardinal);
        memcpy(s.couverture,sol.couverture,sol.cardinal);
        memcpy(s.couverture + sol.cardinal,C,n);
    }
    return s;
}

solution branchBorneCouplInit(Graph *g) {
    return branchementBorneCouplage(g, NULL, 0) ;     
}

solution branchementBorneCouplage(Graph *g, int *C, int n){
    printf("--%d--\n",count++);
    if(g -> nbAretes == 0){
        solution sol;
        sol.cardinal = n;
        sol.couverture = C;
        if(n < meilleure_solution.cardinal){
            if(meilleure_solution.couverture != NULL){
                free(meilleure_solution.couverture);
            }
            meilleure_solution = copy_sol(sol);
        }
        return sol;
    }
    if(testElag(g,n)){
        solution s;
        s.cardinal = INT_MAX;
        s.couverture = NULL;
        return s;
    }
    Graph *h = copieGraph(g);
    solution s = algoCouplage(h);
    freeGraph(h);
    solution sol = concatene_sol(s,C,n);
    if(sol.cardinal < meilleure_solution.cardinal){
        if(meilleure_solution.couverture != NULL){
            free(meilleure_solution.couverture);
        }
        meilleure_solution = copy_sol(sol);
    }

    int *arete = uneArete(g);
    int u = arete[0];
    int v = arete[1];
    free(arete);
    Graph *gcpy1 = copieGraph(g);
    Graph *gcpy2 = copieGraph(g);
    Graph *g_sans_u = retireSommet(gcpy1,u);
    Graph *g_sans_v = retireSommet(gcpy2,v);
    int *C_u = malloc(sizeof(int) * (n+1));
    int *C_v = malloc(sizeof(int) * (n+1));
    if(C != NULL){
        memcpy(C_u,C,sizeof(int) * n);
        memcpy(C_v,C,sizeof(int) * n);
    }
    C_u[n] = u;
    C_v[n] = v;
    if(C != NULL){
        free(C);
    }
    solution branche_u = branchementBorneCouplage(g_sans_u,C_u,n+1);
    solution branche_v = branchementBorneCouplage(g_sans_v,C_v, n+1);

    freeGraph(g_sans_u);
    freeGraph(g_sans_v);

    if(branche_u.cardinal < branche_v.cardinal){
        free(branche_v.couverture);
        return branche_u;
    }
    free(branche_u.couverture);
    return branche_v;
    
}

solution altBranchementBorneCouplage(Graph *g, int *C, int n){
    printf("--%d--\n",count++);
    if(g -> nbAretes == 0){
        solution sol;
        sol.cardinal = n;
        sol.couverture = C;
        if(n < meilleure_solution.cardinal){
            if(meilleure_solution.couverture != NULL){
                free(meilleure_solution.couverture);
            }
            meilleure_solution = copy_sol(sol);
        }
        return sol;
    }
    if(testElag(g,n)){
        solution s;
        s.cardinal = INT_MAX;
        s.couverture = NULL;
        return s;
    }
    Graph *h = copieGraph(g);
    solution s = algoCouplage(h);
    freeGraph(h);
    solution sol = concatene_sol(s,C,n);
    if(sol.cardinal < meilleure_solution.cardinal){
        if(meilleure_solution.couverture != NULL){
            free(meilleure_solution.couverture);
        }
        meilleure_solution = copy_sol(sol);
    }

    int *arete = uneArete(g);
    int u = arete[0];
    int v = arete[1];
    free(arete);
    Graph *gcpy1 = copieGraph(g);
    Graph *gcpy2 = copieGraph(g);
    Graph *g_sans_u = retireSommet(gcpy1,u);
    Graph *g_sans_v = retireSommet(gcpy2,v);
    int *C_u = malloc(sizeof(int) * (n+1));
    int *C_v = malloc(sizeof(int) * (n+1));
    if(C != NULL){
        memcpy(C_u,C,sizeof(int) * n);
        memcpy(C_v,C,sizeof(int) * n);
    }
    C_u[n] = u;
    C_v[n] = v;
    if(C != NULL){
        free(C);
    }
    solution branche_u = altBranchementBorneCouplage(g_sans_u,C_u,n+1);
    solution branche_v = altBranchementBorneCouplage(g_sans_v,C_v, n+1);

    freeGraph(g_sans_u);
    freeGraph(g_sans_v);

    if(branche_u.cardinal < branche_v.cardinal){
        free(branche_v.couverture);
        return branche_u;
    }
    free(branche_u.couverture);
    return branche_v;
    
}

Pile *empile (Pile *p, solution *s) {
    Pile *tete = creeElPile(s) ; 
    tete->suiv = p ; 
    return tete ; 
}

Pile *depile (Pile *p, Pile **el) {
    if (p) {
        Pile *newTete = p->suiv ; 
        *el = p ; 
        return newTete ; 
    }
}

void liberePile (Pile *p) {
    if (p) {
        Pile *suiv = p->suiv ;
        libereElPile(p) ; 
        liberePile(suiv) ;  
    }
}

void libereElPile (Pile *p) {
    if (p) {
        free(p->s) ; 
        free(p) ; 
    }
}

Pile *creeElPile (solution *s) {
    Pile *res = malloc(sizeof(Pile)) ; 
    res->suiv = NULL ; 
    res->s = copieSolution(s) ; 
    return res ; 
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