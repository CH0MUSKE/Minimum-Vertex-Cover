#include "./header/operationGraph.h"
#include <stdio.h>

int main(int argc, char** argv) {
	Graph *g = genereGraphAlea(10, (float) 1) ; 
	int taille = 6 ; 
	int *tab = malloc(sizeof(int) * taille) ; 
	for (int i = 0 ; i < taille - 1 ; i++)
	{
		tab[i] = i ; 
	}
	tab[taille - 1] = 9 ; 
	afficheGraph(g) ; 
	g = retireEnsembleSommet(g, tab, taille) ; 
	/*
	
	*/
    return 0 ; 
}