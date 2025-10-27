#include "./header/branchBound.h" 

solution meilleure_solution = {INT_MAX, NULL};
solution meilleure_solution2 = {INT_MAX, NULL};

int count = 0;
int count2 = 0;

solution branchementSimpleInit (Graph *G) {
    return branchementSimple(G, NULL, 0) ;    
}

solution branchementSimple(Graph *g, int *C, int n){

    solution sol;
    // Si le graphe n'as pas d'arêtes, on arrête la récursion 
    // car la couverture est consituées des sommets restants 
    Graph *gCopy = copieGraph(g) ; 
    gCopy = retireEnsembleSommet(gCopy, C, n) ; 
    
    if(gCopy -> nbAretes == 0){
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
    if(branche_u.cardinal < branche_v.cardinal){
        free(branche_v.couverture);
        return branche_u;
    }
    free(branche_u.couverture);
    return branche_v;

}

int testElag(Graph *g, int cur_n, int ameliore){
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

    if(ameliore){
        return cur_n + maxb >= meilleure_solution2.cardinal;
    }
    return cur_n + maxb >= meilleure_solution.cardinal;



}

solution copy_sol(solution sol){
    solution s;
    s.cardinal = sol.cardinal;
    s.couverture = malloc(sizeof(int) * s.cardinal);
    memcpy(s.couverture,sol.couverture,s.cardinal * sizeof(int));
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
        memcpy(s.couverture,sol.couverture,sol.cardinal * sizeof(int));
        memcpy(s.couverture + sol.cardinal,C,n * sizeof(int));
    }
    return s;
}

solution branchementBorneCouplageInit(Graph *g) {
    solution res = branchementBorneCouplage(g, NULL, 0) ;
    count = 0 ; 
    return res ; 
}

solution branchementBorneCouplage(Graph *g, int *C, int n){
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
    if(testElag(g,n,0)){
        solution s = copy_sol(meilleure_solution);
        free(C);
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
    if(C != NULL){
        free(sol.couverture);
    }
    free(sol_realisable);

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
solution branchementBorneCouplageAmeliore(Graph *g, int *C, int n){
    if(g == NULL || g -> nbAretes == 0){
        solution sol;
        sol.cardinal = n;
        sol.couverture = C;

        if(n < meilleure_solution2.cardinal){
            if(meilleure_solution2.couverture != NULL){
                free(meilleure_solution2.couverture);
            }
            meilleure_solution2 = copy_sol(sol);
        }
        return sol;
    }
    if(testElag(g,n,1)){
        solution s = copy_sol(meilleure_solution2);
        free(C);
        return s;
    }
    int x;
    Graph *h = copieGraph(g);
    int *sol_realisable = algoCouplage(h,&x);
    freeGraph(h);
    solution s;
    s.cardinal = x;
    s.couverture = sol_realisable;
    solution sol = concatene_sol(s,C,n);
    if(sol.cardinal < meilleure_solution2.cardinal){
        if(meilleure_solution2.couverture != NULL){
            free(meilleure_solution2.couverture);
        }
        meilleure_solution2 = copy_sol(sol);
    }
    if(C != NULL){
        free(sol.couverture);
    }
    free(sol_realisable);

    int *arete = uneArete(g);
    int u = arete[0];
    int v = arete[1];
    free(arete);
    
    Graph *gcpy1 = copieGraph(g);
    Graph *gcpy5 = copieGraph(g);
    Graph *g_sans_u = retireSommet(gcpy1,u);
    Graph *g_sans_v = retireSommet(gcpy5,v);
    Graph *gcpy4 = copieGraph(g_sans_u);
    Graph *g_sans_v_u = retireSommet(gcpy4,v);
    solution voisins_u = voisins(g_sans_v,u);
    Graph *gcpy2 = copieGraph(g_sans_v_u);
    Graph *g_sans_v_u_voisins_u = retireEnsembleSommet(gcpy2,voisins_u.couverture,voisins_u.cardinal);

    int *C_u = malloc(sizeof(int) * (n+1));
    int *C_v = malloc(sizeof(int) * (n+1 + voisins_u.cardinal));
    if(C != NULL){
        memcpy(C_u,C,sizeof(int) * n);
        memcpy(C_v,C,sizeof(int) * n);
    }
    C_u[n] = u;
    C_v[n] = v;
    memcpy(C_v + n + 1, voisins_u.couverture,sizeof(int)*voisins_u.cardinal);
    if(C != NULL){
        free(C);
    }
    
    solution branche_u = branchementBorneCouplageAmeliore(g_sans_u,C_u,n+1);
    solution branche_v = branchementBorneCouplageAmeliore(g_sans_v_u_voisins_u,C_v, n+1 + voisins_u.cardinal);


    freeGraph(g_sans_v_u_voisins_u);
    freeGraph(g_sans_u);
    freeGraph(g_sans_v);
    freeGraph(g_sans_v_u);
    free(voisins_u.couverture);

    if(branche_u.cardinal < branche_v.cardinal){
        free(branche_v.couverture);
        return branche_u;
    }
    free(branche_u.couverture);
    return branche_v;
    
}

solution branchementBorneCouplageAmelioreInit(Graph *g) {
    solution res = branchementBorneCouplage(g, NULL, 0) ; 
    count = 0 ; 
    return res ;     
}

solution branchementBorneCouplageAmeliore(Graph *g, int *C, int n){
    //printf("--%d--\n",count++);
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
    freeGraph(h);
    solution s = algoCouplage(h) ;
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
    Graph *gcpy5 = copieGraph(g);
    Graph *g_sans_u = retireSommet(gcpy1,u);
    Graph *g_sans_v = retireSommet(gcpy5,v);
    Graph *gcpy4 = copieGraph(g_sans_u);
    Graph *g_sans_v_u = retireSommet(gcpy4,v);
    solution voisins_u = voisins(g_sans_v,u);
    Graph *gcpy2 = copieGraph(g_sans_v_u);
    Graph *g_sans_v_u_voisins_u = retireEnsembleSommet(gcpy2,voisins_u.couverture,voisins_u.cardinal);
    int *C_u = malloc(sizeof(int) * (n+1));
    int *C_v = malloc(sizeof(int) * (n+1 + voisins_u.cardinal));
    if(C != NULL){
        memcpy(C_u,C,sizeof(int) * n);
        memcpy(C_v,C,sizeof(int) * n);
    }
    C_u[n] = u;
    C_v[n] = v;
    memcpy(C_v + n + 1, voisins_u.couverture,sizeof(int)*voisins_u.cardinal);
    if(C != NULL){
        free(C);
    }
    solution branche_u = branchementBorneCouplageAmeliore(g_sans_u,C_u,n+1);
    solution branche_v = branchementBorneCouplageAmeliore(g_sans_v_u_voisins_u,C_v, n+1 + voisins_u.cardinal);

    freeGraph(g_sans_v_u_voisins_u);

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