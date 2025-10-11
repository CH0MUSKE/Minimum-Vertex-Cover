#include "./header/operationTableau.h"

int rechercheDich (int *tab, int len, int e) {
    if (len == 0) {
        return -1 ; 
    }
    else if (tab[len / 2] == e) {
        return len / 2 ; 
    }
    else if (tab[len / 2] > e)
    {
        return rechercheDich(tab, len / 2, e) ; 
    }
    else {
        return rechercheDich(tab + (len / 2), len / 2, e) ; 
    }
    
}

void afficheTab (int *tab, int len) {
    if (tab) {
        for (int i = 0 ; i < len - 1 ; i++) {
            printf("%d, ", tab[i]) ; 
        }
        if (len > 0) {
            printf("%d\n", tab[len - 1]) ; 
        }
        else {
            printf("\n") ; 
        }
    }
}

int *copieTab (int *tab, int len) {
    int *res = malloc(sizeof(int) * len) ; 
    if (tab) {
        for (int i = 0 ; i < len ; i++) {
            res[i] = tab[i] ; 
        }
    }
    else {
        return NULL ; 
    }
    return res ; 
}

int *supprimePremierEl (int* tab, int len, int e, int *posElt) {
    /*
    Retire le premier e contenu dans tab. 
    index vaut : 
    l'index du nombre retiré 
    -1 si il n'y est pas contenu 
    */
    int index = rechercheIter(tab, len, e) ; 
    
    int *res = NULL ; 
    if (index != -1) {
        if (len != 1) {
            res = malloc(sizeof(int) * (len - 1)) ; 
            int q = 0 ; 
            for (int i = 0 ; i < len ; i++) {
                if (index != i) {
                    res[i - q] = tab[i] ; 
                }
                else {
                    q = 1 ; 
                }
            }
        }
        else {
            res = NULL ; 
            free(tab) ; 
        }
    }
    else {
        res = malloc(sizeof(int) * (len)) ; 
        for (int i = 0 ; i < len - 1 ; i++) {
            res[i] = tab[i] ; 
        }

    }
    *posElt = index ; 
    return res ; 
}

int *retireValTabIndex(int *tab, int len, int index, int *estSupprime) {
    int *res = NULL ; 
    if (index < len && len > 0 && index > -1) {
        *estSupprime = 0 ; 
        int q = 0 ; 
        res = malloc(sizeof(int) * (len - 1)) ; 
        for (int i = 0 ; i < len ; i++)
        {
            if (index != i) {
                res[i - q] = tab[i] ; 
            }
            else {
                q = 1 ; 
            }
        }
    }
    else if (len == 1 && index == len) {
        res = NULL ; 
    }
    else {
        *estSupprime = 1 ; 
        res = copieTab(tab, len) ; 
    }
    free(tab) ; 
    return res ; 
}


int rechercheIter (int *tab, int len, int e) {
    // Cherche e dans tab par recherche itérative 
    for (int i = 0 ; i < len ; i++) {
        if (tab[i] == e) {
            printf("%d\n", i) ; 
            return i ; 
        }
    }
    return -1 ; 
}

int *raccourcitListe (int *tab, int len, int *newLen) {
    // Raccourcit le tableau tab passé en paramètre, supposant que les cases vides sont 
    // marqués par -1
    *newLen = len ; 
    for (int i = 0 ; i < len ; i++) {
        if (tab[i] == -1) {
            *newLen = i ; 
            break ;
        }
    }
    if (*newLen) {
        free(tab) ;
        return NULL ; 
    }
    else {
        int *res = malloc(sizeof(int) * (*newLen)) ; 
        for (int i = 0 ; i < *newLen ; i++) {
            res[i] = tab[i] ; 
        }
        free(tab) ; 
        return res ; 
    }
    
}