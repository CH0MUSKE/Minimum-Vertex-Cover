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

    double tempsMax = 2.0 ; 
    int nbIntervalles = 10 ; 
    int pas = 50 ; 
    double p = 0.4 ; 
    FILE *f = fopen("data.txt", "w") ; 

	if (argc == 5) {
		tempsMax = atof(argv[1]) ; 
		if (atoi(argv[2]) < 0) {
			nbIntervalles = atoi(argv[2]) ; 
		}
		if (atoi(argv[3]) < 0) {
			pas = atoi(argv[3]) ; 
		}
		if (atof(argv[4]) <= 0.0 && atof(argv[4]) <= 1.0) {
			p = atof(argv[4]) ; 
		}
	}
	
    printf("Test de tailleMax pour algoCouverture avec tempsMax = %f\n", tempsMax) ; 
    for (int i = 0 ; i < nbIntervalles ; i++) {
        printf("%.4f, %d\n",(i + 1.0)*(tempsMax / (double) nbIntervalles), 
        tailleMaxGraphe((i + 1.0)*(tempsMax / (double) nbIntervalles), p, pas, algoCouplage)) ; 
    }
    

    
    
	/*
    printf("Test de tailleMax pour algoGlouton avec tempsMax = %f\n", tempsMax) ; 
    for (int i = 0 ; i < nbIntervalles ; i++) {
        printf("%.4f, %d\n",(i + 1.0)*(tempsMax / (double) nbIntervalles), 
        tailleMaxGraphe((i + 1.0)*(tempsMax / (double) nbIntervalles), p, pas, algoGlouton)) ; 
    }
    printf("Test de tailleMax pour branchementSimpleInit avec tempsMax = %f\n", tempsMax) ; 
    for (int i = 0 ; i < nbIntervalles ; i++) {
        printf("%.4f, %d\n",(i + 1.0)*(tempsMax / (double) nbIntervalles), 
        tailleMaxGraphe((i + 1.0)*(tempsMax / (double) nbIntervalles), p, pas, branchementSimpleInit)) ; 
    }
    
    printf("Test de tailleMax pour branchementBorneCouplageInit avec tempsMax = %f\n", tempsMax) ; 
    for (int i = 0 ; i < nbIntervalles ; i++) {
        printf("%.4f, %d\n",(i + 1.0)*(tempsMax / (double) nbIntervalles), 
        tailleMaxGraphe((i + 1.0)*(tempsMax / (double) nbIntervalles), p, pas, branchementBorneCouplageInit)) ; 
    }
    
    printf("Test de tailleMax pour branchementBorneCouplageAmelioreInit avec tempsMax = %f\n", tempsMax) ; 
    for (int i = 0 ; i < nbIntervalles ; i++) {
        printf("%.4f, %d\n",(i + 1.0)*(tempsMax / (double) nbIntervalles), 
        tailleMaxGraphe((i + 1.0)*(tempsMax / (double) nbIntervalles), p, pas, branchementBorneCouplageAmelioreInit)) ; 
    }
	*/

    /* 
    double *d = tempsMoyenAlgo(10, 3, 0.4, 20, branchementSimpleInit) ; 
    ecrireTempsMoyen(d, 3, 20, f) ; 
    printf("======================\n") ; 
    d = tempsMoyenAlgo(10, 5, 0.4, 100, branchementBorneCouplageInit) ; 
    ecrireTempsMoyen(d, 5, 100, f) ; 
    */


    printf("Fin d'execution.\n") ; 
    return 0 ; 
}