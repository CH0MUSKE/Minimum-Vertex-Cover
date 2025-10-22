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
	/*
	On considère que ces valeurs forment les paramètres par défaut de nos tests 
	*/		
	double tempsMax = 3 ; 
	int nbIntervalles = 15 ; 
	int pas = 25 ; 
	double p = 0.3 ; 

    if (argc == 5) {
		argv ++ ; 
		tempsMax = atof(*argv) ; 
		argv ++ ; 
		nbIntervalles = atoi(*argv) ; 
		argv ++ ; 
		pas = atoi(*argv) ; 
		argv ++ ; 
		p = atof(*argv) ; 
    }

	printf("Parametres globaux : \ntempsMax = %.3f\nnbIntervales = %d\npas = %d\np = %.3f\n", tempsMax, nbIntervalles, pas, p) ; 

	/*

	printf("Test de tailleMax pour Branche\n") ; 
	for (int i = 0 ; i < nbIntervalles ; i++) {
		printf("%.4f, %d\n",(i + 1.0)*(tempsMax / (double) nbIntervalles), tailleMaxGraphe((i + 1.0)*(tempsMax / (double) nbIntervalles), p, pas, F1)) ; 
	}
	printf("======================\n") ; 

	printf("Test de tailleMax pour BrancheBoundV1\n") ; 
	for (int i = 0 ; i < nbIntervalles ; i++) {
		printf("%.4f, %d\n",(i + 1.0)*(tempsMax / (double) nbIntervalles), tailleMaxGraphe((i + 1.0)*(tempsMax / (double) nbIntervalles), p, pas, F2)) ; 
	}
	printf("======================\n") ; 

	printf("Test de tailleMax pour BrancheBoundV2\n") ; 
	for (int i = 0 ; i < nbIntervalles ; i++) {
		printf("%.4f, %d\n",(i + 1.0)*(tempsMax / (double) nbIntervalles), tailleMaxGraphe((i + 1.0)*(tempsMax / (double) nbIntervalles), p, pas, F3)) ; 
	}
	printf("======================\n") ; 
	
	*/
    printf("Test de tailleMax pour AlgoCouplage\n") ; 
    for (int i = 0 ; i < nbIntervalles ; i++) {
        printf("%.4f, %d\n",(i + 1.0)*(tempsMax / (double) nbIntervalles), tailleMaxGraphe((i + 1.0)*(tempsMax / (double) nbIntervalles), p, pas, algoCouplage)) ; 
    }
    printf("======================\n") ; 
    
	printf("Test de tailleMax pour AlgoGlouton\n") ; 
    for (int i = 0 ; i < nbIntervalles ; i++) {
        printf("%.4f, %d\n",(i + 1.0)*(tempsMax / (double) nbIntervalles), tailleMaxGraphe((i + 1.0)*(tempsMax / (double) nbIntervalles), p, pas, algoGlouton)) ; 
    }
    printf("======================\n") ; 

    printf("Fin d'execution.\n") ; 
    return 0 ; 
}