#include <math.h> 
#include "./header/operationGraph.h"
#include <limits.h>
#include <math.h>


/*
Applique l'algorithme de branchement, sachant que C représente les sommets déjà 
retirés du graphe et n la taille du tableau des sommets retirés
*/ 
solution branchementSimple(Graph *g, int *C, int n) ; 
solution branchementSimpleInit(Graph *g) ;

int testElag(Graph *g, int cur_n, int ameliore) ; 
/*
Applique l'algorithme de branchement avec borne, 
sachant que C représente les sommets déjà retirés du graphe et 
n la taille du tableau des sommets retirés
*/
solution branchementBorneCouplage(Graph *g, int *C, int n) ;
solution branchementBorneCouplageInit (Graph *G) ; 


solution branchementBorneCouplageAmeliore(Graph *g, int *C, int n) ; 
solution branchementBorneCouplageAmelioreInit (Graph *g) ; 



solution *copieSolution (solution *s) ; 

