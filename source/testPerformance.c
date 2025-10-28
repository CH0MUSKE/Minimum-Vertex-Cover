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
    int nbIntervalles = 10 ; 
    int pas = 10 ; 
    double p = 0.8 ; 
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
    
    for (int i = 1 ; i < 15 ; i++) {
        
        Graph *g ; 
        
        clock_t start ;
        solution t ;
        clock_t end ;
        double temp = 0 ; 
        for (int k = 0 ; k < nbIntervalles ; k++) {
            g = genereGraphAlea(i*pas, p) ; 
            start = clock() ; 
            t = branchementBorneCouplageAmelioreDegMaxInit(g) ; 
            end = clock() ; 
            free(t.couverture) ;  
            temp += (float)(end - start) / (float) CLOCKS_PER_SEC ; 
            freeGraph(g) ; 
        }
        fprintf(f, "%.3f, %d\n", temp / nbIntervalles, i*pas) ; 
        printf("%d\n", i) ; 

    }
    fclose(f) ; 
    /*
    for (int i = 1 ; i < 70 ; i++) {
        
        Graph *g ; 
        
        solution t1, t2, t3 ;
        double temp = 0 ; 
        
        g = genereGraphAlea(i*pas, p) ; 
        t1 = branchementBorneCouplageAmelioreInit(g) ; 
        t2 = algoCouplage(g) ; 
        t3 = algoGlouton(g) ; 
        
        freeGraph(g) ; 
        free(t1.couverture) ;  
        free(t2.couverture) ;  
        free(t3.couverture) ;  
        
        fprintf(f, "%d, %d, %d, %d\n", i*pas, t1.cardinal, t2.cardinal, t3.cardinal) ; 
        printf("%d\n", i) ; 

    }
    fclose(f) ; 


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