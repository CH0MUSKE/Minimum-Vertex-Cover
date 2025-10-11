#include <stdlib.h>
#include <stdio.h>

int rechercheDich (int *tab, int len, int e) ; 
void afficheTab (int *tab, int len) ; 
int *copieTab (int *tab, int len) ; 
int *supprimePremierEl (int* tab, int len, int e, int *posElt) ; 
int *retireValTabIndex(int *tab, int len, int index, int *estSupprime) ; 
int rechercheIter (int *tab, int len, int e) ; 
int *raccourcitListe (int *tab, int len, int *newLen) ; 