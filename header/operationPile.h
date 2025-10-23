#include "./header/branchBound.h"  

typedef struct _pile {
    solution *s ; 
    struct _pile *suiv ; 
} Pile ; 

// Empile solution dans la pile, ne détruit pas solution
Pile *empile (Pile *p, solution *s) ; 

// Empile solution dans la pile, détruit l'élement 
Pile *depile (Pile *p, Pile **el) ; 

//
Pile *creeElPile (solution *s) ; 

void liberePile (Pile *p) ; 

void libereElPile (Pile *p) ; 