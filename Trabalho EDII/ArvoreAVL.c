#ifndef ARVOREAVL //Verificacao se biblioteca foi carregada
#define ARVOREAVL

#include <stdio.h>
#include <stdlib.h>

#include "aluno.c"

int rotacoes;

typedef struct sNoA{
    int chave;
    int fb; //fator balanceamento
    int h; //altura no
    Alunos* aluno;
    struct sNoA *esq;
    struct sNoA *dir;
}ArvAVL;

//função que retorna a altura de um no
int altura_NO(ArvAVL *no){
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

int fatorBalanceamento(ArvAVL * no){
    return (altura_NO(no->dir) - altura_NO(no->esq));
}

ArvAVL *rotacao_direita(ArvAVL *pt){
    //nó auxiliar
    ArvAVL *ptu;
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

ArvAVL *rotacao_esquerda(ArvAVL *pt){
    //nó auxiliar
    ArvAVL *ptu;
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
ArvAVL *RDD(ArvAVL* pt){
    pt->esq = rotacao_esquerda(pt->esq);
    pt = rotacao_direita(pt);
    return pt;
}

//Rotação dupla a esquerda
ArvAVL *RDE(ArvAVL* pt){
    pt->dir = rotacao_direita(pt->dir);
    pt = rotacao_esquerda(pt);
    return pt;
}

//função insere valores na arvore_avl
ArvAVL *insereArvAVL(ArvAVL *no, int chave, Alunos *aluno, int *rt){
    //no auxiliar
    ArvAVL *u;
    //if no vazio ou no folha
    if(no == NULL){
        no = (ArvAVL*)malloc(sizeof(ArvAVL));
        no->chave = chave;
        no->esq = NULL;
        no->dir = NULL;
        no->aluno = aluno;
        no->h = 0;
        no->fb = 0;
    }else if(chave < no->chave){
        no->esq = insereArvAVL(no->esq, chave, aluno, rt);
        no->h = no->esq->h +1;
        no->fb = fatorBalanceamento(no);
        //desbalanceamento a esquerda
        if(no->fb <= -2){
            u = no->esq;
            if(u->fb == -1){
                //printf("RSD\n");
                no = rotacao_direita(no);
                *rt = *rt + 1;
            }else{
                //printf("RDD\n");
                no = RDD(no);
                *rt = *rt + 1;
            }
            no->fb = fatorBalanceamento(no);
        }
    }else if(chave > no->chave){
        no->dir = insereArvAVL(no->dir, chave, aluno, rt);
        no->h = no->dir->h +1;
        no->fb = fatorBalanceamento(no);
        //desbalanceamento a direita
        if(no->fb >= 2){
            u = no->dir;
            if(u->fb == 1){
                //printf("RSE\n");
                no = rotacao_esquerda(no);
                *rt = *rt + 1;
            }else{
                //printf("RDE\n");
                no = RDE(no);
                *rt = *rt + 1;
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

int alturaAVL(ArvAVL *no){
    if (no == NULL){
        return -1;
    }
    else{
        int esq = alturaAVL(no->esq);
        int dir = alturaAVL(no->dir);
        if (esq > dir){
            return esq + 1;
        }
        else{
            return dir + 1;
        }
    } 
}

ArvAVL* buscaArv_AVL(ArvAVL *no, int chave){
    while (no != NULL){
        if (no->chave == chave)
            return no;
        else if (no->chave > chave)
            no = no->esq;
        else
            no = no->dir;
    }
    return NULL;
}

void imprimeAVL(ArvAVL *no){
    if(no != NULL){
        imprimeAVL(no->esq);
        printf("%d %s %s %s %lf %lf %lf %lf %lf\n", 
        no->chave, 
        no->aluno->estado, 
        no->aluno->municipio, 
        no->aluno->rede,
        no->aluno->media_ciencias_natureza,
        no->aluno->media_ciencias_humanas,
        no->aluno->media_linguagem,
        no->aluno->media_matematica,
        no->aluno->media_redacao);
        imprimeAVL(no->dir);
    }
}

#endif