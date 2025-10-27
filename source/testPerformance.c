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
    double p = 0.2 ; 
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
	
    for (int i = 1 ; i < 100 ; i++) {

        Graph *g = genereGraphAlea(i*pas, p) ; 
    
        clock_t start = clock();
        solution t = branchementBorneCouplageInit(g) ; 
        clock_t end = clock();
    
        free(t.couverture) ;  
        double temps = (float)(end - start) / (float) CLOCKS_PER_SEC;
        if (temps > tempsMax) {
            break;
        }
        */
    /*for (int i = 0 ; i < 4 ; i++) {
        int tMax = tailleMaxGraphe (((double) i)/2.0, 0.5, 50, algoCouplage) ; 
        printf("DureeMax : %.3f, TailleMax : %d\n", ((double) i)/2.0, tMax) ; 
    }*/
    Graph *g = genereGraphAlea(25,0.2);

    solution s = branchementBorneCouplage(g, NULL, 0);

    solution so = branchementBorneCouplageAmeliore(g, NULL, 0);

    solution sol = branchementSimple(g,NULL,0);


    printf("%d %d %d\n", s.cardinal, so.cardinal, sol.cardinal);

    freeGraph(g);
    return 0;
}