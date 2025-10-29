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

double *tempsMoyenAlgo(int nbGraphes, int nbPoints, double p, int maxSommets, solution (*algo) (Graph*)) {
    double *res = malloc(sizeof(double) * nbPoints) ; 
    int nbSommets = (int) (maxSommets / nbPoints) ; 
    Graph *g ; 
    for (int i = 0 ; i < nbPoints ; i++) {
        res[i] = 0 ; 
        for (int j = 0 ; j < nbGraphes ; j++) {
            g = genereGraphAlea(nbSommets, 1/sqrt(nbSommets)) ; 
            
            clock_t start = clock();
            solution t = algo(g) ; 
            clock_t end = clock();
            
            free(t.couverture) ; 
            res[i] += (float)(end - start) / (float) CLOCKS_PER_SEC;
            
            freeGraph(g) ; 
        }
        res[i] = res[i] / nbGraphes ; 
        nbSommets += (maxSommets / nbPoints) ; 
        printf("Tour : %d\n", i) ; 
    }
    return res ;     
}

int ecrireTempsMoyen (double *listeTemps, int nbPoints, int maxSommets, FILE *f) {
    int u = (maxSommets / nbPoints) ; 
    int acc = u ; 
    for (int i = 0 ; i < nbPoints ; i++) {
        fprintf(f, "%d, %.4f\n", acc, listeTemps[i]) ; 
        acc += u ; 
    }
    fprintf(f, "==\n") ; 
    return 0 ; 
}
