#include "./header/operationGraph.h"
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
	for (int i = 0; i <200 ; i++){
		Graph *g = genereGraphAlea(1000, (float) 0.25) ; 
		Graph *gp = copieGraph(g) ; 
		int taille1, taille2 ; 
		printf("===================== %d\n", i) ; 
		if (i == 11) {
			//afficheGraph(g) ; 
		}
		int *tab1 = algoCouplage(g, &taille1) ; 
		printf("HI====\n") ; 
		int *tab2 = algoGlouton(gp, &taille2) ; 
		/*
		afficheGraph(g) ; 
		printf("Résultats :\n Non-glouton :\n") ; 
		afficheTab(tab1, taille1) ; 
		printf("Glouton : \n") ; 
		afficheTab(tab2, taille2) ; 
		*/

		libereGraph(g) ; 
		libereGraph(gp) ; 
		free(tab1) ; 
		free(tab2) ; 
		
	/* code */
	}
	printf("Fin de fct") ; 
	
    return 0 ; 
}