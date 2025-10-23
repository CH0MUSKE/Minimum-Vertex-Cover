#include "./header/operationPile.h"

Pile *empile (Pile *p, solution *s) {
    Pile *tete = creeElPile(s) ; 
    tete->suiv = p ; 
    return tete ; 
}

Pile *depile (Pile *p, Pile **el) {
    if (p) {
        Pile *newTete = p->suiv ; 
        *el = p ; 
        return newTete ; 
    }
}

void liberePile (Pile *p) {
    if (p) {
        Pile *suiv = p->suiv ;
        libereElPile(p) ; 
        liberePile(suiv) ;  
    }
}

void libereElPile (Pile *p) {
    if (p) {
        free(p->s) ; 
        free(p) ; 
    }
}

Pile *creeElPile (solution *s) {
    Pile *res = malloc(sizeof(Pile)) ; 
    res->suiv = NULL ; 
    res->s = copieSolution(s) ; 
    return res ; 
}