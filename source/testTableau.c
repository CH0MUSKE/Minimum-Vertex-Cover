#include "./header/operationTableau.h"
#include <stdio.h>

int main(int argc, char** argv) {
    int taille = 10 ; 
	int *tab = malloc(sizeof(int) * taille) ; 
	for (int i = 0 ; i < taille ; i++)
	{
		tab[i] = i ; 
	}
    afficheTab(tab, taille) ; 
    int k ; 
    tab = supprimePremierEl(tab, taille, 0, &k) ; 
    tab = supprimePremierEl(tab, taille, 1, &k) ; 
    tab = supprimePremierEl(tab, taille, 9, &k) ; 
    afficheTab(tab, taille - 2) ; 
}