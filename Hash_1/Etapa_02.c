//inclusÃ£o de biblioteca
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contador = 0;

struct Est_etapa2{
   int chave;
   int cod;
   struct Est_etapa2 *prox;
};

typedef struct Est_etapa2 tipo_etapa2;
typedef tipo_etapa2 *Hash;

void inicializa(Hash *tab, int m){
    int i;

    for (i = 0; i < m; i++){
        tab[i] = NULL;
    }
}

int hash(int chave, int m){
    return chave % m;
}

tipo_etapa2 *aloca(int chave, int cod){
    tipo_etapa2 *novo = (tipo_etapa2 *) malloc(sizeof(tipo_etapa2));
    novo->chave = chave;
    
    for(int i = 0; i < 4; i++)
        novo->cod = cod;
    
    novo->prox = NULL;
    return novo;
}

void insere(Hash *tab, int m, int chave, int  cod){
    int h = hash(chave, m);
    tipo_etapa2 *p = tab[h];
    tipo_etapa2 *ant = NULL;

    
    while ((p != NULL) && (p->chave != chave)){
        ant = p;
        p = p->prox;
    }

    if (p){
        for (int i = 0; i < 4; i++){
            p->cod = cod;
        }
        return;
    }

    tipo_etapa2 *novo = aloca(chave, cod);

    if(!ant)
        tab[h] = novo;
    else{
        ant->prox = novo;
        contador++;
        printf("Colizão: %d\n", contador);
    }
}

int busca(Hash *tab, int m, int chave){
    int h = hash(chave, m);

    tipo_etapa2 *p = tab[h];

    while((p) && (p->chave != chave)){
        p = p->prox;
    }

    return p;
}

float exclui(Hash *tab, int m, int chave){
    int h = hash(chave, m);

    if(tab[h] == NULL)
        return -1;

    else{
        tipo_etapa2 *p = tab[h];
        tipo_etapa2 *ant = NULL;
        float cr = -1;

        while((p) && (p->chave != chave)){
            ant = p;
            p = p->prox;
        }

        if(!p)
            return cr;
        if (!ant)
            tab[h] = p->prox;
        else
            ant->prox = p->prox;
        cr = 1;
        free(p);
        
        return cr;
    }
}

void libera(Hash *tab, int m){
    for(int i=0; i < m; i++){
        if(tab[i]){
            tipo_etapa2 *p = tab[i];
            tipo_etapa2 *q;
            while (p){
                q = p;
                p = p->prox;
                free(q);
            }
        }
    }
}

void imprime(Hash *tab, int m){
    for(int i=0; i < m; i++){
        printf("%d:\n", i);

        if(tab[i] != NULL){
            tipo_etapa2 *p = tab[i];
            printf("\n");
            while(p){
                printf("\tchave: %d\tcod: %d \n", p->chave, p->cod);
                p = p->prox;
            }
        }

        else
            printf("NULL\n");
    }
}

int main(){
    int m = 100;
    FILE *file;

    int chave;
    int cod = 0;
    int nada;

    file = fopen("saida.txt", "r");

    Hash *tab[m];

    inicializa(tab, m);

    if(file != NULL){
        while (fscanf(file, "%d %d", &chave, &nada) != EOF){
            //printf("%d %d\n", chave, cod);
            insere(tab, m, chave, cod++);
        }   
    }
    fclose(file);

    imprime(tab, m);

    libera(tab, m);

    return 0;
}