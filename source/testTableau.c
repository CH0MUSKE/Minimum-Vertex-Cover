#include "./header/operationTableau.h"
#include <stdio.h>

int main(int argc, char** argv) {    

    int taille = 10 ; 
    int k ; 
    int *tab = malloc(sizeof(int) * taille) ; 
    for (int j = 0 ; j < taille ; j++)
    {
        tab[j] = j ; 
    }   
    int *tab2 = copieTab(tab, taille) ; 
    tab2 = supprimePremierEl(tab2, taille, 6, &k) ; 
    afficheTab(tab2, taille - 1) ; 
    

    int *tab3 = copieTab(tab, taille) ; 
    tab3 = retireValTabIndex(tab3, taille - 1, 2, &k) ; 
    afficheTab(tab3, taille - 1) ; 

    int *tab4 = malloc(sizeof(int) * (taille * 2)) ; 
    for (int j = 0 ; j < taille ; j++)
    {
        tab[j] = j ; 
    }   
    for (int j = 0 ; j < taille ; j++) {
        tab[j + taille] = -1 ; 
    }
    tab4 = raccourcitListe(tab4, taille * 2, &k) ; 
    afficheTab(tab4, k) ; 



    free(tab) ; 
    free(tab2) ; 
    free(tab3) ; 
    free(tab4) ; 

    return 0 ; 
}