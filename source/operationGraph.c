#include "./header/operationGraph.h"
 
int calcdegreSommet (Graph *g) {
    if (g)
    {
        int res = 0 ; 
        for (int i = 0 ; i < g->nbSommets ; i++) {
            res += g->degreSommet[i] ; 
        }
        return res ; 
    }
    return 0 ; 
}

float valRandom() {
    // Tire une valeur aléatoire entre 0 et 1 
    return ((float) rand()) / ((float) RAND_MAX) ; 
}

Graph *genereGraphAlea (int n, float p) {
    srand(time(NULL)) ;
    if (p > 1 || p < 0 || n <= 0) {
        return NULL ; 
    }

    Graph *res = creeGraph(n) ; 
    res->tabSommets = malloc(sizeof(int) * res->nbSommets) ; 
    res->degreSommet = malloc(sizeof(int) * res->nbSommets) ; 
    res->tabAdjacence = malloc(sizeof(int*) * res->nbSommets) ; 
    // On crée les sommets 
    for (int i = 0 ; i < res->nbSommets ; i++) {
        res->tabSommets[i] = i ; 
        res->degreSommet[i] = res->nbSommets - 1 ; 
        res->tabAdjacence[i] = malloc(sizeof(int) * res->degreSommet[i]) ; 
        /*
        if (!res->tabAdjacence[i]){
            printf("Erreur creation graphe\n") ; 
            freeGraph(res) ; 
            return NULL ; 
        }
        */
        for (int j = 0 ; j < res->degreSommet[i] ; j++) {
            res->tabAdjacence[i][j] = -1 ; 
        }
    }
    
    // On initialise les degrés temporaires des arcs 
    int *nbArreteCourant = malloc(sizeof(int) * res->nbSommets) ; 
    for (int i = 0; i < res->nbSommets ; i++) {
        nbArreteCourant[i] = 0 ; 
    }

    // On considère que on ne peut que rajouter des sommets dont leur numéro est supérieur 
    // Au numéro présent, pour éviter des doubles arcs 
    for (int i = 0 ; i < res->nbSommets ; i++) {
        
        // ########################## Changer valRandom en : 
        // Génerateur de nombre random https://blog.bithole.dev/blogposts/random-float/
        for (int j = i + 1 ; j < res->nbSommets ; j++) {
            if (valRandom() < p) {
                
                // On met j dans les adjacents de i 
                res->tabAdjacence[i][nbArreteCourant[i]] = j ; 
                nbArreteCourant[i] += 1 ; 
                // On met i dans les adjacents de j 
                res->tabAdjacence[j][nbArreteCourant[j]] = i ; 
                nbArreteCourant[j] += 1 ; 
            }
        }
        int temp = 0 ; 
        res->tabAdjacence[i] = raccourcitListe(res->tabAdjacence[i], res->degreSommet[i], &temp) ; 
        res->degreSommet[i] = temp ; 
        res->nbAretes += temp ; 
    }
    free(nbArreteCourant) ; 
    res->nbAretes = res->nbAretes / 2; 
    return res ;         
}


Graph *creeGraph(int n) {
    Graph *res = malloc(sizeof(Graph)) ; 
    res->nbSommets = n ; 
    res->nbAretes = 0 ; 
    res->degreSommet = NULL ; 
    res->tabSommets = NULL ; 
    res->tabAdjacence = NULL ; 
    return res ; 
}

void freeGraph (Graph *g) {
    if (g) {
        free(g->degreSommet) ; 
        free(g->tabSommets) ; 
        
        for (int i = 0 ; i < g->nbSommets ; i++) {
            if (g->tabAdjacence[i]) {
                free(g->tabAdjacence[i]) ; 
            }
        }

        free(g) ; 
    }
}

Graph *copieGraph (Graph *g) {
    if(g) {
        Graph *res = creeGraph(g->nbSommets) ; 
        res->nbAretes = g->nbAretes ; 
        res->degreSommet = copieTab(g->degreSommet, g->nbSommets) ; 

        res->tabSommets = copieTab(g->tabSommets, g->nbSommets) ; 
        res->tabAdjacence = malloc(sizeof(int*)*g->nbSommets) ; 
        
        for (int i = 0 ; i < g->nbSommets ; i++) {
            
            res->tabAdjacence[i] = copieTab(g->tabAdjacence[i], g->degreSommet[i]) ; 
        }
        return res ; 
    }
    return NULL ; 
}

void afficheGraph(Graph *g) {
    if (g) {
        printf("NbSommets : %d, NbAretes : %d\n", g->nbSommets, g->nbAretes) ; 
        printf("Tableau des sommets : ") ; 
        afficheTab(g->tabSommets, g->nbSommets) ; 
    
        // Finir affichage 
        for (int i = 0 ; i < g->nbSommets ; i++) {
            printf("Sommets adjacents de %d : ", g->tabSommets[i]) ; 
            afficheTab(g->tabAdjacence[i], g->degreSommet[i]) ; 
        }
        printf("Liste des tailles des listAdj : ") ; 
        afficheTab(g->degreSommet, g->nbSommets) ; 
    } 
    else {
        printf("Graphe est vide\n") ; 
    }

}

Graph *retireSommet (Graph *G, int v) {
	/*
	1. Détruire le sommet v dans la liste des sommets de G 
	2. Pour chaque sommet présent dans la liste des adjacents du sommet v : 
		2.1. Détruire le sommet v de cette liste 
	3. Détruire la liste des adjacents du sommet v 
	*/

    
    Graph *res = copieGraph(G) ; 
    
	freeGraph(G) ; 
	int posValSupprimer = calculeIndexValeur(res->tabSommets, res->nbSommets, v) ; 
	if (posValSupprimer != -1 && res->nbSommets > 1) {
        // Etape 2 
		int temp ; 
        
		for (int i = 0 ; i < res->degreSommet[posValSupprimer] ; i++) {
            int posSommetAdj = calculeIndexValeur(res->tabSommets, res->nbSommets, res->tabAdjacence[posValSupprimer][i]) ; 
            
        
			res->tabAdjacence[posSommetAdj] = 
            supprimePremierEl(res->tabAdjacence[posSommetAdj], res->degreSommet[posSommetAdj], v, &temp) ; 
            if (temp != -1) {
                res->degreSommet[posSommetAdj] -= 1 ; 
            }
            else {
                printf("%p\n", res->tabAdjacence[posSommetAdj]) ; 
                afficheTab(res->tabAdjacence[posSommetAdj], res->degreSommet[posSommetAdj]) ; 
                printf("%d, Error\n", posSommetAdj) ; 
            }
		}

		// Etape 3 
        res->nbAretes -= res->degreSommet[posValSupprimer] ; 
		res->degreSommet = retireValTabIndex(res->degreSommet, res->nbSommets, posValSupprimer, &temp) ; 
        int **listAdj = malloc(sizeof(int*) * (res->nbSommets - 1)) ; 

        temp = 0 ; 
        for (int i = 0 ; i < res->nbSommets ; i++) {
            if (posValSupprimer != i) {
                listAdj[i - temp] = res->tabAdjacence[i] ; 
            }
            else {
                temp = 1 ; 
            }
        }
        free(res->tabAdjacence) ; 
        res->tabAdjacence = listAdj ; 
        res->tabSommets = retireValTabIndex(res->tabSommets, res->nbSommets, posValSupprimer, &temp) ; 
		res->nbSommets -= 1 ; 
        
        
	}
    else if (posValSupprimer != -1 && res->nbSommets == 1) {
        freeGraph(res) ; 
        res = NULL ; 
    }
	return res ; 
}

Graph *retireEnsembleSommet (Graph *g, int *tab, int len) {
    Graph *res = copieGraph(g) ; 
    freeGraph(g) ; 
    for (int i = 0 ; i < len ; i++) {
        
        if (res) {
            res = retireSommet(res, tab[i]) ; 
        }
        else {
            return res ; 
        }
    }
    return res ; 
}

int **listeAretes(Graph *g){
    int nbSommets = g ->nbSommets;
    int nbAretes = g -> nbAretes;
    int **list = malloc(sizeof(int *) * nbAretes); 
    for (int i = 0; i < nbSommets; i++){
            list[i] = malloc(sizeof(int) * 2);
            for (int j = 0 ;j< g -> degreSommet[i]; j++){
                if(g->tabSommets[i] < g->tabAdjacence[i][j]){
                    list[i][0] = g ->tabSommets[i];
                    list[i][j] = g -> tabAdjacence[i][j];
                }
            }
    }
    return list;
}


int *algoCouplage(Graph *G, int *tailleCouverture) {
    int *C = malloc(sizeof(int) * G->nbSommets) ; 
    int tailleSup = G->nbSommets ; 
    int nbSommetsCouverture = 0 ; 
    for (int i = 0 ; i < G->nbSommets ; i++) {
        C[i] = -1 ; 
    }
    Graph *grapheCourant = copieGraph(G) ; 
    
    for (int i = 0 ; i < grapheCourant->nbSommets ; i++) {
        if (grapheCourant->nbAretes > 0) {    
            for (int j = 0 ; j < grapheCourant->degreSommet[i] ; j++) {
                
                int *aRetirer = malloc(sizeof(int) * 2) ; 
                aRetirer[0] = grapheCourant->tabSommets[i] ; 
                aRetirer[1] = grapheCourant->tabAdjacence[i][j] ; 
                
                grapheCourant = retireEnsembleSommet(
                    grapheCourant, 
                    aRetirer, 
                    2 ) ; 
                    
                
                C[nbSommetsCouverture] = aRetirer[0] ; 
                C[nbSommetsCouverture + 1] = aRetirer[1] ; 
                nbSommetsCouverture += 2 ; 
                i = 0 ; 
                free(aRetirer) ; 
                if (!grapheCourant) {
                    C = raccourcitListe(C, tailleSup, tailleCouverture) ; 
                    return C ;                         
                }
                //afficheGraph(grapheCourant) ; 
            }
        }
    }
    freeGraph(grapheCourant) ; 
    C = raccourcitListe(C, tailleSup, tailleCouverture) ; 
    return C ; 
} 


int *algoGlouton(Graph *G, int *tailleCouverture) {
    
    int *C = malloc(sizeof(int) * G->nbSommets) ; 
    int tailleSup = G->nbSommets ; 
    int nbSommetsCouverture = 0 ; 
    for (int i = 0 ; i < G->nbSommets ; i++) {
        C[i] = -1 ; 
    }
    Graph *grapheCourant = copieGraph(G) ; 
    while (grapheCourant && grapheCourant->nbAretes > 0) {
        int indexSommetMaximal = indexSommetDegMax(grapheCourant) ; 
        C[nbSommetsCouverture] = grapheCourant->tabSommets[indexSommetMaximal] ; 
        grapheCourant = retireSommet(grapheCourant, grapheCourant->tabSommets[indexSommetMaximal]) ; 
        nbSommetsCouverture += 1 ; 
    }
    if (grapheCourant) {
        freeGraph(grapheCourant) ; 
    }
    C = raccourcitListe(C, tailleSup, tailleCouverture) ; 
    return C ; 
}

int indexSommetDegMax (Graph *G) {
    if (G) {
        int argMax = 0 ; 
        for (int i = 0; i < G->nbSommets; i++) {
            if(G->degreSommet[i] > G->degreSommet[argMax]) {
                argMax = i ; 
            }
        }
        return argMax ; 
    }
    return -1 ; 
}
int map_indice_sommet(int nbSommets,int *tabSommets, int sommet){
    for(size_t i = 0; i < nbSommets; i++){
        if(tabSommets[i] == sommet){
            return i;
        }
    }
    return -1;
}

int degre_sommet(int sommet, Graph *g){
    int n = 0;
    int nbSommets = g -> nbSommets;
    int indice_sommet = map_indice_sommet(nbSommets, g -> tabSommets, sommet);
    if(indice_sommet == -1) return -1;
    for(int i = 0; i < nbSommets; i++){
        if(g -> tabAdjacence[indice_sommet][i] == 1){
            n++;
        }
    }
    return n;
}

int **mat_adj_to_liste_adj(Graph *g){
    int **tabAdjacence = g -> tabAdjacence;
    int *tabSommet = g -> tabSommets;
    int *degreSommet = g -> degreSommet;
    int **list_adj = malloc(sizeof(int *) * g -> nbSommets);
    for(int i = 0; i < g -> nbSommets; i++){
        list_adj[i] = malloc(sizeof(int) * degreSommet[i]);
        int k = 0;
        for(int j  = 0; j < g -> nbSommets; j++){
            if(tabAdjacence[i][j] == 1){
                list_adj[i][k] = tabSommet[j];
                printf("-%d %d-",list_adj[0][0], list_adj[0][1]);
                k++;
            }
        }
    }

    return list_adj;
}

int ajout_degre_tous_sommets(Graph *g){
    int nbSommets = g -> nbSommets;
    for(int i = 0; i < nbSommets; i++){
        int n = degre_sommet(g -> tabSommets[i], g);
        if(n == -1) return 1;
        g ->degreSommet[i] = n;
    }

    return 0;
}

int ajout_arete(Graph *g, int sommetA, int sommetB){
    int ia = map_indice_sommet(g ->nbSommets,g -> tabSommets,sommetA);
    int ib = map_indice_sommet(g ->nbSommets,g -> tabSommets,sommetB);
    if(ia == -1 || ib == -1){
        return 1;
    }
    g -> tabAdjacence[ia][ib] = 1;
    g -> tabAdjacence[ib][ia] = 1; 

    return 0;
       
}

int gestion_erreur_strtol(char *s){
    char * endPtr;
    int n = strtol(s,&endPtr,10);
    if(n == 0){
        if(endPtr == s){
            return -1;
        }
    }
    return n;
}

int gerer_ligne(unsigned int i, char *line, Graph *g){
    switch(i){
        case 0: return (strcmp(line,"Nombre de sommets") == 0);
        case 1: {
            int n = gestion_erreur_strtol(line);
            if(n == -1) return 0;
            g -> nbSommets = n;
            g -> tabSommets = malloc(sizeof(int) * n);
            g -> tabAdjacence = malloc(sizeof(int *) * n);
            g -> degreSommet = malloc(sizeof(int) * n);
            for(int i = 0; i < n; i++){
                g -> tabAdjacence[i] = calloc(n,sizeof(int));
            }
            break;
        }
        case 2: return (strcmp(line,"Sommets") == 0);
        default: {
            int nb_s = g -> nbSommets;
            if(i <= 2 + nb_s){
                int n = gestion_erreur_strtol(line);
                if(n == -1) return 0;
                g -> tabSommets[i-3] = n;
                break;
            }
            if(i == 3 + nb_s){
                return (strcmp(line,"Nombre d aretes") == 0);
            }
            if(i == 4 + nb_s){
                int n = gestion_erreur_strtol(line);
                if(n == -1) return 0;
                g -> nbAretes = n;
                break;
            }
            if(i == 5 + nb_s){
                return (strcmp(line,"Aretes") == 0);
            }
            char *saveptr;
            char *cpy = strdup(line);
            char *sommetA = strtok_r(cpy," ",&saveptr);
            char *sommetB = strtok_r(NULL, " ", &saveptr);
            int a = gestion_erreur_strtol(sommetA);
            int b  = gestion_erreur_strtol(sommetB);
            if(a == -1 || b == -1) return 0;
            int x = ajout_arete(g,a,b);
            free(cpy);
            if(x == 1) return 0;
            if(i == 5 + g -> nbAretes + g -> nbSommets){
                if(ajout_degre_tous_sommets(g) == 1) return 0;
                int **list_adj = mat_adj_to_liste_adj(g);
                free_tab(g -> tabAdjacence, g -> nbSommets);
                g -> tabAdjacence = list_adj;
            }
            break;
        }
    }
    return 1;
}

Graph *lireGraph(char *f){
    int fd = open(f,O_RDWR,0700);
    if(lseek(fd,0,SEEK_END) < 0){
        goto end;
    }
    if(write(fd,"\n",1) < 0){
        goto end;
    }
    if(lseek(fd,0,SEEK_SET) < 0){
        goto end;
    }
    char buf[520]; 
    int r = 0;
    char *carry = NULL;
    ssize_t n = 0;
    Graph *g = malloc(sizeof(Graph));
    unsigned int i = 0;

    while((n = read(fd, buf, 1)) > 0){
        char *data;
        buf[n] = '\0';
        if(carry){
            size_t len = strlen(carry);
            data = malloc(sizeof(char) * (len + n + 1));
            memcpy(data,carry,len);
            memcpy(data + len, buf, n);
            data[len + n] = '\0';
            free(carry);
            carry = NULL;
        }
        else{
            data = strdup(buf);
        }
        char *saveptr;
        char *cpy = strdup(data);
        char *tok = strtok_r(cpy,"\n", &saveptr);
        while(tok != NULL){
            char *next = strtok_r(NULL,"\n", &saveptr);
            if (next == NULL && data[strlen(data) - 1] != '\n'){
                carry = strdup(tok);
            }
            else{
                if(gerer_ligne(i,tok,g) != 1){
                    printf("Le fichier est mal formaté\n");
                    g = NULL;
                    free(data);
                    free(cpy);
                    goto end;
                }
                i++;
            }
            tok = next;
        }
        
        free(data);
    }
    end:
    close(fd);
    return g;
}


int ecrireGraph(char *nom, Graph *g){
    int r = 0;
    int nbSommets = g -> nbSommets;
    int nbAretes = g -> nbAretes;
    int fd = open(nom,O_WRONLY | O_CREAT | O_TRUNC, 0700);
    if(write(fd,"Nombre de sommets\n",18) < 0){
        r = 1;
        goto end;
    }
    char buf[13];
    sprintf(buf,"%d\n",nbSommets);
    if(write(fd,buf,strlen(buf)) < 0){
        r = 1;
        goto end;
    }
    if(write(fd,"Sommets\n",8) < 0){
        r = 1;
        goto end;
    }
    for(int i = 0; i < nbSommets; i++){
        sprintf(buf,"%d\n",g ->tabSommets[i]);
        if(write(fd,buf,strlen(buf)) < 0){
            r = 1;
            goto end;
        }        
    }
    if(write(fd,"Nombre d aretes\n",16) < 0){
        r = 1;
        goto end;
    }
    sprintf(buf,"%d\n",nbAretes);
    if(write(fd,buf,strlen(buf)) < 0){
        r = 1;
        goto end;
    }
    if(write(fd,"Aretes\n",7) < 0){
        r = 1;
        goto end;
    }
    char buf2[25];
    for (int i = 0; i < nbSommets; i++){
        for (int j = 0 ;j< g -> degreSommet[i]; j++){
            if(g->tabSommets[i] < g->tabAdjacence[i][j]){
                sprintf(buf2,"%d %d\n", g->tabSommets[i], g->tabAdjacence[i][j]);
                if(write(fd,buf2,strlen(buf2)) < 0){
                    r = 1;
                    goto end;
                } 
            }
        }
    }
    end:
    close(fd);
    return r;
}


