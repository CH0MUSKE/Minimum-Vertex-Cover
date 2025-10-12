#include "./header/operationGraph.h"
#include <stdio.h>

int main(int argc, char** argv) {
	Graph *g = genereGraphAlea(2, (float) 1) ; 
	int *tab = malloc(sizeof(int) * 3) ; 
	tab[0] = 0 ; 
	tab[1] = 1 ; 
	tab[2] = 5 ; 
	Graph *gp  ; 
	gp = retireEnsembleSommet(g, tab, 3) ; 
	afficheGraph(gp) ; 
	/*
	gp = retireEnsembleSommet(g, tab, 3)  ; 
    
	
	int taille = 5 ; 
	int *tab = malloc(sizeof(int) * taille) ; 
	for (int i = 0 ; i < taille ; i++)
	{
		tab[i] = i ; 
	}
	afficheTab(tab, taille) ; 
	int *t ; 
	int *k = retireValTabIndex(tab, taille, 0, t) ; 
	printf("%d\n", k) ; 
	afficheTab(k, taille) ; 
	printf("--------------------\n") ; 
	*/
    return 0 ; 
}