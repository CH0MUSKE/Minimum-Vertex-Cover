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
    int nbIntervalles = 20 ; 
    int pas = 20 ; 
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
    for (int i = 1 ; i < 70 ; i++) {
        
        Graph *g ; 
        
        clock_t start ;
        solution t ;
        clock_t end ;
        double temp = 0 ; 
        for (int k = 0 ; k < nbIntervalles ; k++) {
            g = genereGraphAlea(i*pas, p) ; 
            start = clock() ; 
            t = branchementBorneCouplageInit(g) ; 
            end = clock() ; 
            free(t.couverture) ;  
            temp += (float)(end - start) / (float) CLOCKS_PER_SEC ; 
            freeGraph(g) ; 
        }
        fprintf(f, "%.3f, %d\n", temp / nbIntervalles, i*pas) ; 
        printf("%d\n", i) ; 
        /*
        if (temp/nbIntervalles > tempsMax) {
            break;
        }
        
        */
    }
    fclose(f) ; 
    /*
    printf("Test de tailleMax pour algoGlouton avec tempsMax = %f\n", tempsMax) ; 
    for (int i = 0 ; i < nbIntervalles ; i++) {
        printf("%.4f, %d\n",(i + 1.0)*(tempsMax / (double) nbIntervalles), 
        tailleMaxGraphe((i + 1.0)*(tempsMax / (double) nbIntervalles), p, pas, branchementBorneCouplageInit)) ; 
    }
    
    Graph *g = genereGraphAlea(20,0.2);
    printf("+++++\n") ; 
    solution s = branchementBorneCouplageInit(g);

    solution so = branchementBorneCouplageAmelioreInit(g);

    solution sol = branchementSimpleInit(g);


    printf("%d %d %d\n", s.cardinal, so.cardinal, sol.cardinal);
    freeGraph(g);
    */
    printf("FinAlgo\n") ; 
    return 0;
}