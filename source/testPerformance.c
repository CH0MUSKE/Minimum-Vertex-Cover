#include "./header/mesureFonction.h"

int main(int argc, char** argv) {

    /*
    Nombre maximum de sommets par type d'algorithme 
    Pour algorithme non-glouton, avec un pas de 25 :
    1 sec, p = 0.8 => 1250
    1 sec, p = 0.6 => 1425
    1 sec, p = 0.4 => 1750
    1 sec, p = 0.2 => 2325

    Pour algorithme glouton, avec un pas de 25 : 
    1 sec, p = 0.8 => 1250
    1 sec, p = 0.6 => 1350
    1 sec, p = 0.4 => 1725
    1 sec, p = 0.2 => 2325

    Sachant algoNonGlouton, pas de 50 : 
    DureeMax : 0.000, TailleMax : 50
    DureeMax : 0.500, TailleMax : 1300
    DureeMax : 1.000, TailleMax : 1600
    DureeMax : 1.500, TailleMax : 1550

    Si on laisse l'algorithme tourner plus longtemps, l'ordi plante donc on va éviter...
    int nbPoints = 5 ; 
    double *d = tempsMoyenNonGlouton(10, nbPoints, 1.0) ; 
    for (int i = 0 ; i < nbPoints ; i++) {
        printf("%d, %.3f\n", i*(MAXSOMMETS / nbPoints), d[i]) ; 
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