#include "./header/operationGraph.h"
#include <stdio.h>

int main(int argc, char** argv) {
	Graph *g = genereGraphAlea(7, (float) 1) ; 
	afficheGraph(g) ; 
	Graph *gp = retireSommet(g, 1) ; 
	afficheGraph(gp) ; 
	gp = retireSommet(gp, 1) ; 
	afficheGraph(gp) ;
	/*
	int *tab = malloc(sizeof(int) * 5) ; 
	for (int i = 0 ; i < 5 ; i++)
	{
		tab[i] = i ; 
	}
	afficheTab(tab, 5) ; 
	int *t ; 
	int *k = retireValTabIndex(tab, 5, 2, t) ; 
	afficheTab(k, 5) ; 
	*/
    
    return 0 ; 
}