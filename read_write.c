#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _graph
{
    int nbSommets;
    int nbAretes;
    int *degreSommet;
    int *tabSomets;
    int **tabAdjacence;
}Graph;




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
    int indice_sommet = map_indice_sommet(nbSommets, g -> tabSomets, sommet);
    if(indice_sommet == -1) return -1;
    for(int i = 0; i < nbSommets; i++){
        if(g -> tabAdjacence[indice_sommet][i] == 1){
            n++;
        }
    }
    return n;
}

int ajout_degre_tous_sommets(Graph *g){
    int nbSommets = g -> nbSommets;
    for(int i = 0; i < nbSommets; i++){
        int n = degre_sommet(g -> tabSomets[i], g);
        if(n == -1) return 1;
        g ->degreSommet[i] = n;
    }

    return 0;
}

int ajout_arete(Graph *g, int sommetA, int sommetB){
    int ia = map_indice_sommet(g ->nbSommets,g -> tabSomets,sommetA);
    int ib = map_indice_sommet(g ->nbSommets,g -> tabSomets,sommetB);
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
            g -> tabSomets = malloc(sizeof(int) * n);
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
                g -> tabSomets[i-3] = n;
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
            if(ajout_degre_tous_sommets(g) == 1) return 0;
            break;
        }
    }
    return 1;
}

Graph *lireGraph(char *f){
    int fd = open(f,O_RDONLY,0700);
    char buf[520]; 
    int r = 0;
    char *carry = NULL;
    ssize_t n = 0;
    Graph *g = malloc(sizeof(Graph));
    unsigned int i = 0;

    while((n = read(fd, buf, 519)) > 0){
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

void printGraph(Graph *g){
    if (g == NULL) {
        printf("Graph invalide.\n");
        return;
    }

    printf("Nombre de sommets\n");
    printf("%d\n", g->nbSommets);

    printf("Sommets\n");
    for (int i = 0; i < g->nbSommets; i++) {
        printf("%d\n", g->tabSomets[i]);
    }

    printf("Nombre d aretes\n");
    printf("%d\n", g->nbAretes);

    printf("Aretes\n");
    for (int i = 0; i < g->nbSommets; i++) {
        for (int j = i + 1; j < g->nbSommets; j++) {
            if (g->tabAdjacence[i][j] == 1) {
                printf("%d %d\n", g->tabSomets[i], g->tabSomets[j]);
            }
        }
    }
}

int ecrireGraph(Graph *g,char *nom){
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
        sprintf(buf,"%d\n",g ->tabSomets[i]);
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
        for (int j = i + 1;j< nbSommets; j++){
            if (g->tabAdjacence[i][j] == 1){
                sprintf(buf2,"%d %d\n", g->tabSomets[i], g->tabSomets[j]);
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


int main(){
    Graph *g = lireGraph("graph.txt");
    for(int i = 0; i < g -> nbSommets; i++){
        printf("%d\n",g -> degreSommet[i]);
    }
    return ecrireGraph(g,"graph2.txt");
}