#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct aluno{
    int matricula;

    float cr;
    struct aluno *prox;    
}TAluno;

typedef TAluno* Hash;


int hash_linear(int mat, int tam, int i){
    double A;
    int pos = mat % tam;
    
    return ((pos+i)%tam);
}

void inicializa(Hash *tab, int m){

    int i;
    for(i=0; i<m; i++){
        tab[i] = NULL;
    }
}

TAluno* aloca(int mat, float cr){
    TAluno *novo = (TAluno*) malloc (sizeof(TAluno));
    novo -> matricula = mat;
    novo -> cr = cr;
    novo -> prox = NULL;
    return novo;
}

void insere_linear(Hash *tab, int m, int i, int mat, float cr){
    int h = hash_linear(mat,m,i);
    TAluno *p = tab[h];
    TAluno *ant = NULL;
    while ((p != NULL) && (p->matricula != mat)){
        ant = p;
        p = p->prox;
    }

    if(p){
        p -> cr = cr;
        return;
    }
   

    TAluno *novo = aloca(mat, cr);

    if(!ant){
        tab[h] = novo;
    }else{
        ant -> prox = novo;
    }
}

void imprime(Hash *tab, int m){
    for(int i = 0; i < m; i++){
        printf("%d: ",i);
        if (tab[i]){
            TAluno *p = tab[i];
            printf("\n");
            while(p){
                printf("\t%d\t%f\t%p\n", p-> matricula, p-> cr, p->prox);
                p = p->prox;
            }
        }
        else printf("NULL\n");
    }
}



TAluno* busca_linear(Hash *tab, int m, int i, int mat){
    int h = hash_linear(mat, m, i);
    TAluno *p = tab[h];
    while((p) && (p->matricula != mat)){
        p = p -> prox;
    }
    return p;
}



float exclui_linear(Hash *tab, int m,int i, int mat){
     
    int h = hash_linear(mat, m,i);
    if(tab[h] == NULL){
        return -1;
    }

    TAluno *p = tab[h];
    TAluno *ant = NULL;
    float cr = -1;

    while ((p != NULL) && (p->matricula != mat)){
        ant = p;
        p = p->prox;
    }

    if (p == NULL){
        return cr;
    }
    if (ant == NULL){
        tab[h] = p->prox;
    }else{
        ant->prox = p->prox;
    }
    cr =  p -> cr;
    free(p);

    return cr;
}

void libera(Hash *tab, int m){
    int i;
    for(i=0; i < m; i++){
        if(tab[i]){
            TAluno *p = tab[i];
            TAluno *q;
            while(p){
                q = p;
                p = p->prox;
                free(q);
            }
        }
    }
}

int main(){
    int m;
    m = 5;

    Hash *tab[m];
    inicializa(tab, m);
    // passados por parametro tabela/tamanho/valor matricula/coeficiente de rendimento
    insere_linear(tab, m, 0, 12, 5.8);
    insere_linear(tab, m, 1, 3, 7.2);
    insere_linear(tab, m, 0, 12, 4.5);
    insere_linear(tab, m, 2, 18, 9.1);
    insere_linear(tab, m, 3, 9, 6.3);
    insere_linear(tab, m, 4, 13, 9);
    insere_linear(tab, m, 5, 21, 7);
    insere_linear(tab, m, 6, 25, 4);
    insere_linear(tab, m, 5, 21, 7);
    insere_linear(tab, m, 6, 25, 4);

    imprime(tab, m);

    TAluno *p = busca_linear(tab, m, 2, 18);
    if (!p){printf("Elemento nao encontrado!\n");}
    else{printf("%d\t%f\n", p->matricula, p->cr);}

    printf(" ------------------------------ \n");
    int cr = exclui_linear(tab, m, 2, 18);
    if(cr != -1) printf("%d\t%f foi excluido\n", 18, cr);

    cr = exclui_linear(tab, m, 0, 12);
    if(cr != -1) printf("%d\t%f foi excluido\n", 12, cr);

    imprime(tab, m);

    libera(tab, m);

    return 0;
}
