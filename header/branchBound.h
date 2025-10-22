#include <math.h> 
#include "./header/operationGraph.h"
#include <limits.h>
#include <math.h>

typedef struct solution{
    int cardinal;
    int *couverture;
}solution;

 

solution branchementSimple(Graph *g, int *C, int n) ; 
solution branchementBorneCouplage(Graph *g, int *C, int n) ;
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
int valeurBorne (Graph *G, solution *couverture) ; 
