#include "./header/mesureFonction.h"

int main(int argc, char** argv) {

    /*
    Algo couverture 
    DureeMax : 0.500, TailleMax : 1250
    DureeMax : 1.000, TailleMax : 1600
    DureeMax : 1.500, TailleMax : 1850
    DureeMax : 2.000, TailleMax : 2000
    DureeMax : 2.500, TailleMax : 2200
    DureeMax : 3.000, TailleMax : 2300

    Algo glouton 
    DureeMax : 0.500, TailleMax : 1350
    DureeMax : 1.000, TailleMax : 1700
    DureeMax : 1.500, TailleMax : 1950
    DureeMax : 2.000, TailleMax : 2150
    DureeMax : 2.500, TailleMax : 2300
    DureeMax : 3.000, TailleMax : 2450

    Si on laisse l'algorithme tourner plus longtemps, l'ordi plante donc on va éviter...
    printf("Algorithme de couplage.") ; 
    for (int i = 0 ; i < 7 ; i++) {
        int tMax = tailleMaxGraphe (i/2.0, 0.5, 50, algoCouplage) ; 
        printf("DureeMax : %.3f, TailleMax : %d\n", i/2.0, tMax) ; 
        }
        printf("Algorithme de couverture glouton.") ; 
        for (int i = 0 ; i < 7 ; i++) {
            int tMax = tailleMaxGraphe (i/2.0, 0.5, 50, algoGlouton) ; 
            printf("DureeMax : %.3f, TailleMax : %d\n", i/2.0, tMax) ; 
            }
            */
    
    int nbPoints = 10 ; 
    double *d = tempsMoyenAlgoCouplage(20, nbPoints, 0.2) ; 
    for (int i = 0 ; i < nbPoints ; i++) {
        printf("%d, %.3f\n", (i+1)*(MAXSOMMETS / nbPoints), d[i]) ; 
    }


    printf("Fin d'execution.\n") ; 
    return 0 ; 
}