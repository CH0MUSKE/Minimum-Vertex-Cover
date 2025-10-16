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
    afficheTab(tab, taille - 2) ; 
    

    for (int i = 0 ; i < 1000 ; i++) {
        int taille = 1000000 ; 
        int *tab = malloc(sizeof(int) * taille) ; 
        for (int j = 0 ; j < taille ; j++)
        {
            tab[j] = j ; 
        }   
        tab = supprimePremierEl(tab, taille, 9, &k) ; 
        free(tab) ; 
        printf("========== %d\n", i) ; 
    }

    return 0 ; 
}