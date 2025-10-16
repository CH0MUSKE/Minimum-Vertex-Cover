#include <time.h>
#include "./header/operationGraph.h"
// On définit cette constante pour un nombre raisonnable de sommets dans un graphe
#define MAXSOMMETS 100 

/*
Mesure le nombre maximum de sommets possibles dans un graphe généré aléatoirement
avec une proba de p pour les arêtes pour que le traitement 
par la fonction algo soit complété dans un temps inférieur à tempsMax.
Pour simplifier le calcul on fait cette mesure avec un pas donné, et 
le temps total ne peut pas éxéder 180s 
*/
int tailleMaxGraphe (double tempsMax, float p, int pas, int* (*algo) (Graph*, int*)) ; 

// Calcule les nbPoints de temps de l'algorithme non-glouton 
double *tempsMoyenNonGlouton (int nbGraphes, int nbPoints, double p) ; 