#include "./header/operationGraph.h"
#include <stdio.h>
#define MAXBUFF 1000

Graph *altLireGraph(FILE *f) {

	char buff [MAXBUFF] ;  
    int x ; 
	
	// Nombre de sommets 
	if (fgets(buff, MAXBUFF, f) == NULL) {
		printf("Erreur=\n") ; 
	}
	
	// valeur 
	fgets(buff, MAXBUFF, f) ; 
	if (sscanf(buff, "%d\n", &x) != 1) {
		printf("Erreur\n") ; 
	}
	
	// Sommets 
	fgets(buff, MAXBUFF, f) ; 
	Graph *res = creeGraph(x) ; 
	res->tabSommets = malloc(sizeof(int) * x) ; 
	res->degreSommet = malloc(sizeof(int) * x) ; 
	for (int i = 0 ; i < res->nbSommets ; i++) {
		// valeur
		fgets(buff, MAXBUFF, f) ; 
		sscanf(buff, "%d\n", &x) ; 
		res->tabSommets[i] = x ; 
		res->degreSommet[i] = res->nbSommets - 1 ; 
	}
	
	// Nombre d'aretes 
	fgets(buff, MAXBUFF, f) ; 
	
	// valeur 
	fgets(buff, MAXBUFF, f) ; 
	sscanf(buff, "%d\n", &x) ; 
	
	res->nbAretes = x ; 
	res->tabAdjacence = malloc(sizeof(int*) * res->nbSommets) ; 
	
	fgets(buff, MAXBUFF, f) ; 
	
	
	for (int i = 0 ; i < res->nbSommets ; i++) {
		res->tabAdjacence[i] = malloc(sizeof(int) * (res->nbSommets - 1)) ; 
		for (int j = 0 ; j < res->nbSommets - 1 ; j++) {
			res->tabAdjacence[i][j] = -1 ; 
		}
	}

	
	// Tableau des longeurs courantes des listes d'adjacence 
	int *currentLens = malloc(sizeof(int) * res->nbSommets) ; 
	for (int i = 0 ; i < res->nbSommets ; i++) {
		currentLens[i] = 0 ; 
	}

	int y ; 
	for (int i = 0 ; i < res->nbAretes ; i++) {
		fgets(buff, MAXBUFF, f) ; 
		sscanf(buff, "%d %d\n", &x, &y) ; 
		res->tabAdjacence[x][currentLens[x]] = y ;
		currentLens[x] += 1 ; 
		res->tabAdjacence[y][currentLens[y]] = x ; 
		currentLens[y] += 1 ; 
	}
	printf("") ; 
	for (int i = 0 ; i < res->nbSommets ; i++) {
		res->tabAdjacence[i] = raccourcitListe(res->tabAdjacence[i], res->degreSommet[i] - 1, &x) ; 
		res->degreSommet[i] = x ; 
	}

    return res ; 
}


int main(int argc, char** argv) {
	/*
	FILE *f = fopen("exempleinstance.txt", "r") ; 
	if (f == NULL) {
		printf("TTK\n") ; 
	}
	Graph *g = altLireGraph(f) ; 
	afficheGraph(g) ; 

	solution s = algoGlouton(g) ; 
	afficheTab(s.couverture, s.cardinal) ; 
	*/

	

	printf("Fin de fct") ; 	
	
    return 0 ; 
}