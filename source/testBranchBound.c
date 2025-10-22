#include "./header/branchBound.h"
#include <stdio.h>

int main(int argc, char** argv) {
	Graph *g = genereGraphAlea(15, 0.8) ; 
	afficheGraph(g) ; 
	solution s = branchSimplInit(g) ; 
    afficheTab(s.couverture, s.cardinal) ; 
	printf("Fin de fct") ; 
	
	
    return 0 ; 
}