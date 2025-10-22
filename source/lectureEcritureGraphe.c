#include <./header/IOGraphe.h>

int map_indice_sommet(int nbSommets,int *tabSommets, int sommet){
    for(int i = 0; i < nbSommets; i++){
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

int gerer_ligne(int i, char *line, Graph *g){
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
                freeTab(g -> tabAdjacence, g -> nbSommets);
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
    char *carry = NULL;
    int n = 0;
    Graph *g = malloc(sizeof(Graph));
    int i = 0;

    while((n = read(fd, buf, 1)) > 0){
        char *data;
        buf[n] = '\0';
        if(carry){
            int len = strlen(carry);
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