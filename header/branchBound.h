#include <math.h> 
#include "./header/operationGraph.h"
#include <limits.h>
#include <math.h>


/*
Applique l'algorithme de branchement, sachant que C représente les sommets déjà 
retirés du graphe et n la taille du tableau des sommets retirés
*/ 
solution branchementSimple(Graph *g, int *C, int n) ; 
/*
Applique l'algorithme de branchement avec borne, 
sachant que C représente les sommets déjà retirés du graphe et 
n la taille du tableau des sommets retirés
*/
solution branchementBorneCouplage(Graph *g, int *C, int n) ;

solution branchBorneCouplInit(Graph *g) ;
solution branchSimplInit (Graph *G) ; 



typedef struct _pile {
    solution *s ; 
    struct _pile *suiv ; 
} Pile ; 


// Empile solution dans la pile, ne détruit pas solution
Pile *empile (Pile *p, solution *s) ; 

// Empile solution dans la pile, détruit l'élement 
Pile *depile (Pile *p, Pile **el) ; 

//
Pile *creeElPile (solution *s) ; 

void liberePile (Pile *p) ; 

void libereElPile (Pile *p) ; 

solution branchementSimple(Graph *g, int *C, int n) ; 
solution *copieSolution (solution *s) ; 

