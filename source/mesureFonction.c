#include "./header/mesureFonction.h"


int tailleMaxGraphe (double tempsMax, float p, int pas) {
    float temps = 0.0 ; 
    float tempsEcroule = 0.0 ; 
    Graph *g = NULL ; 
    if (pas < 0) {
        pas = 1 ; 
    }
    int i = pas ; 
    int u ; 
    while(temps < tempsMax && i < 10000 && tempsEcroule < 180) {
        g = genereGraphAlea(i, p) ; 
        
        clock_t start = clock();
        int *t = algoGlouton(g, &u) ; 
        clock_t end = clock();

        free(t) ; 
        temps = (float)(end - start) / (float) CLOCKS_PER_SEC;
        tempsEcroule += temps ; 
        libereGraph(g) ; 
        i += pas ; 
        if (!(i % (pas * 100))){
            printf("Nb de sommets : %d\n", i) ;             
        }
    }
    return i ; 
}

double *tempsMoyenNonGlouton (int nbGraphes, int nbPoints, double p) {
    double *res = malloc(sizeof(double) * nbPoints) ; 
    int nbSommets = (int) (MAXSOMMETS / nbPoints) ; 
    Graph *g ; 
    int u ; 
    for (int i = 0 ; i < nbPoints ; i++) {
        res[i] = 0 ; 
        printf("Takam %d\n", i) ; 
        for (int j = 0 ; j < nbGraphes ; j++) {
            g = genereGraphAlea(nbSommets, p) ; 
            
            clock_t start = clock();
            int *t = algoGlouton(g, &u) ;             
            clock_t end = clock();

            res[i] += (float)(end - start) / (float) CLOCKS_PER_SEC;
            libereGraph(g) ; 
        }
        res[i] = res[i] / nbGraphes ; 
        nbSommets += (MAXSOMMETS / nbPoints) ; 
    }
    return res ;     
}