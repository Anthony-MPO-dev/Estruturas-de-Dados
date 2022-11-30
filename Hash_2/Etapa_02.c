//inclusÃ£o de biblioteca
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define A 0.618034

struct Est_etapa2{
   int chave;
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

int hash1(int chave, int m){
    return chave % m;
}

int hash2(int chave, int m){
    double n = 0.000000;
    n = m * ((chave * A) - ((int)(chave * A)));
    return floor(n);
}

tipo_etapa2 *aloca(int chave){
    tipo_etapa2 *novo = (tipo_etapa2*) malloc(sizeof(tipo_etapa2));
    novo->chave = chave;
    novo->prox = NULL;
    return novo;
}

void insere1(Hash *tab, int m, int chave, int *col1){
    int h = hash1(chave, m);
    tipo_etapa2 *p = tab[h];
    tipo_etapa2 *ant = NULL;
    
    while ((p != NULL) && (p->chave != chave)){
        ant = p;
        p = p->prox;
    }

    if(p){
        p->chave = chave;
        return;
    }

    tipo_etapa2 *novo = aloca(chave);

    if(!ant)
        tab[h] = novo;
    else{
        ant->prox = novo;
        *col1 = *col1 + 1;
    }
}

void insere2(Hash *tab, int m, int chave, int *col2){
    int h = hash2(chave, m);
    tipo_etapa2 *p = tab[h];
    tipo_etapa2 *ant = NULL;

    while ((p != NULL) && (p->chave != chave)){
        ant = p;
        p = p->prox;
    }

    if(p){
        p->chave = chave;
        return;
    }

    tipo_etapa2 *novo = aloca(chave);

    if(!ant)
        tab[h] = novo;
    else{
        ant->prox = novo;
        *col2 = *col2 + 1;
    }
}

int busca(Hash *tab, int m, int chave){
    int h = hash1(chave, m);

    tipo_etapa2 *p = tab[h];

    while((p) && (p->chave != chave)){
        p = p->prox;
    }

    return p;
}

float exclui(Hash *tab, int m, int chave){
    int h = hash1(chave, m);

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
        printf("\n%d:", i);

        if(tab[i] != NULL){
            tipo_etapa2 *p = tab[i];
            printf("\n");
            while(p){
                printf("\tchave: %d \n", p->chave);
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
    FILE *file2;

    int chave;
   
    char *arq_name1 = (char *)malloc(20 * sizeof(char));
    char *arq_name2 = (char *)malloc(21 * sizeof(char));
    char *arq_name3 = (char *)malloc(21 * sizeof(char));
    char *arq_name4 = (char *)malloc(20 * sizeof(char));
    char *arq_name5 = (char *)malloc(21 * sizeof(char));
    char *arq_name6 = (char *)malloc(21 * sizeof(char));

    Hash *tab[m];
    Hash *tab2[m];
    Hash *tab3[m];
    Hash *tab4[m];

    int cont_50[]  = {0,0};
    int cont_100[] = {0,0};
    int cont_150[] = {0,0};

    int cont_50_2[]  = {0,0};
    int cont_100_2[] = {0,0};
    int cont_150_2[] = {0,0};

    inicializa(tab, m);
    inicializa(tab2, m);
    inicializa(tab3, m);
    inicializa(tab4, m);

    int colides1=0, colides2=0;
    int colides3=0, colides4=0;
    int tipo =0;

    for (int i = 1; i < 6; i++) {

        snprintf (arq_name1, 20, "%s%d%s", "arquivos/50_1_", i, ".txt");
        snprintf (arq_name2, 21, "%s%d%s", "arquivos/100_1_", i, ".txt");
        snprintf (arq_name3, 21, "%s%d%s", "arquivos/150_1_", i, ".txt");
        snprintf (arq_name4, 20, "%s%d%s", "arquivos/50_2_", i, ".txt");
        snprintf (arq_name5, 21, "%s%d%s", "arquivos/100_2_", i, ".txt");
        snprintf (arq_name6, 21, "%s%d%s", "arquivos/150_2_", i, ".txt");

        file = fopen(arq_name1, "r");
        file2 = fopen(arq_name4, "r");
        
        inicializa(tab, m);
        inicializa(tab2, m);
        inicializa(tab3, m);
        inicializa(tab4, m);

        if(file != NULL && file2 != NULL){
            while (fscanf(file, "%d", &chave) != EOF){
                insere1(tab, m, chave, &colides1);
                insere2(tab2, m, chave, &colides2);
            }
            while(fscanf(file2, "%d", &chave) != EOF){
                insere1(tab3, m, chave, &colides3);
                insere2(tab4, m, chave, &colides4);
            }     
        }
        printf("TIPO de ARQUIVO 1:\n");
        printf("HASH 1 -> {Arqs 50 nums:\n Colisoes: %d\n}\n", colides1);
        printf("HASH 2 -> {Arqs 50 nums:\n Colisoes: %d\n}\n\n", colides2);
        printf("TIPO de ARQUIVO 2:\n");
        printf("HASH 1 -> {Arqs 50 nums:\n Colisoes: %d\n}\n", colides3);
        printf("HASH 2 -> {Arqs 50 nums:\n Colisoes: %d\n}\n\n", colides4);

        cont_50[0] = cont_50[0] + colides1;
        cont_50[1] = cont_50[1] + colides2;
        cont_50_2[0] = cont_50_2[0] + colides3;
        cont_50_2[1] = cont_50_2[1] + colides4;
        colides1 = 0;
        colides2 = 0;
        colides3 = 0;
        colides4 = 0;
        fclose(file);
        fclose(file2);

        file = fopen(arq_name2, "r");
        file2 = fopen(arq_name5, "r");
            
        inicializa(tab, m);
        inicializa(tab2, m);
        inicializa(tab3, m);
        inicializa(tab4, m);

        if(file != NULL && file2 != NULL){
            while (fscanf(file, "%d", &chave) != EOF){
                insere1(tab, m, chave, &colides1);
                insere2(tab2, m, chave, &colides2);
            } 
            while (fscanf(file2, "%d", &chave) != EOF){
                insere1(tab3, m, chave, &colides3);
                insere2(tab4, m, chave, &colides4);
            }  

        }
        printf("TIPO de ARQUIVO 1:\n");
        printf("HASH 1 -> {Arqs 100 nums:\n Colisoes: %d\n}\n", colides1);
        printf("HASH 2 -> {Arqs 100 nums:\n Colisoes: %d\n}\n\n", colides2);
        printf("TIPO de ARQUIVO 2:\n");
        printf("HASH 1 -> {Arqs 100 nums:\n Colisoes: %d\n}\n", colides3);
        printf("HASH 2 -> {Arqs 100 nums:\n Colisoes: %d\n}\n\n", colides4);
        cont_100[0] = cont_100[0] + colides1;
        cont_100[1] = cont_100[1] + colides2;
        cont_100_2[0] = cont_100_2[0] + colides3;
        cont_100_2[1] = cont_100_2[1] + colides4;
        colides1 = 0;
        colides2 = 0;
        colides3 = 0;
        colides4 = 0;
        fclose(file);
        fclose(file2);

        file = fopen(arq_name3, "r");
        file2 = fopen(arq_name6, "r");

        inicializa(tab, m);
        inicializa(tab2, m);
        inicializa(tab3, m);
        inicializa(tab4, m);

        if(file != NULL && file2 != NULL){
            while (fscanf(file, "%d", &chave) != EOF){
                insere1(tab, m, chave, &colides1);
                insere2(tab2, m, chave, &colides2);
            } 
             while (fscanf(file2, "%d", &chave) != EOF){
                insere1(tab3, m, chave, &colides3);
                insere2(tab4, m, chave, &colides4);
            }     
        }
        printf("TIPO de ARQUIVO 1:\n");
        printf("HASH 1 -> {Arqs 150 nums:\n Colisoes: %d\n}\n", colides1);
        printf("HASH 2 -> {Arqs 150 nums:\n Colisoes: %d\n}\n\n", colides2);
        printf("TIPO de ARQUIVO 2:\n");
        printf("HASH 1 -> {Arqs 150 nums:\n Colisoes: %d\n}\n", colides3);
        printf("HASH 2 -> {Arqs 150 nums:\n Colisoes: %d\n}\n\n", colides4);
        cont_150[0] = cont_150[0] + colides1;
        cont_150[1] = cont_150[1] + colides2;
        cont_150_2[0] = cont_150_2[0] + colides3;
        cont_150_2[1] = cont_150_2[1] + colides4;
        colides1 = 0;
        colides2 = 0;
        colides3 = 0;
        colides4 = 0;
        fclose(file);
        fclose(file2);

    }
    
    printf("Arquivos tipo 1 {\n");
 
    printf("Colisoes com Hash 1\n");
    printf("Com 50 valores foram contadas:\nColisoes: %d\n", cont_50[0]);
    printf("Com 100 valores foram contadas:\nColisoes: %d\n", cont_100[0]);
    printf("Com 150 valores foram contadas:\nColisoes: %d\n\n", cont_150[0]);
    printf("Colisoes com Hash 2\n");
    printf("Com 50 valores foram contadas:\nColisoes: %d\n", cont_50[1]);
    printf("Com 100 valores foram contadas:\nColisoes: %d\n", cont_100[1]);
    printf("Com 150 valores foram contadas:\nColisoes: %d\n\n", cont_150[1]);

    printf("\n=========================================================================\n\n");
    printf("Arquivos tipo 2 {\n");

    printf("Colisoes com Hash 1\n");
    printf("Com 50 valores foram contadas:\nColisoes: %d\n", cont_50_2[0]);
    printf("Com 100 valores foram contadas:\nColisoes: %d\n", cont_100_2[0]);
    printf("Com 150 valores foram contadas:\nColisoes: %d\n\n", cont_150_2[0]);
    printf("Colisoes com Hash 2\n");
    printf("Com 50 valores foram contadas:\nColisoes: %d\n", cont_50_2[1]);
    printf("Com 100 valores foram contadas:\nColisoes: %d\n", cont_100_2[1]);
    printf("Com 150 valores foram contadas:\nColisoes: %d\n\n", cont_150_2[1]);

    cont_50[0] = (cont_50[0] + cont_100[0] + cont_150[0] + cont_50[1] + cont_100[1] + cont_150[1] 
    + cont_50_2[0] + cont_100_2[0] + cont_150_2[0] + cont_50_2[1] + cont_100_2[1] + cont_150_2[1]);

    printf("Ao total foram contadas:\nColisoes: %d\n\n", cont_50[0]);

    printf("}\n");
    
    return 0;
}

