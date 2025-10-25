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

    */

    double tempsMax = 1.0 ; 
    int nbIntervalles = 5 ; 
    int pas = 50 ; 
    double p = 0.4 ; 
    printf("Test de tailleMax pour AlgoCouverture avec tempsMax = %f\n", tempsMax) ; 
    for (int i = 0 ; i < nbIntervalles ; i++) {
        printf("%.4f, %d\n",(i + 1.0)*(tempsMax / (double) nbIntervalles), tailleMaxGraphe((i + 1.0)*(tempsMax / (double) nbIntervalles), p, pas, algoCouplage)) ; 
    }
    printf("======================\n") ; 
    



    printf("Fin d'execution.\n") ; 
    return 0 ; 
}