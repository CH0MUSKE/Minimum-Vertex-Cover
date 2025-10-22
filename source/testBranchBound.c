#include "./header/branchBound.h"
#include <stdio.h>

int main(int argc, char** argv) {
	/*
	int taille = 6 ; 
	int *tab = malloc(sizeof(int) * taille) ; 
	for (int i = 0 ; i < taille - 1 ; i++)
	{
		tab[i] = i ; 
		}
		tab[taille - 1] = 9 ; 
		afficheGraph(g) ; 
		g = retireEnsembleSommet(g, tab, taille) ; 
		
	*/
	Graph *g = genereGraphAlea(15, 0.8) ; 
    Graph *gp = copieGraph(g) ; 
	afficheGraph(g) ; 
	solution s = branchSimplInit(g) ; 
    afficheTab(s.couverture, s.cardinal) ; 
    s = branchSimplInit2(gp) ; 
    afficheTab(s.couverture, s.cardinal) ; 
	printf("Fin de fct") ; 
	
	
    return 0 ; 
}