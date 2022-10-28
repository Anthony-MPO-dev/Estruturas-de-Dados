#ifndef ARVBIN_AVL //Verificacao se biblioteca foi carregada
#define ARVBIN_AVL

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int num=0;

typedef struct sNoa{
    int chave;
    int fb; //fator de balanceamento
    int h; //altura do noh
    struct sNoa* esq;
    struct sNoa* dir;
}TNoA;

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

int altura_NO(TNoA *no){
    if (no == NULL)
        return -1;
    else 
        return no->h;  
}

int fatorBalanceamento_NO(TNoA *no){
    return (altura_NO(no -> dir) - altura_NO(no->esq));
}

TNoA* rotacao_direita(TNoA* pt){
    TNoA *ptu;
    ptu = pt->esq;
    pt->esq = ptu->dir;
    ptu->dir = pt;
    pt ->h = maior(altura_NO(pt->esq),altura_NO(pt->dir))+1;
    ptu->h = maior(altura_NO(ptu->esq), pt->h)+1;
    pt = ptu;

    return pt;
}

TNoA* rotacao_esquerda(TNoA* pt){
    TNoA *ptu;
    ptu = pt->dir;
    pt->dir = ptu->esq;
    ptu-> esq = pt;
    pt-> h = maior(altura_NO(pt->esq),altura_NO(pt->dir))+1;
    ptu-> h = maior(altura_NO(ptu->dir), pt->h)+1;
    pt = ptu;

    return pt;
}

TNoA* rotacao_dupla_direita(TNoA* pt){
    pt->esq = rotacao_esquerda(pt->esq);
    pt = rotacao_direita(pt);
    return pt;
}

TNoA* rotacao_dupla_esquerda(TNoA* pt){
    pt->dir = rotacao_direita(pt->dir);
    pt = rotacao_esquerda(pt);
    return pt; 
}

TNoA* insere_AVL(TNoA *no, int chave){
    TNoA* u;

    if (no == NULL){
        no = (TNoA *) malloc(sizeof(TNoA));
        no->chave = chave;
        no->esq = NULL;
        no->dir = NULL;
        no->h = 0;
        no->fb = 0;
    }

    else if(chave < (no->chave)){
        no->esq = insere_AVL(no->esq, chave);
        no->h = no->esq->h +1;
        no->fb = fatorBalanceamento_NO(no);

        if (no->fb <= -2){
            u = no->esq;/*Recebe filho a esquerda*/
            u->fb = fatorBalanceamento_NO(u);
            
            if (u->fb == -1){/*Caso de sinais iguais negativos: RD*/
                //printf("RSD(%d)\n",no->chave);
                no = rotacao_direita(no);
                num += 1;
            }
            else{/*Caso de sinais diferentes: Rotacao dupla direita */
                //printf("RDD(%d)\n", no->chave);
                no = rotacao_dupla_direita(no);
                num += 1;
            }   
            no -> fb = 0;  
        }
    }

    else if(chave > (no->chave)){
        no -> dir = insere_AVL(no->dir, chave);
        no -> h = no->dir->h +1;
        no -> fb = fatorBalanceamento_NO(no);

        if (no->fb >= 2){
            u = no->dir;/*Recebe filho a direita*/
            u->fb = fatorBalanceamento_NO(u);
            
            if (u->fb == 1){/*Caso de sinais iguais negativos: RSE*/
                //printf("RSE(%d)\n",no->chave);
                no = rotacao_esquerda(no);
                num += 1;
            }
            else{/*Caso de sinais diferentes: Rotacao dupla esquerda */
                //printf("RDE(%d)\n", no->chave);
                no = rotacao_dupla_esquerda(no);
                num += 1;
            }   
            no -> fb = 0;  
        }
    }

    else{
        printf("Insercao Invalida\n");
        exit(1);
    }
    return no;
}

void imprime_AVL(TNoA* no, int tab){
    if(no != NULL){
        tab += 10;
        imprime_AVL(no->dir, tab);
        printf("\n");
        for (int i = 10; i < tab; i++)
            printf(" ");

        printf("%d (%d)\n", no->chave, no->h);
        imprime_AVL(no->esq, tab);
    }
}

int Altura_AVL(TNoA *no){ 
    return no->h+1;
}

int rotations(){
    return num;
}

void restart(){
    num = 0;
}

/*int main(){
    TNoA *tree;
    tree = NULL;

    tree = insere_AVL(tree, 10);
    tree = insere_AVL(tree, 7);
    tree = insere_AVL(tree, 6);
    tree = insere_AVL(tree, 3);
    tree = insere_AVL(tree, 8);

    printf("Altura: %d\n", Altura_AVL(tree));
    printf("rotacoes: %d\n", rotations());

    imprime_AVL(tree, 0);

}*/


#endif

