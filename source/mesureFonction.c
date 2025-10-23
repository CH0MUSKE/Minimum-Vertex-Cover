#include "./header/mesureFonction.h"


int tailleMaxGraphe (double tempsMax, float p, int pas, solution (*algo) (Graph*)) {
    float temps = 0.0 ; 
    float tempsEcroule = 0.0 ; 
    Graph *g = NULL ; 
    if (pas < 0) {
        pas = 1 ; 
    }
    int i = pas ; 
    while(temps < tempsMax && i < 10000 && tempsEcroule < 60) {
        g = genereGraphAlea(i, p) ; 
        
        clock_t start = clock();
        solution t = algo(g) ; 
        clock_t end = clock();

        free(t.couverture) ;  
        temps = (float)(end - start) / (float) CLOCKS_PER_SEC;
        tempsEcroule += temps ; 
        freeGraph(g) ; 
        i += pas ; 
    }
    return i ; 
}

double *tempsMoyenAlgo(int nbGraphes, int nbPoints, double p, solution (*algo) (Graph*)) {
    double *res = malloc(sizeof(double) * nbPoints) ; 
    int nbSommets = (int) (MAXSOMMETS / nbPoints) ; 
    Graph *g ; 
    for (int i = 0 ; i < nbPoints ; i++) {
        res[i] = 0 ; 
        for (int j = 0 ; j < nbGraphes ; j++) {
            g = genereGraphAlea(nbSommets, p) ; 
            
            clock_t start = clock();
            solution t = algo(g) ; 
            clock_t end = clock();

            free(t.couverture) ; 
            res[i] += (float)(end - start) / (float) CLOCKS_PER_SEC;
            
            freeGraph(g) ; 
        }
        res[i] = res[i] / nbGraphes ; 
        nbSommets += (MAXSOMMETS / nbPoints) ; 
    }
    return res ;     
}
