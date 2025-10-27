#include "./header/branchBound.h"
#include <stdio.h>

int main(int argc, char** argv) {

    for (int i = 1; i < 1000; i++)
    {
        Graph *g = genereGraphAlea(i, 0.4) ; 
        Couplage c = couplage(g) ; 
        
        for (int j = 0; j < c.cardinal; j++)
        {
            free(c.couplage[j]) ; 
        }

        free(c.couplage) ;         
        freeGraph(g) ; 

    }
    
	printf("Fin de fct") ; 
	
	
    return 0 ; 
}