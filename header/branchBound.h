#include <math.h> 
#include "./header/operationGraph.h"

typedef struct solution{
    int cardinal;
    int *couverture;
}solution;

typedef struct _couverture {
    int *listeSommets ; 
} Couverture ; 

solution branchementSimple(Graph *g, int *C, int n) ; 
solution *copieSolution (solution *s) ; 
int valeurBorne (Graph *G, solution *couverture) ; 