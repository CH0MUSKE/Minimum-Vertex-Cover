#include "./header/branchBound.h" 

solution meilleure_solution = {INT_MAX, NULL};

int count = 0;

solution branchementSimpleInit (Graph *G) {
    return branchementSimple(G, NULL, 0) ;    
}

solution branchementSimple(Graph *g, int *C, int n){

    if(g -> nbAretes == 0){
        solution sol;
        sol.cardinal = n;
        sol.couverture = copieTab(C,n);
        return sol;
    }
    int *arete = uneArete(g);
    int u = arete[0];
    int v = arete[1];
    free(arete);
    Graph *g_sans_u = retireSommet(g,u);
    Graph *g_sans_v = retireSommet(g,v);
    int *C_u = malloc(sizeof(int) * (n+1));
    int *C_v = malloc(sizeof(int) * (n+1));
    if(C != NULL){
        memcpy(C_u,C,sizeof(int) * n);
        memcpy(C_v,C,sizeof(int) * n);
    }
    C_u[n] = u;
    C_v[n] = v;

    solution branche_u = branchementSimple(g_sans_u,C_u,n+1);
    solution branche_v = branchementSimple(g_sans_v,C_v, n+1);

    freeGraph(g_sans_u);
    freeGraph(g_sans_v);
    free(C_u);
    free(C_v);

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
    meilleure_solution.cardinal = INT_MAX;
    if(meilleure_solution.couverture){
        free(meilleure_solution.couverture);
        meilleure_solution.couverture = NULL;
    }
    return res ; 
}

solution branchementBorneCouplage(Graph *g, int *C, int n){
    
    /*
    Si le graphe ne contient aucune arête ou bien est vide, on 
    considère que l'on a une solution optimale
    */
    if(g == NULL || g -> nbAretes == 0){
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
    /*
    Si on ne respecte pas la borne inf, on élague 
    */
    if(testElag(g,n)){
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
    free(s.couverture);

    int *arete = uneArete(g);
    int u = arete[0];
    int v = arete[1];
    free(arete);
    Graph *g_sans_u = retireSommet(g,u);
    Graph *g_sans_v = retireSommet(g,v);
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

        if(n < meilleure_solution.cardinal){
            if(meilleure_solution.couverture != NULL){
                free(meilleure_solution.couverture);
            }
            meilleure_solution = copy_sol(sol);
        }
        return sol;
    }
    if(testElag(g,n)){
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
    free(s.couverture);

    int *arete = uneArete(g);
    int u = arete[0];
    int v = arete[1];
    free(arete);
    

    Graph *g_sans_u = retireSommet(g,u);
    Graph *g_sans_v = retireSommet(g,v);
    Graph *g_sans_v_u = retireSommet(g_sans_u,v);
    solution voisins_u = voisins(g_sans_v,u);

    Graph *g_sans_v_u_voisins_u = retireEnsembleSommet(g_sans_v_u,voisins_u.couverture,voisins_u.cardinal);

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
    solution res = branchementBorneCouplageAmeliore(g, NULL, 0) ; 
    count = 0 ; 
    meilleure_solution.cardinal = INT_MAX;
    if(meilleure_solution.couverture){
        free(meilleure_solution.couverture);
        meilleure_solution.couverture = NULL;
    }
    return res ;     
}

solution branchementBorneCouplageAmelioreDegMax(Graph *g, int *C, int n){
    if(g == NULL || g -> nbAretes == 0){
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
    free(s.couverture);

    int indexMax = indexSommetDegMax(g);
    int u = g->tabSommets[indexMax];
    int v = g ->tabAdjacence[indexMax][0];
    


    Graph *g_sans_u = retireSommet(g,u);
    Graph *g_sans_v = retireSommet(g,v);
    
    Graph *g_sans_v_u = retireSommet(g_sans_u,v);
    solution voisins_u = voisins(g_sans_v,u);
    
    Graph *g_sans_v_u_voisins_u = retireEnsembleSommet(g_sans_v_u,voisins_u.couverture,voisins_u.cardinal);

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
    
    solution branche_u = branchementBorneCouplageAmelioreDegMax(g_sans_u,C_u,n+1);
    solution branche_v = branchementBorneCouplageAmelioreDegMax(g_sans_v_u_voisins_u,C_v, n+1 + voisins_u.cardinal);


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

solution branchementBorneCouplageAmelioreDegMaxInit(Graph *g) {
    solution res = branchementBorneCouplageAmelioreDegMax(g, NULL, 0) ; 
    count = 0 ; 
    meilleure_solution.cardinal = INT_MAX;
    if(meilleure_solution.couverture){
        free(meilleure_solution.couverture);
        meilleure_solution.couverture = NULL;
    }
    return res ;     
}

Reduction reductionDeg1Graph(Graph *g){
    int flag = 1;
    Reduction r;
    r.graph = NULL;
    r.sol.cardinal = 0;
    r.sol.couverture = NULL;
    Graph *h = copieGraph(g);
    if(h == NULL) return r;
    int n = 0;
    int *couverture = malloc(sizeof(int) * g -> nbSommets);
    while(flag && h){
        flag = 0;
        for(int i = 0; i < h->nbSommets; i++){
            if(h->degreSommet[i] == 1){
                couverture[n++] = h ->tabAdjacence[i][0];
                int tab[] = {h -> tabSommets[i], h -> tabAdjacence[i][0]};
                Graph *tmp = retireEnsembleSommet(h,tab,2);
                freeGraph(h);
                h = tmp;
                flag = 1;
                break;
            }
        }
    }

    int *couverture_bonne_taille = NULL;
    if (n > 0) {
        couverture_bonne_taille = malloc(sizeof(int) * n);
        memcpy(couverture_bonne_taille, couverture, n * sizeof(int));
    }
    free(couverture);
    r.graph = h;
    r.sol.cardinal = n;
    r.sol.couverture = couverture_bonne_taille;
    return r;
}

solution branchementBorneCouplageAmelioreDegMaxTestDeg1(Graph *g0, int *C0, int n0){
    Reduction r = reductionDeg1Graph(g0);
    Graph *g = r.graph;
    int n = r.sol.cardinal + n0;
    int * C = malloc(sizeof(int) * n);
    memcpy(C,C0,n0 * sizeof(int));
    memcpy(C + n0,r.sol.couverture,r.sol.cardinal * sizeof(int));
    if(r.sol.couverture)free(r.sol.couverture);
    if(g == NULL || g -> nbAretes == 0){
        solution sol;
        sol.cardinal = n;
        sol.couverture = copieTab(C,n);

        if(n < meilleure_solution.cardinal){
            if(meilleure_solution.couverture != NULL){
                free(meilleure_solution.couverture);
            }
            meilleure_solution = copy_sol(sol);
        }
        freeGraph(g);
        if(C)free(C);
        return sol;
    }
    if(testElag(g,n)){
        solution s = copy_sol(meilleure_solution);
        freeGraph(g);
        if(C)free(C);
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
    if(C)free(sol.couverture);

    free(s.couverture);

    int indexMax = indexSommetDegMax(g);
    int u = g->tabSommets[indexMax];
    int v = g ->tabAdjacence[indexMax][0];
    


    Graph *g_sans_u = retireSommet(g,u);
    Graph *g_sans_v = retireSommet(g,v);
    
    Graph *g_sans_v_u = retireSommet(g_sans_u,v);
    solution voisins_u = voisins(g_sans_v,u);
    
    Graph *g_sans_v_u_voisins_u = retireEnsembleSommet(g_sans_v_u,voisins_u.couverture,voisins_u.cardinal);

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
    
    solution branche_u = branchementBorneCouplageAmelioreDegMaxTestDeg1(g_sans_u,C_u,n+1);
    solution branche_v = branchementBorneCouplageAmelioreDegMaxTestDeg1(g_sans_v_u_voisins_u,C_v, n+1 + voisins_u.cardinal);


    freeGraph(g_sans_v_u_voisins_u);
    freeGraph(g_sans_u);
    freeGraph(g_sans_v);
    freeGraph(g_sans_v_u);
    freeGraph(g);
    free(voisins_u.couverture);
    free(C_u);
    free(C_v);

    if(branche_u.cardinal < branche_v.cardinal){
        free(branche_v.couverture);
        return branche_u;
    }
    free(branche_u.couverture);
    return branche_v;
    
}

solution branchementBorneCouplageAmelioreDegMaxTestDeg1Init(Graph *g) {
    solution res = branchementBorneCouplageAmelioreDegMaxTestDeg1(g, NULL, 0) ; 
    count = 0 ; 
    meilleure_solution.cardinal = INT_MAX;
    if(meilleure_solution.couverture){
        free(meilleure_solution.couverture);
        meilleure_solution.couverture = NULL;
    }
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