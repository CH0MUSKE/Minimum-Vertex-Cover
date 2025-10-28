#include "./header/branchBound.h"
#include <stdio.h>

int main(int argc, char** argv) {

    /*for (int i = 1; i < 1000; i++)
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
    
	printf("Fin de fct") ; */

    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int i = 0;
    while(i == 0){
        Graph *g = genereGraphAlea(20, 0.4) ; 
        //solution so = branchementBorneCouplageAmelioreInit(g);
        solution s = branchementSimpleInit(g);
        //solution sol = branchementBorneCouplageInit(g);
        //solution solu = branchementBorneCouplageAmelioreDegMaxInit(g);
        a = s.cardinal;
        //b = so.cardinal;
        //c = sol.cardinal;
        //d = solu.cardinal;
        printf("%d\n", s.cardinal );
        printf("----- simple ------\n");
        for(int i = 0; i <a; i++){
            printf("-%d-",s.couverture[i]);
        }
        /*printf("\n----- ameliore ------\n");
        for(int i = 0; i <b; i++){
            printf("-%d-",so.couverture[i]);
        }
        printf("\n----- amelioreDegMax ------\n");
        for(int i = 0; i <d; i++){
            printf("-%d-",solu.couverture[i]);
        }
        printf("\n------ couplage -----\n");
        for(int i = 0; i <c; i++){
            printf("-%d-",sol.couverture[i]);
        }*/
        printf("\n-----------\n");
        freeGraph(g);
        free(s.couverture);
        //free(sol.couverture);
        //free(so.couverture);
        //free(solu.couverture);
        i++;
    }
    printf("**%d**\n",i);
    
    


	
    return 0 ; 
}