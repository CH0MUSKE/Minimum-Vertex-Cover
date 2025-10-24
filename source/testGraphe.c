#include "./header/operationGraph.h"
#include <stdio.h>

int main(int argc, char** argv) {
	Graph *g = genereGraphAlea(4, 0.1) ; 
	afficheGraph(g) ; 
	solution s = voisins(g, 1) ; 
	afficheTab(s.couverture, s.cardinal) ; 

	printf("Fin de fct") ; 	
	
    return 0 ; 
}