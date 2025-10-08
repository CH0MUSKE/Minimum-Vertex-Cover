#include "./header/operationGraph.h"
#include <stdio.h>

int main(int argc, char* argv) {
    int *a = malloc(sizeof(int) * 5) ; 
    for (int i = 0 ; i < 5 ; i++) {
        a[i] = i ; 
    }
    afficheTab(a, 5) ; 
    return 0 ; 
}