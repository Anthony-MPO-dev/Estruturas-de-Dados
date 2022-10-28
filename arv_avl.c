#include <stdio.h>
#include <stdlib.h>

typedef struct  sNoA
{
    int chave;
    int fb; //fator balanceamento
    int h; //altura no
    struct sNoA *esq;
    struct sNoA *dir;
}TNoA;


//função que retorna a altura de um no
int altura_NO(TNoA *no){
    if (no == NULL)
        return -1;
    else
        return no->h;     

}   

int maior(int x, int y){
    if(x>y)
        return x;
    else
        return y;
}


int fatorBalanceamento(TNoA * no){
    return (altura_NO(no->dir) - altura_NO(no->esq));
}

TNoA *rotacao_direita(TNoA *pt){
    //nó auxiliar
    TNoA *ptu;
    //recebe no filho esquerdo
    ptu = pt->esq;
    //filho a direita do filho a esquerda agora e filho a esquerda 
    pt->esq = ptu->dir;
    ptu->dir = pt;

    //no rotacionado rerebe nova altura, somando 1 + a maior altura de um dos filhos
    pt->h = maior(altura_NO(pt->esq), altura_NO(pt->dir))+1;

    //atualiza altura do novo nó pai
    ptu->h = maior(altura_NO(ptu->esq), pt->h)+1;

    

    pt = ptu;
    return pt;
}

TNoA *rotacao_esquerda(TNoA *pt){
    //nó auxiliar
    TNoA *ptu;
    //recebe no filho direita
    ptu = pt->dir;
    //filho a esquerda do filho a direita agora e filho a direita 
    pt->dir = ptu->esq;
    ptu->esq     = pt;

    //no rotacionado rerebe nova altura, somando 1 + a maior altura de um dos filhos
    pt->h = maior(altura_NO(pt->esq), altura_NO(pt->dir))+1;
    
    //atualiza altura do novo nó pai
    ptu->h = maior(altura_NO(ptu->esq), pt->h)+1;

    pt = ptu;
    return pt;
}

//Rotação dupla a direita
TNoA *RDD(TNoA* pt){
    pt->esq = rotacao_esquerda(pt->esq);
    pt = rotacao_direita(pt);
    return pt;
}

//Rotação dupla a esquerda
TNoA *RDE(TNoA* pt){
    pt->dir = rotacao_direita(pt->dir);
    pt = rotacao_esquerda(pt);
    return pt;
}

//função insere valores na arvore_avl
TNoA *insere(TNoA* no, int chave){
    //no auxiliar
    TNoA *u;
    //if no vazio ou no folha
    if(no == NULL){
        no = (TNoA*)malloc(sizeof(TNoA));
        no->chave = chave;
        no->esq = NULL;
        no->dir = NULL;
        no->h = 0;
        no->fb = 0;
    }else if(chave < no->chave){
        no->esq = insere(no->esq, chave);
        no->h = no->esq->h +1;
        no->fb = fatorBalanceamento(no);
        //desbalanceamento a esquerda
        if(no->fb <= -2){
            u = no->esq;
            if(u->fb == -1){
                printf("RSD\n");
                no = rotacao_direita(no);
            }else{
                printf("RDD\n");
                no = RDD(no);
            }
            no->fb = fatorBalanceamento(no);
        }
    }else if(chave > no->chave){
        no->dir = insere(no->dir, chave);
        no->h = no->dir->h +1;
        no->fb = fatorBalanceamento(no);
        //desbalanceamento a direita
        if(no->fb >= 2){
            u = no->dir;
            if(u->fb == 1){
                printf("RSE\n");
                no = rotacao_esquerda(no);
            }else{
                printf("RDE\n");
                no = RDE(no);
            }
            no->fb = fatorBalanceamento(no);
        }
    }else{
        //ERRO: chave ja existe
        printf("ERRO: Inserçao invalida (Chave ja existente)");
        exit(1);
    }
    return no;
}

void imprime(TNoA *no, int tab){
    if(no != NULL){
        tab +=10;
        imprime(no->dir, tab);
        printf("\n");
        for(int i =10; i<tab; i++)
            printf(" ");
        
        printf("%d (%d)\n", no->chave, no->h);
        imprime(no->esq, tab +2);
    }
}

int main(){
    TNoA* raiz;
    raiz = NULL;

    printf("************************50\n");
    raiz = insere(raiz,50);
    printf("************************40\n");
    raiz = insere(raiz,40);
    printf("************************30\n");
    raiz = insere(raiz,30);

    imprime(raiz, 0);

}