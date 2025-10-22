#include "./header/operationGraph.h"
#include <limits.h>
#include <math.h>


typedef struct solution{
    int cardinal;
    int *couverture;
}solution;

 

solution branchementSimple(Graph *g, int *C, int n) ; 
solution branchementBorneCouplage(Graph *g, int *C, int n) ;