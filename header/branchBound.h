#include "./header/operationGraph.h"

typedef struct solution{
    int cardinal;
    int *couverture;
}solution;

typedef struct _couverture {
    int *listeSommets ; 
} Couverture ; 

solution branchementSimple(Graph *g, int *C, int n) ; 