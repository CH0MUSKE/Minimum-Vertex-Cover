#include "./header/branchBound.h"


int main(int argc, char const *argv[]) {
    
    if (argc != 3) {
        printf("Pas assez de parametre : %d, 3 attendu\n", argc) ; 
    }

    Graph *g = lireGraph(argv[1]) ; 
    int mode = atoi(argv[2]) ; 
    solution s ; 
    switch (mode + 1) {
    case 1 :
        s = algoCouplage(g) ; 
        break;

    case 2 : 
        s = algoGlouton(g) ; 
        break; 

    case 3 : 
        s = branchementSimpleInit(g) ; 
        break ; 

    case 4 : 
        s = branchementBorneCouplageInit(g) ; 
        break ; 

    case 5 : 
        s = branchementBorneCouplageAmelioreInit(g) ; 
        break ; 

    case 6 : 
        s = branchementBorneCouplageAmelioreDegMaxInit(g) ; 
        break ; 

    case 7 : 
        s = branchementBorneCouplageAmelioreDegMaxTestDeg1Init(g) ; 
        break ; 

    default:
        printf("Erreur, mode non valide\n") ; 
        break;
    }

    printf("Noeuds de la couverture :") ; 
    afficheTab(s.couverture, s.cardinal) ; 

    return 0;
}
