#include <stdlib.h>
#include <stdio.h>

/*
Effectue une recherche dichotomique de e dans tab 
Renvoie -1 si e n'est pas dans tab 
*/
int rechercheDich (int *tab, int len, int e) ; 

// Affiche le tableau passé en paramètre
void afficheTab (int *tab, int len) ; 

// Copie le tableau passé en paramètre, renvoie NULL si le tableau est de longueur vide ou est un pointeur NULL  
int *copieTab (int *tab, int len) ; 

/*
Supprime la première occurence de e dans tab, posElt valant -1 si e n'est pas dans tab
Détruit la liste passé en paramètre 
*/ 
int *supprimePremierEl (int* tab, int len, int e, int *posElt) ; 

/*
Retire la valeur située à la position index, estSupprime vaut 1 si on a pas pu 
supprimer, 0 sinon 
Détruit la liste passé en paramètre 
*/
int *retireValTabIndex(int *tab, int len, int index, int *estSupprime) ; 

// Cherche e dans tab par recherche itérative 
int rechercheIter (int *tab, int len, int e) ; 

// Raccourcit le tableau tab passé en paramètre, supposant que les cases vides sont 
// marqués par -1
// Détruit la liste passé en paramètre 
int *raccourcitListe (int *tab, int len, int *newLen) ; 