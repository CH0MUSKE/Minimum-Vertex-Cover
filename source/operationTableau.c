#include "./header/operationTableau.h"

int rechercheDich (int *tab, int len, int e) {
    /*
    Effectue une recherche dichotomique de e dans tab 
    Renvoie -1 si e n'est pas dans tab 
    */
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
    else {
        printf("Tableau vide\n") ; 
    }
}

int *copieTab (int *tab, int len) {
    int *res = malloc(sizeof(int) * len) ; 
    if (tab && len) {
        for (int i = 0 ; i < len ; i++) {
            res[i] = tab[i] ; 
        }
    }
    else if (!res) {
        printf("====Critical copy error====\n") ; 
        return NULL ; 
    }
    
    else {
        free(res) ; 
        return NULL ; 
    }
    return res ; 
}

int *supprimePremierEl (int* tab, int len, int e, int *posElt) {

    int index = rechercheIter(tab, len, e) ;     
    
    int *res = NULL ; 
    if (index != -1) {
        if (len != 1) {
            res = malloc(sizeof(int) * (len - 1)) ; 
            int q = 0 ; 
            if (!res) {
                printf("====Memory not allocated in supprimePremierEl====\n") ; 
            }
            for (int i = 0 ; i < len ; i++) {
                if (index != i) {
                    res[i - q] = tab[i] ; 
                }
                else {
                    q = 1 ; 
                }
            }
        }
    }

    else {
        res = malloc(sizeof(int) * (len)) ; 
        for (int i = 0 ; i < len ; i++) {
            res[i] = tab[i] ; 
        }
        printf("Element not removed : %d\n", e) ; 
    }

    free(tab) ; 
    *posElt = index ; 
    return res ; 
}

int *retireValTabIndex(int *tab, int len, int index, int *estSupprime) {
    int *res = NULL ; 
    if (!tab) {
        *estSupprime = 1 ; 
        return res ; 
    }
    else if (len == 1 && index == 0) {
        res = NULL ; 
    }
    else if (index < len && len > 0 && index > -1) {
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
    else {
        *estSupprime = 1 ; 
        res = copieTab(tab, len) ; 
    }
    free(tab) ; 
    return res ; 
}


int rechercheIter (int *tab, int len, int e) {
    // Cherche e dans tab par recherche itérative 
    if (tab) {
        for (int i = 0 ; i < len ; i++) {
            if (tab[i] == e) {
                return i ; 
            }
        }
    }
    else {
        printf("====RechercheIter : tab does not exist====\n") ; 
    }
    printf("Element not found : %d\n", e) ; 
    return -1 ; 
}

int *raccourcitListe (int *tab, int len, int *newLen) {
    *newLen = len ; 
    if (tab) {
        for (int i = 0 ; i < len ; i++) {
            if (tab[i] == -1) {
                *newLen = i ; 
                break ;
            }
        }
        if (!*newLen) {
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
    *newLen = -1 ; 
    return NULL ;     
}

void freeTab(int **tab, size_t n){
    for(size_t i = 0; i < n; i++){
        free(tab[i]);
    }
    free(tab);
}
int calculeIndexValeur(int*tab, int len, int v) {
    if (tab && len) {
        for (int i = 0 ; i < len ; i++) {
            if (tab[i] == v) {
                return i ; 
            }
        }
    }
    return -1 ; 
}